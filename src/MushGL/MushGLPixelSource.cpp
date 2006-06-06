//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLPixelSource.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } vz1knUYnzwX5FNm6RC5EZw
/*
 * $Id: MushGLPixelSource.cpp,v 1.6 2006/05/02 17:32:13 southa Exp $
 * $Log: MushGLPixelSource.cpp,v $
 * Revision 1.6  2006/05/02 17:32:13  southa
 * Texturing
 *
 * Revision 1.5  2005/08/28 22:41:51  southa
 * MushGLTexture work
 *
 * Revision 1.4  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.3  2005/06/16 17:25:39  southa
 * Client/server work
 *
 * Revision 1.2  2005/05/19 13:02:09  southa
 * Mac release work
 *
 * Revision 1.1  2005/02/13 22:44:07  southa
 * Tesseract stuff
 *
 */

#include "MushGLPixelSource.h"

#include "MushGLResolverPixelSource.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(MushGLPixelSource);

MUSHCORE_INSTALLER(MushGLPixelSource::Install);

MushGLPixelSource::MushGLPixelSource() :
    m_storageType("GL")
{
}

void
MushGLPixelSource::ValueParameterSet(Mushware::U32 inNum, Mushware::tLongVal inVal)
{
    ostringstream message;
    message << "MushGLPixelSource::ValueParameterSet: Unknown parameter: " << inNum;
    throw MushcoreRequestFail(message.str());
}

void
MushGLPixelSource::StringParameterSet(Mushware::U32 inNum, const std::string& inStr)
{
    switch (inNum)
    {
        case kParamStorageType:
            m_storageType = inStr;
            break;
            
        default:   
            ostringstream message;
            message << "MushGLPixelSource::StringParameterSet: Unknown parameter: " << inNum;
            throw MushcoreRequestFail(message.str());
            break;
    }
}

void
MushGLPixelSource::ParamDecode(const MushRubyValue& inName, const MushRubyValue& inValue)
{
	std::string nameStr = inName.String();
	
	if (nameStr == "name" || nameStr == "type")
    {
		// Ignore - already handled by the resolver
	}
	else if (nameStr == "storagetype")
	{
		m_storageType = inValue.String();
	}
	else if (nameStr == "size")
	{
		m_size = t4Val(inValue.ValVector());
	}
	else
	{
	    throw MushcoreSyntaxFail("Texture parameter '"+nameStr+"' not known by this texture type");	
	}
}

void
MushGLPixelSource::ParamHashDecode(const Mushware::tRubyHash& inHash)
{
    tRubyHash::const_iterator endIter = inHash.end();
    for (tRubyHash::const_iterator p = inHash.begin(); p != endIter; ++p)
    {
		ParamDecode(p->first, p->second);
	}
}

void
MushGLPixelSource::BufferFill(Mushware::U32 * const outPtr, const Mushware::t2U32 inSize) const
{
    throw MushcoreRequestFail("Cannot fill buffer from this pixel source");
}

void
MushGLPixelSource::ToTextureCreate(MushGLTexture& outTexture)
{
    throw MushcoreRequestFail("Cannot create texture from this pixel source");
}

void
MushGLPixelSource::Install(void)
{
	MushGLResolverPixelSource::Sgl().PrefixAdd("MushGLPixelSource");
}

//%outOfLineFunctions {
void
MushGLPixelSource::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "storageType=" << m_storageType << ", ";
    ioOut << "size=" << m_size;
    ioOut << "]";
}
bool
MushGLPixelSource::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "storageType")
    {
        ioIn >> m_storageType;
    }
    else if (inTagStr == "size")
    {
        ioIn >> m_size;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLPixelSource::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("storageType");
    ioOut << m_storageType;
    ioOut.TagSet("size");
    ioOut << m_size;
}
//%outOfLineFunctions } YbNcJD9YtJWUOuroVDIZmQ
