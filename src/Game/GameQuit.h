#ifndef GAMEQUIT_H
#define GAMEQUIT_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GameQuit.h,v 1.5 2003/01/11 13:03:14 southa Exp $
 * $Log: GameQuit.h,v $
 * Revision 1.5  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.4  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.3  2002/12/20 13:17:42  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/03 20:28:17  southa
 * Network, player and control work
 *
 * Revision 1.1  2002/11/18 18:55:58  southa
 * Game resume and quit
 *
 */

#include "Mushcore.h"

#include "GameBase.h"

class GameQuit : public GameBase
{
public:
    GameQuit();
    virtual void Process(GameAppHandler& inAppHandler);
    virtual void Display(GameAppHandler& inAppHandler);
    virtual void ScriptFunction(const std::string& inName, GameAppHandler& inAppHandler) const;
    virtual void SwapIn(GameAppHandler& inAppHandler);
    virtual void SwapOut(GameAppHandler& inAppHandler);

protected:
    
private:
    void Init(void);
    void Timing(void);
        
    enum tGameState
    {
        kGameStateInvalid,
        kGameStateInit,
        kGameStateTiming
    };

    enum
    {
        kQuitHangTime=500, // msec to hang around regardless
        kQuitTimeout=5000  // msec to wait for web links
    };

    tGameState m_gameState;
    Mushware::U32 m_startMsec;
};
#endif
