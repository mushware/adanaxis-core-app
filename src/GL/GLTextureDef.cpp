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
 * $Id: GLTextureDef.cpp,v 1.8 2003/01/13 14:31:55 southa Exp $
 * $Log: GLTextureDef.cpp,v $
 * Revision 1.8  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.7  2003/01/12 17:32:51  southa
 * Mushcore work
 *
 * Revision 1.6  2002/12/29 20:59:53  southa
 * More build fixes
 *
 * Revision 1.5  2002/12/20 13:17:36  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/19 15:44:39  southa
 * Graphic optimisations
 *
 */

#include "GLTextureDef.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

bool
GLTextureDef::NeedsAlpha(void) const
{
    if (!m_needsAlphaValid)
    {
        DetermineNeedsAlpha();
    }
    return m_needsAlpha;
}

void
GLTextureDef::DetermineNeedsAlpha(void) const
{
    U8 *dataPtr=reinterpret_cast<U8 *>(m_dataPtr);
    U32 dataSize=m_width*m_height; // Number of pixels to check
    
    MUSHCOREASSERT(dataPtr != NULL || dataSize == 0);

    m_needsAlpha=false;
    dataPtr += 3; // Advance to first alpha byte
    for (U32 i=0; i<dataSize; ++i)
    {
        if (*dataPtr != 255)
        {
            m_needsAlpha = true;
            break;
        }
        dataPtr+=4;
    }
    m_needsAlphaValid=true;
}
