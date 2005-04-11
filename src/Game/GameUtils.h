//%includeGuardStart {
#ifndef GAMEUTILS_H
#define GAMEUTILS_H
//%includeGuardStart } tnIW58cbpoexh5GV89K1gQ
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameUtils.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 1HRLY36l0fDdeXDF6UkrqA
/*
 * $Id: GameUtils.h,v 1.1 2005/04/10 00:10:40 southa Exp $
 * $Log: GameUtils.h,v $
 * Revision 1.1  2005/04/10 00:10:40  southa
 * Registration
 *
 */

#include "mushMushcore.h"

class GameUtils
{
public:
    static Mushware::U32 Rotate(Mushware::U32 inVal, Mushware::U32 inRot);
    static Mushware::U32 GameUtils::HashGenerate(Mushware::U32 inCode);
    static bool CodeVerify(const std::string& inCode);
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
