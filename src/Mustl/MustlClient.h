#ifndef MUSTLCLIENT_H
#define MUSTLCLIENT_H
/*
 * $Id: MustlClient.h,v 1.3 2002/12/13 01:06:53 southa Exp $
 * $Log: MustlClient.h,v $
 * Revision 1.3  2002/12/13 01:06:53  southa
 * Mustl work
 *
 * Revision 1.2  2002/12/12 18:38:24  southa
 * Mustl separation
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
 * Revision 1.11  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 * Revision 1.10  2002/11/23 14:39:05  southa
 * Store ports in network order
 *
 * Revision 1.9  2002/11/22 18:02:43  southa
 * Wait for TCP connection
 *
 * Revision 1.8  2002/11/20 22:35:27  southa
 * Multiplayer setup
 *
 * Revision 1.7  2002/11/05 18:15:17  southa
 * Web server
 *
 * Revision 1.6  2002/11/04 01:02:38  southa
 * Link checks
 *
 * Revision 1.5  2002/11/03 18:43:09  southa
 * Network fixes
 *
 * Revision 1.4  2002/11/01 18:46:25  southa
 * UDP Links
 *
 * Revision 1.3  2002/11/01 16:15:27  southa
 * Network send and receive
 *
 * Revision 1.2  2002/10/31 19:55:54  southa
 * Network links
 *
 * Revision 1.1  2002/10/31 16:41:33  southa
 * Network client
 *
 */

#include "MustlStandard.h"
#include "MustlAddress.h"

class MustlData;

class MustlClient
{
public:
    MustlClient();
    ~MustlClient();

    void TCPConnect(const MustlAddress& inAddress);
    void TCPSocketTake(Mustl::tSocket inSocket, const MustlAddress& inAddress);
    void UDPConnect(const MustlAddress& inAddress);
    void TCPDisconnect(void);
    void UDPDisconnect(void);

    void TCPSend(MustlData& inData);
    void TCPReceive(MustlData& outData);
    void UDPSend(MustlData& inData);
    void UDPReceive(MustlData& outData);

    bool TCPConnectionCompleted(void);
    // void ResolveTargetName(void);
    bool UDPConnectedGet(void) const { return m_udpConnected; }
    void UDPRemotePortSetHostOrder(Mustl::U32 inPortHostOrder);
    const MustlAddress& TCPAddressGet(void) const { return m_tcpAddress; }
    const MustlAddress& UDPAddressGet(void) const { return m_udpAddress; }
    void UDPAddressSet(const MustlAddress& inAddress) { m_udpAddress = inAddress; }
    void Print(ostream& ioOut) const;
    
private:

    Mustl::tSocket m_tcpSocket;
    Mustl::tSocket m_udpSocket;
    MustlAddress m_tcpAddress;
    MustlAddress m_udpAddress;
    bool m_tcpConnected;
    bool m_udpConnected;
    bool m_logTraffic;
};

inline ostream&
operator<<(ostream &ioOut, const MustlClient& inClient)
{
    inClient.Print(ioOut);
    return ioOut;
}
#endif
