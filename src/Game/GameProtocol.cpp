/*
 * $Id: GameProtocol.cpp,v 1.4 2002/11/25 12:06:18 southa Exp $
 * $Log: GameProtocol.cpp,v $
 * Revision 1.4  2002/11/25 12:06:18  southa
 * Received net message routing
 *
 * Revision 1.3  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.2  2002/11/24 23:54:36  southa
 * Initial send of objects over links
 *
 * Revision 1.1  2002/11/24 23:18:24  southa
 * Added type name accessor to CorePickle
 *
 */

#include "GameProtocol.h"

#include "mushMedia.h"

void
GameProtocol::CreateObjectCreate(MediaNetData& ioData, CorePickle& inObj, const string& inRemoteName)
{
    ostringstream netStream;

    netStream << "<" << inObj.TypeNameGet() << " name=\"" << inRemoteName << "\">";
    inObj.Pickle(netStream);
    netStream << "</" << inObj.TypeNameGet() << ">";
    MediaNetProtocol::LongAppMessageCreate(ioData, kMessageTypeCreateObject, netStream.str());
    MediaNetLog::Instance().NetLog() << "Sent " << ioData << endl; 
}
