//%includeGuardStart {
#ifndef GAMESPACEPOINT_H
#define GAMESPACEPOINT_H
//%includeGuardStart } /+DKWObbq0SNT4/q5yxtCA
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameSpacePoint.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } YxXYjdrjzBHVG0kABQN2wA
/*
 * $Id: GameSpacePoint.h,v 1.8 2003/08/21 23:08:55 southa Exp $
 * $Log: GameSpacePoint.h,v $
 * Revision 1.8  2003/08/21 23:08:55  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.6  2002/12/20 13:17:43  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:26  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.2  2002/08/01 16:47:12  southa
 * First multi-box collsion checking
 *
 * Revision 1.1  2002/07/31 16:27:17  southa
 * Collision checking work
 *
 */

#include "Mushcore.h"
#include "mushGL.h"

class GameSpacePoint : public GLPoint
{
public:
    GameSpacePoint() {}
    explicit GameSpacePoint(const GLPoint& inPoint) { x=inPoint.x; y=inPoint.y; }

private:
    GameSpacePoint(const GameMapPoint &inPoint) {} // prevent this
    GameSpacePoint& operator=(const GameMapPoint& inPoint) { return *this; } // prevent this
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
