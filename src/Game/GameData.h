#ifndef GAMEDATA_H
#define GAMEDATA_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameData.h,v 1.19 2002/12/03 20:28:16 southa Exp $
 * $Log: GameData.h,v $
 * Revision 1.19  2002/12/03 20:28:16  southa
 * Network, player and control work
 *
 * Revision 1.18  2002/11/18 18:55:58  southa
 * Game resume and quit
 *
 * Revision 1.17  2002/11/17 13:38:30  southa
 * Game selection
 *
 * Revision 1.16  2002/10/22 20:42:03  southa
 * Source conditioning
 *
 * Revision 1.15  2002/08/27 08:56:23  southa
 * Source conditioning
 *
 * Revision 1.14  2002/08/22 10:11:11  southa
 * Save records, spacebar dialogues
 *
 * Revision 1.13  2002/08/20 11:43:25  southa
 * GameRewards added
 *
 * Revision 1.12  2002/08/18 20:44:34  southa
 * Initial chequepoint work
 *
 * Revision 1.11  2002/08/10 12:34:48  southa
 * Added current dialogues
 *
 * Revision 1.10  2002/08/09 17:09:04  southa
 * GameDialogue added
 *
 * Revision 1.9  2002/08/07 13:36:49  southa
 * Conditioned source
 *
 * Revision 1.8  2002/07/18 11:40:35  southa
 * Overplotting and movement
 *
 * Revision 1.7  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.6  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.5  2002/06/05 15:53:26  southa
 * Player and keyboard control
 *
 * Revision 1.4  2002/06/04 20:27:37  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.3  2002/06/04 14:12:25  southa
 * Traits loader first stage
 *
 * Revision 1.2  2002/05/30 16:21:53  southa
 * Pickleable GameContract
 *
 * Revision 1.1  2002/05/30 14:41:12  southa
 * GameData and loadtilemap command
 *
 */

#include "mushCore.h"

class GameTileMap;
class GameFloorMap;
class GameContract;
class GameTraits;
class GameController;
class GamePiece;
class GamePiecePlayer;
class GameDialogue;
class GameView;
class GameTimer;
class GameType;
class GameRewards;

class GameData
{
public:
    typedef map<string, GameDialogue *> DialogueMap;
    typedef map<string, GameDialogue *>::iterator DialogueMapIterator;
    typedef map<string, GameDialogue *>::const_iterator DialogueMapConstIterator;
    ~GameData();
    static GameData& Instance(void) {return *((m_instance==NULL)?m_instance=new GameData:m_instance);}

    void Clear(void);
    
    GameTileMap *TileMapGetOrCreate(const string& inName);
    GameTileMap *TileMapGet(const string& inName) const;
    GameFloorMap *FloorMapGetOrCreate(const string& inName);
    GameFloorMap *FloorMapGet(const string& inName) const;
    GameContract *ContractGetOrCreate(const string& inName);
    GameContract *ContractGet(const string& inName) const;
    bool ContractExists(const string& inName) const;
    void ContractsClear(void);
    GameTraits *TraitsDeleteAndCreate(const string& inName, GameTraits *inTraits);
    GameTraits *TraitsGet(const string& inName) const;
    GameController *ControllerGetOrCreate(const string& inName);
    GameController *ControllerGet(const string& inName) const;
    const GamePiece *TemplateDeleteAndCreate(const string& inName, GamePiece *inPiece);
    const GamePiece *TemplateGet(const string& inName) const;
    GamePiece *PieceDeleteAndCreate(const string& inName, GamePiece *inPiece);
    GamePiece *PieceGet(const string& inName) const;
    GameDialogue *DialogueDeleteAndCreate(const string& inName, GameDialogue *inDialogue);
    GameDialogue *DialogueGet(const string& inName) const;
    const DialogueMap& DialogueMapGet(void) const { return m_dialogues; }
    GameView *ViewGetOrCreate(const string& inName);
    GameView *ViewGet(const string& inName) const;
    GameView *CurrentViewGet(void) const;

    CoreData<GamePiecePlayer>& PlayerGet(void) { return *m_playerData; }
    
    GameTimer& TimerGet(void);
    GameType& TypeGet(void) const;
    void TypeSet(GameType *inType);
    GameRewards& RewardsGet(void) const;
    void RewardsSet(GameRewards *inRewards);

    GameDialogue *CurrentDialogueAdd(const string& inName, const GameDialogue& inDialogue);
    void CurrentDialogueDelete(const string& inName);
    const DialogueMap& CurrentDialogueMapGet(void) const { return m_currentDialogues; }
    void CurrentDialoguesClear(void);


    
    void DumpAll(ostream& inOut) const;

private:
    GameData();
    map<string, GameTileMap *> m_tilemaps;
    map<string, GameFloorMap *> m_floormaps;
    map<string, GameContract *> m_contracts;
    map<string, GameTraits *> m_traits;
    map<string, GameController *> m_controllers;
    DialogueMap m_dialogues;
    map<string, GamePiece *> m_templates;
    map<string, GamePiece *> m_pieces;
    map<string, GameView *> m_views;

    CoreData<GamePiecePlayer> *m_playerData;
    
    GameTimer *m_timer;
    GameType *m_gameType;
    GameRewards *m_gameRewards;
    
    DialogueMap m_currentDialogues;

    static GameData *m_instance;
};

class GameDataNotPresent: public exception
{
public:
    GameDataNotPresent(const string &inMessage) {m_message=inMessage;}
    ~GameDataNotPresent() throw() {}
    const string& StringGet(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    string m_message;
};

inline ostream& operator<<(ostream &s, GameDataNotPresent f)
{
    return s << f.StringGet();
}

#endif
