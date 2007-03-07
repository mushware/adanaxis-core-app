//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisVolatileData.cpp
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } zadk8cle2hIJ/tR0KH/bYw
/*
 * $Id: AdanaxisVolatileData.cpp,v 1.11 2006/11/12 20:09:55 southa Exp $
 * $Log: AdanaxisVolatileData.cpp,v $
 * Revision 1.11  2006/11/12 20:09:55  southa
 * Missile guidance
 *
 * Revision 1.10  2006/08/01 17:21:30  southa
 * River demo
 *
 * Revision 1.9  2006/07/28 16:52:19  southa
 * Options work
 *
 * Revision 1.8  2006/07/26 16:37:21  southa
 * Options menu
 *
 * Revision 1.7  2006/07/19 10:22:15  southa
 * World objects
 *
 * Revision 1.6  2006/07/04 16:55:26  southa
 * Ruby key handling
 *
 * Revision 1.5  2006/07/02 21:08:54  southa
 * Ruby menu work
 *
 */

#include "AdanaxisVolatileData.h"

AdanaxisVolatileData::AdanaxisVolatileData() :
    m_rubySpace(Mushware::kRubyQnil),
    m_scannerOn(false)
{
}

//%outOfLineFunctions {

const char *AdanaxisVolatileData::AutoName(void) const
{
    return "AdanaxisVolatileData";
}

MushcoreVirtualObject *AdanaxisVolatileData::AutoClone(void) const
{
    throw MushcoreRequestFail("Cannot clone 'AdanaxisVolatileData'");;
}

MushcoreVirtualObject *AdanaxisVolatileData::AutoCreate(void) const
{
    return new AdanaxisVolatileData;
}

MushcoreVirtualObject *AdanaxisVolatileData::AutoVirtualFactory(void)
{
    return new AdanaxisVolatileData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisVolatileData", AdanaxisVolatileData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisVolatileData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameVolatileData::AutoPrint(ioOut);
    ioOut << "decoList=" << m_decoList << ", ";
    ioOut << "worldList=" << m_worldList << ", ";
    ioOut << "aRenderMesh=" << m_aRenderMesh << ", ";
    ioOut << "rubySpace=" << m_rubySpace << ", ";
    ioOut << "brightness=" << m_brightness << ", ";
    ioOut << "scannerOn=" << m_scannerOn << ", ";
    ioOut << "playerTargetID=" << m_playerTargetID << ", ";
    ioOut << "khaziCount=" << m_khaziCount << ", ";
    ioOut << "playerCount=" << m_playerCount;
    ioOut << "]";
}
bool
AdanaxisVolatileData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "decoList")
    {
        ioIn >> m_decoList;
    }
    else if (inTagStr == "worldList")
    {
        ioIn >> m_worldList;
    }
    else if (inTagStr == "aRenderMesh")
    {
        ioIn >> m_aRenderMesh;
    }
    else if (inTagStr == "rubySpace")
    {
        ioIn >> m_rubySpace;
    }
    else if (inTagStr == "brightness")
    {
        ioIn >> m_brightness;
    }
    else if (inTagStr == "scannerOn")
    {
        ioIn >> m_scannerOn;
    }
    else if (inTagStr == "playerTargetID")
    {
        ioIn >> m_playerTargetID;
    }
    else if (inTagStr == "khaziCount")
    {
        ioIn >> m_khaziCount;
    }
    else if (inTagStr == "playerCount")
    {
        ioIn >> m_playerCount;
    }
    else if (MushGameVolatileData::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
AdanaxisVolatileData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameVolatileData::AutoXMLPrint(ioOut);
    ioOut.TagSet("decoList");
    ioOut << m_decoList;
    ioOut.TagSet("worldList");
    ioOut << m_worldList;
    ioOut.TagSet("aRenderMesh");
    ioOut << m_aRenderMesh;
    ioOut.TagSet("rubySpace");
    ioOut << m_rubySpace;
    ioOut.TagSet("brightness");
    ioOut << m_brightness;
    ioOut.TagSet("scannerOn");
    ioOut << m_scannerOn;
    ioOut.TagSet("playerTargetID");
    ioOut << m_playerTargetID;
    ioOut.TagSet("khaziCount");
    ioOut << m_khaziCount;
    ioOut.TagSet("playerCount");
    ioOut << m_playerCount;
}
//%outOfLineFunctions } noJAi2lAxJgmvs5gpWZXIA
