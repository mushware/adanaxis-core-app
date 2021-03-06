//%includeGuardStart {
#ifndef MUSTLPROTOCOL_H
#define MUSTLPROTOCOL_H
//%includeGuardStart } 1s1+w5hUT8AWziTGSz4RqA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlProtocol.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } om9WeRM0CBgomAbZrb1Nmw
/*
 * $Id: MustlProtocol.h,v 1.9 2006/06/01 15:39:54 southa Exp $
 * $Log: MustlProtocol.h,v $
 * Revision 1.9  2006/06/01 15:39:54  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/05/19 13:02:19  southa
 * Mac release work
 *
 * Revision 1.7  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.6  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:30  southa
 * Fixed file headers
 *
 * Revision 1.4  2002/12/29 20:30:56  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.3  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/17 12:53:34  southa
 * Mustl library
 *
 * Revision 1.1  2002/12/12 14:00:26  southa
 * Created Mustl
 *
 * Revision 1.11  2002/12/07 18:32:16  southa
 * Network ID stuff
 *
 * Revision 1.10  2002/12/05 13:20:13  southa
 * Client link handling
 *
 * Revision 1.9  2002/11/27 20:17:27  southa
 * Basic network cleardown
 *
 * Revision 1.8  2002/11/27 16:35:10  southa
 * Client and server image handling
 *
 * Revision 1.7  2002/11/25 12:06:18  southa
 * Received net message routing
 *
 * Revision 1.6  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.5  2002/11/04 19:34:47  southa
 * Network link maintenance
 *
 * Revision 1.4  2002/11/04 13:11:58  southa
 * Link setup work
 *
 * Revision 1.3  2002/11/04 01:02:38  southa
 * Link checks
 *
 * Revision 1.2  2002/11/03 20:10:00  southa
 * Initial message unpacking
 *
 * Revision 1.1  2002/11/03 18:43:09  southa
 * Network fixes
 *
 */

#include "MustlStandard.h"

class MustlData;
class MustlID;

class MustlProtocol
{
public:
    enum tMessageType
    {
        kMessageTypeInvalid,
        kMessageTypeMinLinkLayer='A', // These messages are for the link
        kMessageTypeTCPLinkCheck=kMessageTypeMinLinkLayer,
        kMessageTypeTCPLinkCheckReply,
        kMessageTypeUDPLinkCheck,
        kMessageTypeUDPLinkCheckReply,
        kMessageTypeKillLink,
        kMessageTypeIDRequest,
        kMessageTypeMaxFixedLength,
        kMessageTypeMaxLinkLayer, // Subsequent messages are for the application
        kMessageTypeLongAppStart=128,
        kMessageTypeIDTransfer=kMessageTypeLongAppStart,
        kMessageTypeLongAppEnd=191,
        kMessageTypeShortAppStart=192,
        kMessageTypeShortAppEnd=224,
    };

    enum tReasonCode
    {
        kReasonCodeInvalid,
        kReasonCodeNone=65,
        kReasonCodeDisconnect=66,
        kReasonCodePeerDisconnected=67,
        kReasonCodeTCPLinkCheckFail=68,
        kReasonCodeTCPBadLink=69,
        kReasonCodeUDPLinkCheckFail=70,
        kReasonCodeUDPBadLink=71,
        kReasonCodeIdleTimeout=72,
        kReasonCodeUserDisconnect=73
    };
    
    static void TCPLinkCheckCreate(MustlData& outData, Mustl::U32 inSequenceNumber);
    static void TCPLinkCheckReplyCreate(MustlData& outData, Mustl::U32 inSequenceNumber);
    static void UDPLinkCheckCreate(MustlData& outData, Mustl::U32 inSequenceNumber);
    static void UDPLinkCheckReplyCreate(MustlData& outData, Mustl::U32 inSequenceNumber);
    static void KillLinkCreate(MustlData& outData, tReasonCode inReason);
    static void IDRequestCreate(MustlData& outData);

    static void IDTransferCreate(MustlData& outData, const MustlID& inID);

    static void LongAppMessageCreate(MustlData& ioData, Mustl::U32 inType, const std::string& inStr);
    static void LongAppMessageHeaderCreate(MustlData& ioData, Mustl::U32 inType);
    static void LongAppMessageFinish(MustlData& ioData);

    static void Unpack(MustlData& ioData);
    static void RemoveLength(MustlData& ioData, Mustl::U32 inType);
    static Mustl::U32 LinkToAppType(Mustl::U32 inType);
    static bool MessageTake(MustlData& ioData);
    static bool MessageTypeIsLinkLayer(Mustl::U32 inType);

    
private:
    enum
    {
        kSyncByte1='S',
        kSyncByte2='y'
    };

    enum tUnpackUnpackState
    {
        kUnpackStateInvalid,
        kUnpackStateSync1,
        kUnpackStateSync2,
        kUnpackStateMessageType,
        kUnpackStateLengthMSB,
        kUnpackStateLengthLSB,
        kUnpackStateMessageDone,
        kUnpackStateMessageReady
    };
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
