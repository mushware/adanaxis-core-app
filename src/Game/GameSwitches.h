#ifndef GAMESWITCHES_H
#define GAMESWITCHES_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameSwitches.h,v 1.1 2002/06/05 12:28:05 southa Exp $
 * $Log: GameSwitches.h,v $
 * Revision 1.1  2002/06/05 12:28:05  southa
 * Map rendered using traits
 *
 */

#define CACHETESTING 0

#if CACHETESTING
#define IFCACHETESTING(a) a
#else
#define IFCACHETESTING(a)
#endif
#endif
