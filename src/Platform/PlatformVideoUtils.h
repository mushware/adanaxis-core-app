//%includeGuardStart {
#ifndef PLATFORMVIDEOUTILS_H
#define PLATFORMVIDEOUTILS_H
//%includeGuardStart } AEK+Al+NrqhKC+Q5B1/9Bg
//%Header {
/*****************************************************************************
 *
 * File: src/Platform/PlatformVideoUtils.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } fB1pDiCpnlEZRwSPca6UqQ
/*
 * $Id: PlatformVideoUtils.h,v 1.11 2003/08/21 23:09:34 southa Exp $
 * $Log: PlatformVideoUtils.h,v $
 * Revision 1.11  2003/08/21 23:09:34  southa
 * Fixed file headers
 *
 * Revision 1.10  2003/04/13 08:39:18  southa
 * Bring window to foreground on mode change
 *
 * Revision 1.9  2003/01/20 10:45:31  southa
 * Singleton tidying
 *
 * Revision 1.8  2003/01/11 13:03:18  southa
 * Use Mushcore header
 *
 * Revision 1.7  2002/12/20 13:17:47  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/12/03 20:28:18  southa
 * Network, player and control work
 *
 * Revision 1.5  2002/11/12 11:49:22  southa
 * Initial MHTML processing
 *
 * Revision 1.4  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.3  2002/10/17 15:50:59  southa
 * Config saving, pause and quit
 *
 * Revision 1.2  2002/10/15 14:02:31  southa
 * Mode changes
 *
 * Revision 1.1  2002/10/14 18:13:18  southa
 * GLModeDef work
 *
 */

#include "Mushcore.h"

class GLModeDef;

class PlatformVideoUtils
{
public:
    PlatformVideoUtils();
    static PlatformVideoUtils& Sgl(void) {return *((m_instance==NULL)?m_instance=new PlatformVideoUtils:m_instance);}
    const GLModeDef& ModeDefGet(Mushware::U32 inNum);
    Mushware::U32 PreviousModeDef(Mushware::U32 inNum) const;
    Mushware::U32 NextModeDef(Mushware::U32 inNum) const;
    Mushware::U32 DefaultModeGet(void) const;
    Mushware::U32 NumModesGet(void) const;
    void RenderModeInfo(Mushware::U32 inNum) const;
    void ModeChangePrologue(void);
    void ModeChangeEpilogue(void);
    static void VBLWait(void);
    static void ForceShowCursor(void);
    static void AppActivate(void);
    
private:
    std::vector<GLModeDef> m_modeDefs;
    static PlatformVideoUtils *m_instance;

    bool m_threadAttached;
    unsigned long m_fgThreadID;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
