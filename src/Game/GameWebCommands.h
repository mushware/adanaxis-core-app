//%includeGuardStart {
#ifndef GAMEWEBCOMMANDS_H
#define GAMEWEBCOMMANDS_H
//%includeGuardStart } puAgc09IqUu5uc5E1mmYLA
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameWebCommands.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } k0sdtxsnYLlHUV/432PZEQ
/*
 * $Id: GameWebCommands.h,v 1.8 2003/08/21 23:08:59 southa Exp $
 * $Log: GameWebCommands.h,v $
 * Revision 1.8  2003/08/21 23:08:59  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/17 13:30:39  southa
 * Source conditioning and build fixes
 *
 * Revision 1.6  2003/01/11 13:03:15  southa
 * Use Mushcore header
 *
 * Revision 1.5  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
 * Revision 1.4  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/11/27 13:23:26  southa
 * Server and client data exchange
 *
 * Revision 1.2  2002/11/20 22:35:27  southa
 * Multiplayer setup
 *
 * Revision 1.1  2002/11/18 13:40:32  southa
 * Moved to correct place
 *
 * Revision 1.5  2002/11/14 19:35:30  southa
 * Configuration work
 *
 * Revision 1.4  2002/11/14 17:29:07  southa
 * Config database
 *
 * Revision 1.3  2002/11/14 11:40:28  southa
 * Configuration handling
 *
 * Revision 1.2  2002/11/12 18:02:13  southa
 * POST handling and handlepostvalues command
 *
 * Revision 1.1  2002/11/07 11:59:02  southa
 * Web commands
 *
 */

#include "Mushcore.h"

class GameWebCommands
{
public:
    static void Install(void);
    static MushcoreScalar PostHandler(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar DisplayModesWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameConfigInputWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameServerStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameClientStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameLinkStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);

private:

};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
