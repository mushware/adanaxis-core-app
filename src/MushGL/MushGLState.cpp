//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLState.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } DpVSwdn2BT7R+Z75FlZHnw
/*
 * $Id: MushGLState.cpp,v 1.10 2007/04/18 12:44:38 southa Exp $
 * $Log: MushGLState.cpp,v $
 * Revision 1.10  2007/04/18 12:44:38  southa
 * Cache purge fix and pre-release tweaks
 *
 * Revision 1.9  2007/04/18 09:22:36  southa
 * Header and level fixes
 *
 * Revision 1.8  2006/09/07 16:38:51  southa
 * Vertex shader
 *
 * Revision 1.7  2006/07/18 16:58:37  southa
 * Texture fixes
 *
 * Revision 1.6  2006/06/30 17:26:10  southa
 * Render prelude
 *
 * Revision 1.5  2006/06/01 15:39:18  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/09/06 12:15:35  southa
 * Texture and rendering work
 *
 * Revision 1.3  2005/09/05 17:14:22  southa
 * Solid rendering
 *
 * Revision 1.2  2005/08/31 23:57:27  southa
 * Texture coordinate work
 *
 * Revision 1.1  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 */

#include "MushGLState.h"

#include "MushGLUtil.h"

MUSHCORE_SINGLETON_INSTANCE(MushGLState);

using namespace Mushware;
using namespace std;

MushGLState::MushGLState()
{
    InvalidateAll();
    m_standardShader.NameSet("standard");
}

void
MushGLState::InvalidateAll(void)
{
    m_colourArray = kStateNone;
    m_edgeFlagArray = kStateNone;
    m_indexArray = kStateNone;
    m_normalArray = kStateNone;
    for (Mushware::U32 i=0; i<m_texCoordArrays.size(); ++i)
    {
        m_texCoordArrays[i] = kStateNone;
    }
    m_vertexArray = kStateNone;
    m_activeTexNum = 0;
    m_clientActiveTexNum = 0;
	m_pCurrentColourBuffer = NULL;
	m_pCurrentTexCoordBuffer = NULL;
	m_pCurrentVertexBuffer = NULL;
}

void
MushGLState::Reset(void)
{
    static bool resetErrorLogged = false;
    
    ArraysDisable();
    for (Mushware::U32 i=0; i<m_textureStates.size(); ++i)
    {
        TextureDisable2D(i);
    }
    ActiveTextureZeroBased(0);
    ClientActiveTextureZeroBased(0);
    if (MushGLV::Sgl().HasShader())
    {
        try
        {
            m_standardShader.WRef().Bind();
        }
        catch (std::exception& e)
        {
            if (!resetErrorLogged)
            {
                MushcoreLog::Sgl().WarningLog() << "Shader binding failed in reset: " << e.what() << endl;
                m_standardShader.WRef().Dump(MushcoreLog::Sgl().WarningLog());
                MushcoreLog::Sgl().WarningLog() << "(This error is reported once only)" << endl;
                resetErrorLogged = true;
                
                // Ignore error - shader test will catch this problem
            }
        }    
    }
}

void
MushGLState::ResetWriteAll(void)
{
	Reset();
	InvalidateAll();

    // Make sure that all available texture units are disabled
	for (U32 i=0; i < MushGLV::Sgl().NumTextureUnits(); ++i)
	{
        ActiveTextureZeroBased(i);
        glDisable(GL_TEXTURE_2D);
		ClientActiveTextureZeroBased(i);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
    ActiveTextureZeroBased(0);
    ClientActiveTextureZeroBased(0);
	MushGLUtil::CheckGLError();
}

void
MushGLState::RenderStateSet(Mushware::U32 inRenderState)
{
    switch (inRenderState)
    {
        case kRenderState2D:
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            glDisable(GL_CULL_FACE);
            glDisable(GL_POLYGON_SMOOTH);
            glDisable(GL_DEPTH_TEST);
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glDisable(GL_LIGHTING);
#if 0
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
#else
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
#endif
            break;
            
        case kRenderState4D:
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            glDisable(GL_CULL_FACE);
            glDisable(GL_POLYGON_SMOOTH);
            glDisable(GL_DEPTH_TEST);
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glDisable(GL_LIGHTING);
#if 0
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
#else
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
#endif
    break;
            
        default:
            throw(MushcoreRequestFail("Invalid RenderState value"));
            break;
    }
}

void
MushGLState::ActiveTextureZeroBased(Mushware::U32 inTexNum)
{
    if (m_activeTexNum != inTexNum)
    {
        MushGLV::Sgl().ActiveTextureZeroBased(inTexNum);
    }
    m_activeTexNum = inTexNum;
}

void
MushGLState::ClientActiveTextureZeroBased(Mushware::U32 inTexNum)
{
    if (m_clientActiveTexNum != inTexNum)
    {
        MushGLV::Sgl().ClientActiveTextureZeroBased(inTexNum);
    }
    m_clientActiveTexNum = inTexNum;
}

void
MushGLState::TextureStateGrow(Mushware::U32 inTexNum)
{
    if (inTexNum <= m_textureStates.size())
    {
        if (inTexNum >= MushGLV::Sgl().NumTextureUnits())
        {
            std::ostringstream message;
            message << "Texture number too high (" << inTexNum << " >= " << MushGLV::Sgl().NumTextureUnits() << ")";
            throw MushcoreRequestFail(message.str());
        }
        m_textureStates.resize(inTexNum+1, kStateNone);
    }
}

void
MushGLState::TextureEnable2D(Mushware::U32 inTexNum)
{
    TextureStateGrow(inTexNum);
    if (m_textureStates[inTexNum] != kStateTrue)
    {
        ActiveTextureZeroBased(inTexNum);
        glEnable(GL_TEXTURE_2D);
        m_textureStates[inTexNum] = kStateTrue;
    }
}    

void
MushGLState::TextureDisable2D(Mushware::U32 inTexNum)
{
    TextureStateGrow(inTexNum);
    if (m_textureStates[inTexNum] != kStateFalse)
    {
        ActiveTextureZeroBased(inTexNum);
        glDisable(GL_TEXTURE_2D);
        m_textureStates[inTexNum] = kStateFalse;
    }
}    

void
MushGLState::DisableClientState(Mushware::U8& ioStateVar, Mushware::U32 inGLState)
{
    if (ioStateVar != kStateFalse)
    {
        glDisableClientState(inGLState);
        ioStateVar = kStateFalse;
    }
}

void
MushGLState::TextureArrayGrow(Mushware::U32 inTexNum)
{
    if (inTexNum <= m_texCoordArrays.size())
    {
        if (inTexNum >= MushGLV::Sgl().NumTextureUnits())
        {
            std::ostringstream message;
            message << "Texture number too high (" << inTexNum << " >= " << MushGLV::Sgl().NumTextureUnits() << ")";
            throw MushcoreRequestFail(message.str());
        }
        m_texCoordArrays.resize(inTexNum+1, kStateNone);
    }
}

void
MushGLState::DisableClientTextureState(Mushware::U32 inTexNum)
{
    TextureArrayGrow(inTexNum);
    if (m_texCoordArrays[inTexNum] != kStateFalse)
    {
        ClientActiveTextureZeroBased(inTexNum);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
    m_texCoordArrays[inTexNum] = kStateFalse;
	m_pCurrentTexCoordBuffer = NULL;
}

void
MushGLState::ColourArraySetTrue(MushGLVertexBuffer<Mushware::t4GLVal>& ioBuffer)
{
    ioBuffer.Bind();
    
    glColorPointer(4, MUSHGL_VALTYPE, 0, ioBuffer.AddrForGLGet());
    
    if (m_colourArray != kStateTrue)
    {
        glEnableClientState(GL_COLOR_ARRAY);
        m_colourArray = kStateTrue;
    }
	m_pCurrentColourBuffer = &ioBuffer;
}

void
MushGLState::TexCoordArraySetTrue(MushGLVertexBuffer<Mushware::tGLTexCoord>& ioBuffer, Mushware::U32 inTexNum)
{
    TextureArrayGrow(inTexNum);
    
    ActiveTextureZeroBased(inTexNum);
    ClientActiveTextureZeroBased(inTexNum);
    
    ioBuffer.Bind();
    
    glTexCoordPointer(2, MUSHGL_VALTYPE, 0, ioBuffer.AddrForGLGet());
    
    MUSHCOREASSERT(inTexNum < m_texCoordArrays.size());
    
    if (m_texCoordArrays[inTexNum] != kStateTrue)
    {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        m_texCoordArrays[inTexNum] = kStateTrue;
    }
	m_pCurrentTexCoordBuffer = &ioBuffer;
}

void
MushGLState::VertexArraySetTrue(MushGLVertexBuffer<Mushware::t4GLVal>& ioBuffer)
{
    ioBuffer.Bind();
    
    glVertexPointer(4, MUSHGL_VALTYPE, 0, ioBuffer.AddrForGLGet());
    
    if (m_vertexArray != kStateTrue)
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        m_vertexArray = kStateTrue;
    }
	m_pCurrentVertexBuffer = &ioBuffer;
}

void
MushGLState::ArraysDisable(void)
{
    ColourArrayDisable();
    EdgeFlagArrayDisable();
    IndexArrayDisable();
    NormalArrayDisable();
    for (Mushware::U32 i=0; i<m_texCoordArrays.size(); ++i)
    {
        TexCoordArrayDisable(i);
    }
    VertexArrayDisable();
}

void
MushGLState::TexturesDisable(void)
{
    for (Mushware::U32 i=0; i<m_textureStates.size(); ++i)
    {
        TextureDisable2D(i);
    }
}

void
MushGLState::ShaderDisable(void)
{
    if (MushGLV::Sgl().HasShader())
    {
        MushGLV::Sgl().UseProgramObject(kGLHandleNull);
    }
}        

//%outOfLineFunctions {

const char *MushGLState::AutoName(void) const
{
    return "MushGLState";
}

MushcoreVirtualObject *MushGLState::AutoClone(void) const
{
    return new MushGLState(*this);
}

MushcoreVirtualObject *MushGLState::AutoCreate(void) const
{
    return new MushGLState;
}

MushcoreVirtualObject *MushGLState::AutoVirtualFactory(void)
{
    return new MushGLState;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLState", MushGLState::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLState::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "colourArray=" << m_colourArray << ", ";
    ioOut << "edgeFlagArray=" << m_edgeFlagArray << ", ";
    ioOut << "indexArray=" << m_indexArray << ", ";
    ioOut << "normalArray=" << m_normalArray << ", ";
    ioOut << "vertexArray=" << m_vertexArray << ", ";
    ioOut << "texCoordArrays=" << m_texCoordArrays << ", ";
    ioOut << "textureStates=" << m_textureStates << ", ";
    ioOut << "activeTexNum=" << m_activeTexNum << ", ";
    ioOut << "clientActiveTexNum=" << m_clientActiveTexNum << ", ";
    ioOut << "standardShader=" << m_standardShader << ", ";
    if (m_pCurrentColourBuffer == NULL)
    {
        ioOut << "pCurrentColourBuffer=NULL"  << ", ";
    }
    else
    {
        ioOut << "pCurrentColourBuffer=" << *m_pCurrentColourBuffer << ", ";
    }
    if (m_pCurrentTexCoordBuffer == NULL)
    {
        ioOut << "pCurrentTexCoordBuffer=NULL"  << ", ";
    }
    else
    {
        ioOut << "pCurrentTexCoordBuffer=" << *m_pCurrentTexCoordBuffer << ", ";
    }
    if (m_pCurrentVertexBuffer == NULL)
    {
        ioOut << "pCurrentVertexBuffer=NULL" ;
    }
    else
    {
        ioOut << "pCurrentVertexBuffer=" << *m_pCurrentVertexBuffer;
    }
    ioOut << "]";
}
bool
MushGLState::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "colourArray")
    {
        ioIn >> m_colourArray;
    }
    else if (inTagStr == "edgeFlagArray")
    {
        ioIn >> m_edgeFlagArray;
    }
    else if (inTagStr == "indexArray")
    {
        ioIn >> m_indexArray;
    }
    else if (inTagStr == "normalArray")
    {
        ioIn >> m_normalArray;
    }
    else if (inTagStr == "vertexArray")
    {
        ioIn >> m_vertexArray;
    }
    else if (inTagStr == "texCoordArrays")
    {
        ioIn >> m_texCoordArrays;
    }
    else if (inTagStr == "textureStates")
    {
        ioIn >> m_textureStates;
    }
    else if (inTagStr == "activeTexNum")
    {
        ioIn >> m_activeTexNum;
    }
    else if (inTagStr == "clientActiveTexNum")
    {
        ioIn >> m_clientActiveTexNum;
    }
    else if (inTagStr == "standardShader")
    {
        ioIn >> m_standardShader;
    }
    else if (inTagStr == "pCurrentColourBuffer")
    {
        ioIn >> m_pCurrentColourBuffer;
    }
    else if (inTagStr == "pCurrentTexCoordBuffer")
    {
        ioIn >> m_pCurrentTexCoordBuffer;
    }
    else if (inTagStr == "pCurrentVertexBuffer")
    {
        ioIn >> m_pCurrentVertexBuffer;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLState::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("colourArray");
    ioOut << m_colourArray;
    ioOut.TagSet("edgeFlagArray");
    ioOut << m_edgeFlagArray;
    ioOut.TagSet("indexArray");
    ioOut << m_indexArray;
    ioOut.TagSet("normalArray");
    ioOut << m_normalArray;
    ioOut.TagSet("vertexArray");
    ioOut << m_vertexArray;
    ioOut.TagSet("texCoordArrays");
    ioOut << m_texCoordArrays;
    ioOut.TagSet("textureStates");
    ioOut << m_textureStates;
    ioOut.TagSet("activeTexNum");
    ioOut << m_activeTexNum;
    ioOut.TagSet("clientActiveTexNum");
    ioOut << m_clientActiveTexNum;
    ioOut.TagSet("standardShader");
    ioOut << m_standardShader;
    ioOut.TagSet("pCurrentColourBuffer");
    ioOut << m_pCurrentColourBuffer;
    ioOut.TagSet("pCurrentTexCoordBuffer");
    ioOut << m_pCurrentTexCoordBuffer;
    ioOut.TagSet("pCurrentVertexBuffer");
    ioOut << m_pCurrentVertexBuffer;
}
//%outOfLineFunctions } Cq3uqh7/l/B4M0/kuQRk0w
