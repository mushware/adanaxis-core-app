//%includeGuardStart {
#ifndef MUSHMUSHCOREIO_H
#define MUSHMUSHCOREIO_H
//%includeGuardStart } hpWm4RhEe3fsJWdwb0tRJw
//%Header {
/*****************************************************************************
 *
 * File: src/API/mushMushcoreIO.h
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } EoceiVd5awxOKaVtjABc/g
/*
 * $Id: mushMushcoreIO.h,v 1.5 2006/06/22 19:07:27 southa Exp $
 * $Log: mushMushcoreIO.h,v $
 * Revision 1.5  2006/06/22 19:07:27  southa
 * Build fixes
 *
 * Revision 1.4  2006/06/01 15:38:45  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/06/14 13:25:32  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/05/19 13:01:57  southa
 * Mac release work
 *
 * Revision 1.1  2004/01/06 20:46:48  southa
 * Build fixes
 *
 */

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/MushcoreIO.h>
#elif defined(HAVE_MUSHCORE_H)
#include <MushcoreIO.h>
#else
#include "Mushcore/MushcoreIO.h"
#endif
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
