/*
 * $Id: MediaNetWebServer.cpp,v 1.8 2002/11/24 12:57:02 southa Exp $
 * $Log: MediaNetWebServer.cpp,v $
 * Revision 1.8  2002/11/24 12:57:02  southa
 * Added configuration host protection
 *
 * Revision 1.7  2002/11/24 00:29:08  southa
 * Serve web pages to local addresses only
 *
 * Revision 1.6  2002/11/23 14:39:06  southa
 * Store ports in network order
 *
 * Revision 1.5  2002/11/22 11:42:07  southa
 * Added developer controls
 *
 * Revision 1.4  2002/11/18 21:02:40  southa
 * Prevent crash on exit
 *
 * Revision 1.3  2002/11/15 18:58:34  southa
 * Configuration mode
 *
 * Revision 1.2  2002/11/06 14:16:57  southa
 * Basic web server
 *
 * Revision 1.1  2002/11/05 18:15:18  southa
 * Web server
 *
 */

#include "MediaNetWebServer.h"

#include "MediaNet.h"
#include "MediaNetLog.h"
#include "MediaNetWebLink.h"

#include "mushPlatform.h"

auto_ptr<MediaNetWebServer> MediaNetWebServer::m_instance;

MediaNetWebServer::MediaNetWebServer() :
    m_linkCtr(0),
    m_permission(kPermissionLocal),
    m_serving(false)
{
}

void
MediaNetWebServer::Connect(U32 inPort)
{
    if (m_serving)
    {
        Disconnect();
    }

    MediaNet::Instance();

    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, NULL, inPort) == -1)
    {
        ostringstream message;
        message << "Server creation failed: " << SDLNet_GetError();
        throw(NetworkFail(message.str()));
    }

    m_tcpSocket=SDLNet_TCP_Open(&ip);

    if (m_tcpSocket == NULL)
    {
        ostringstream message;
        message << "Server creation failed: " << SDLNet_GetError();
        throw(NetworkFail(message.str()));
    }

    MediaNetLog::Instance().WebLog() << "Created web server on port " << inPort << endl;
    m_serving=true;
}

void
MediaNetWebServer::Disconnect(void)
{
    if (m_serving)
    {
        SDLNet_TCP_Close(m_tcpSocket);
        m_tcpSocket = NULL;
        m_serving=false;
    }
}
        
MediaNetWebServer::~MediaNetWebServer()
{
    if (m_serving)
    {
        COREASSERT(m_tcpSocket != NULL);
        SDLNet_TCP_Close(m_tcpSocket);
    }
    MediaNetLog::Instance().WebLog() << "Closed web server" << endl;
}

void
MediaNetWebServer::Accept(void)
{
    if (m_serving)
    {
        COREASSERT(m_tcpSocket != NULL);
        TCPsocket newSocket=SDLNet_TCP_Accept(m_tcpSocket);
        if (newSocket != NULL)
        {
            IPaddress *remoteIP;

            remoteIP = SDLNet_TCP_GetPeerAddress(newSocket);
            if (remoteIP == NULL)
            {
                throw(NetworkFail(string("Couldn't resolve IP for socket: ")+SDLNet_GetError()));
            }
            U32 remoteHost=remoteIP->host;
            if (CheckIPAddressAllowed(remoteHost))
            {
                ostringstream name;
                name << "web" << m_linkCtr;
                CoreData<MediaNetWebLink>::Instance().Give(name.str(), new MediaNetWebLink(newSocket));
                m_linkCtr++;
                MediaNetLog::Instance().WebLog() << "Accepted web connection " << name.str() << endl;
            }
            else
            {
                SDLNet_TCP_Close(newSocket);
                MediaNetLog::Instance().WebLog() << "Rejected web connection from prohibited IP address " << MediaNetUtils::IPAddressToLogString(remoteHost) << endl;
            }
        }
    }
}

bool
MediaNetWebServer::IsConnected(void) const
{
    return m_serving;
}

void
MediaNetWebServer::ExtraAllowedAddrSet(const string& inAddr)
{
    if (inAddr != m_extraAllowedAddr)
    {
        m_extraAllowedAddr=inAddr;

        IPaddress remoteIP;
        char buffer[strlen(inAddr.c_str())+1];
        strncpy(buffer, inAddr.c_str(), strlen(inAddr.c_str())+1);

        if (SDLNet_ResolveHost(&remoteIP, buffer, 0) == -1)
        {
            PlatformMiscUtils::MinorErrorBox("Could not resolve host name '"+inAddr+"', entered as the Extra Allowed Configuration address");
            m_extraAllowedIP = 0;
        }
        else
        {
            m_extraAllowedIP = remoteIP.host;
        }
    }
}

bool
MediaNetWebServer::CheckIPAddressAllowed(U32 inIPNetworkOrder)
{
    bool retVal;
    bool askUser=false;
    
    switch (m_permission)
    {
        case kPermissionNone:
            askUser=true;
            break;

        case kPermissionLocal:
            if (PlatformNet::IsLocalAddress(inIPNetworkOrder))
            {
                retVal=true;
            }
            else
            {
                askUser=true;
            }
            break;

        case kPermissionAll:
            retVal=true;
            break;

        default:
            throw(LogicFail("Bad value for MediaNetWebServer::m_permission"));
    }

    if (askUser)
    {
        if (inIPNetworkOrder == m_extraAllowedIP && m_extraAllowedAddr.size() != 0)
        {
            // This is the extra allowed address
            retVal = true;
        }
        else
        {
            map<U32, bool>::const_iterator p = m_permissionMap.find(inIPNetworkOrder);
            if (p != m_permissionMap.end())
            {
                retVal = p->second;
            }
            else
            {
                ostringstream message;
                message << "A computer with IP address " << MediaNetUtils::IPAddressToString(inIPNetworkOrder);
                message << " is attempting to connect to the " << CoreInfo::ApplicationNameGet() << " localweb server.  Would you like to allow this?  If in doubt, choose Deny.";
                retVal=PlatformMiscUtils::PermissionBox(message.str(), false);
    
                if (!retVal && PlatformNet::IsLocalAddress(inIPNetworkOrder))
                {
                    // Don't store denied permission for local addresses
                }
                else
                {
                    m_permissionMap[inIPNetworkOrder] = retVal;
                }
            }
        }
    }
    return retVal;
}
