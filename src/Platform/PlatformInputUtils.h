#ifndef PLATFORMINPUTUTILS_H
#define PLATFORMINPUTUTILS_H
#ifndef INPUTUTILS_H
#define INPUTUTILS_H
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
 * $Id: PlatformInputUtils.h,v 1.1 2002/06/06 14:59:57 southa Exp $
 * $Log: PlatformInputUtils.h,v $
 * Revision 1.1  2002/06/06 14:59:57  southa
 * Mouse fixes
 *
 * Revision 1.1  2002/06/06 12:32:37  southa
 * Added support for src/Support/platform
 *
 * Revision 1.1  2002/06/06 10:40:20  southa
 * Created
 *
 */

#include "mushCore.h"

class PlatformInputUtils
{
public:
    static bool MouseDeltaPrologue(S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY);    
    static void GetMouseDeltas(S32& outXDelta, S32& outYDelta, S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY);
    static void MouseDeltaEpilogue(S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY);
};

#endif
#endif
