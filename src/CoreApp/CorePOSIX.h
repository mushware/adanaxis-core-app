#ifndef COREPOSIX_H
#define COREPOSIX_H
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
 * $Id: CorePOSIX.h,v 1.4 2002/06/27 00:07:06 southa Exp $
 * $Log: CorePOSIX.h,v $
 * Revision 1.4  2002/06/27 00:07:06  southa
 * Catch up
 *
 * Revision 1.3  2002/06/24 16:41:14  southa
 * Fixed for mingw32
 *
 * Revision 1.2  2002/05/27 12:58:42  southa
 * GameContract and global configs added
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#else
// Assume we have everything
#define HAVE_SYS_TYPES_H 1
#define HAVE_SYS_WAIT_H 1
#define HAVE_SYS_PARAM_H 1
#define HAVE_UNISTD_H 1
#endif

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef HAVE_SYS_WAIT_H
#include <sys/wait.h>
#define HAVE_POSIX 1
#endif

#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#endif
