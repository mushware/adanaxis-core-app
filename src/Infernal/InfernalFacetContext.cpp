//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalFacetContext.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Sm2dksqO3j2Rsr1/+cPdyw
/*
 * $Id: InfernalFacetContext.cpp,v 1.1 2004/01/10 20:29:34 southa Exp $
 * $Log: InfernalFacetContext.cpp,v $
 * Revision 1.1  2004/01/10 20:29:34  southa
 * Form and rendering work
 *
 */

#include "InfernalFacetContext.h"

#include "mushMushcoreIO.h"

using namespace Mushware;
using namespace std;

void
InfernalFacetContext::RenderTypeImport(const std::string& inName)
{
    if (inName == "points")
    {
        m_renderType=GL_POINTS;
    }
    else if (inName == "linestrip")
    {
        m_renderType=GL_LINE_STRIP;
    }
    else if (inName == "lineloop")
    {
        m_renderType=GL_LINE_LOOP;
    }
    else if (inName == "lines")
    {
        m_renderType=GL_LINES;
    }
    else if (inName == "trianglestrip")
    {
        m_renderType=GL_TRIANGLE_STRIP;
    }
    else if (inName == "trianglefan")
    {
        m_renderType=GL_TRIANGLE_FAN;
    }
    else if (inName == "triangles")
    {
        m_renderType=GL_TRIANGLES;
    }
    else if (inName == "quadstrip")
    {
        m_renderType=GL_QUAD_STRIP;
    }
    else if (inName == "quads")
    {
        m_renderType=GL_QUADS;
    }
    else if (inName == "polygon")
    {
        m_renderType=GL_POLYGON;
    }
    else
    {
        throw MushcoreDataFail("Unknown rendering type '"+inName+"'");
    }
}

void
InfernalFacetContext::VerticesImport(const std::vector<Mushware::t3Val>& inVertices)
{
    U32 inputSize=inVertices.size();
    m_vertices.resize(inputSize*3);
    std::vector<GLfloat>::iterator p = m_vertices.begin();
    for (U32 i=0; i<inputSize; ++i)
    {
        for (U32 j=0; j<3; ++j)
        {
            *p = inVertices[i].Get(j);
            ++p;
        }
    }
    MUSHCOREASSERT(p == m_vertices.end());
}
//%outOfLineFunctions {

const char *InfernalFacetContext::AutoNameGet(void) const
{
    return "InfernalFacetContext";
}

MushcoreVirtualObject *InfernalFacetContext::AutoClone(void) const
{
    return new InfernalFacetContext(*this);
}

MushcoreVirtualObject *InfernalFacetContext::AutoCreate(void) const
{
    return new InfernalFacetContext;
}

MushcoreVirtualObject *InfernalFacetContext::AutoVirtualFactory(void)
{
    return new InfernalFacetContext;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("InfernalFacetContext", InfernalFacetContext::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
InfernalFacetContext::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "textureRef=" << m_textureRef << ", ";
    ioOut << "listContextNum=" << m_listContextNum << ", ";
    ioOut << "listName=" << m_listName << ", ";
    ioOut << "renderType=" << m_renderType << ", ";
    ioOut << "arraySize=" << m_arraySize << ", ";
    ioOut << "vertices=" << m_vertices << ", ";
    ioOut << "texCoords=" << m_texCoords << ", ";
    ioOut << "normals=" << m_normals << ", ";
    ioOut << "contextValid=" << m_contextValid;
    ioOut << "]";
}
bool
InfernalFacetContext::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "textureRef")
    {
        ioIn >> m_textureRef;
    }
    else if (inTagStr == "listContextNum")
    {
        ioIn >> m_listContextNum;
    }
    else if (inTagStr == "listName")
    {
        ioIn >> m_listName;
    }
    else if (inTagStr == "renderType")
    {
        ioIn >> m_renderType;
    }
    else if (inTagStr == "arraySize")
    {
        ioIn >> m_arraySize;
    }
    else if (inTagStr == "vertices")
    {
        ioIn >> m_vertices;
    }
    else if (inTagStr == "texCoords")
    {
        ioIn >> m_texCoords;
    }
    else if (inTagStr == "normals")
    {
        ioIn >> m_normals;
    }
    else if (inTagStr == "contextValid")
    {
        ioIn >> m_contextValid;
    }
    else
    {
        return false;
    }
    return true;
}
void
InfernalFacetContext::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("textureRef");
    ioOut << m_textureRef;
    ioOut.TagSet("listContextNum");
    ioOut << m_listContextNum;
    ioOut.TagSet("listName");
    ioOut << m_listName;
    ioOut.TagSet("renderType");
    ioOut << m_renderType;
    ioOut.TagSet("arraySize");
    ioOut << m_arraySize;
    ioOut.TagSet("vertices");
    ioOut << m_vertices;
    ioOut.TagSet("texCoords");
    ioOut << m_texCoords;
    ioOut.TagSet("normals");
    ioOut << m_normals;
    ioOut.TagSet("contextValid");
    ioOut << m_contextValid;
}
//%outOfLineFunctions } ZjEBBfa8cx9qwqlyIFiFwg
