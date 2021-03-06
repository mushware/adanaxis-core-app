//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisSaveData.cpp
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
//%Header } wJd26Ge/I945f5EPGV6fIg
/*
 * $Id: AdanaxisSaveData.cpp,v 1.23 2007/06/13 14:08:48 southa Exp $
 * $Log: AdanaxisSaveData.cpp,v $
 * Revision 1.23  2007/06/13 14:08:48  southa
 * Level 29
 *
 * Revision 1.22  2007/06/07 13:23:03  southa
 * Level 24
 *
 * Revision 1.21  2007/05/10 14:06:26  southa
 * Level 16 and retina spin
 *
 * Revision 1.20  2007/04/21 09:41:06  southa
 * Level work
 *
 * Revision 1.19  2007/04/18 09:22:04  southa
 * Header and level fixes
 *
 * Revision 1.18  2007/04/16 08:41:09  southa
 * Level and header mods
 *
 * Revision 1.17  2007/03/20 17:31:24  southa
 * Difficulty and GL options
 *
 * Revision 1.16  2006/11/03 18:46:33  southa
 * Damage effectors
 *
 * Revision 1.15  2006/10/19 15:41:36  southa
 * Item handling
 *
 * Revision 1.14  2006/08/01 17:21:29  southa
 * River demo
 *
 * Revision 1.13  2006/07/31 11:01:36  southa
 * Music and dialogues
 *
 * Revision 1.12  2006/07/28 11:14:27  southa
 * Records for multiple spaces
 *
 * Revision 1.11  2006/07/27 13:51:34  southa
 * Menu and control fixes
 *
 * Revision 1.10  2006/06/01 15:38:48  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/07/29 14:59:49  southa
 * Maptor access
 *
 * Revision 1.8  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.7  2005/07/12 12:18:17  southa
 * Projectile work
 *
 * Revision 1.6  2005/07/02 00:42:36  southa
 * Conditioning tweaks
 *
 * Revision 1.5  2005/06/30 14:26:35  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.3  2005/06/20 14:30:33  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/16 17:25:37  southa
 * Client/server work
 *
 * Revision 1.1  2005/06/14 20:39:40  southa
 * Adanaxis work
 *
 */

#include "AdanaxisSaveData.h"

AdanaxisSaveData::AdanaxisSaveData() :
    m_clockStarted(false),
    m_retinaSpin(0.0),
    m_permanentSpin(false),
    m_permanentThrust(false),
    m_speedAugmentation(false)
{
}

//%outOfLineFunctions {

const char *AdanaxisSaveData::AutoName(void) const
{
    return "AdanaxisSaveData";
}

MushcoreVirtualObject *AdanaxisSaveData::AutoClone(void) const
{
    throw MushcoreRequestFail("Cannot clone 'AdanaxisSaveData'");;
}

MushcoreVirtualObject *AdanaxisSaveData::AutoCreate(void) const
{
    return new AdanaxisSaveData;
}

MushcoreVirtualObject *AdanaxisSaveData::AutoVirtualFactory(void)
{
    return new AdanaxisSaveData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisSaveData", AdanaxisSaveData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisSaveData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameSaveData::AutoPrint(ioOut);
    ioOut << "projectileList=" << m_projectileList << ", ";
    ioOut << "khaziList=" << m_khaziList << ", ";
    ioOut << "itemList=" << m_itemList << ", ";
    ioOut << "effectorList=" << m_effectorList << ", ";
    ioOut << "clockStarted=" << m_clockStarted << ", ";
    ioOut << "spaceName=" << m_spaceName << ", ";
    ioOut << "gameDifficulty=" << m_gameDifficulty << ", ";
    ioOut << "primaryType=" << m_primaryType << ", ";
    ioOut << "retinaSpin=" << m_retinaSpin << ", ";
    ioOut << "permanentSpin=" << m_permanentSpin << ", ";
    ioOut << "permanentThrust=" << m_permanentThrust << ", ";
    ioOut << "speedAugmentation=" << m_speedAugmentation;
    ioOut << "]";
}
bool
AdanaxisSaveData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "projectileList")
    {
        ioIn >> m_projectileList;
    }
    else if (inTagStr == "khaziList")
    {
        ioIn >> m_khaziList;
    }
    else if (inTagStr == "itemList")
    {
        ioIn >> m_itemList;
    }
    else if (inTagStr == "effectorList")
    {
        ioIn >> m_effectorList;
    }
    else if (inTagStr == "clockStarted")
    {
        ioIn >> m_clockStarted;
    }
    else if (inTagStr == "spaceName")
    {
        ioIn >> m_spaceName;
    }
    else if (inTagStr == "gameDifficulty")
    {
        ioIn >> m_gameDifficulty;
    }
    else if (inTagStr == "primaryType")
    {
        ioIn >> m_primaryType;
    }
    else if (inTagStr == "retinaSpin")
    {
        ioIn >> m_retinaSpin;
    }
    else if (inTagStr == "permanentSpin")
    {
        ioIn >> m_permanentSpin;
    }
    else if (inTagStr == "permanentThrust")
    {
        ioIn >> m_permanentThrust;
    }
    else if (inTagStr == "speedAugmentation")
    {
        ioIn >> m_speedAugmentation;
    }
    else if (MushGameSaveData::AutoXMLDataProcess(ioIn, inTagStr))
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
AdanaxisSaveData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameSaveData::AutoXMLPrint(ioOut);
    ioOut.TagSet("projectileList");
    ioOut << m_projectileList;
    ioOut.TagSet("khaziList");
    ioOut << m_khaziList;
    ioOut.TagSet("itemList");
    ioOut << m_itemList;
    ioOut.TagSet("effectorList");
    ioOut << m_effectorList;
    ioOut.TagSet("clockStarted");
    ioOut << m_clockStarted;
    ioOut.TagSet("spaceName");
    ioOut << m_spaceName;
    ioOut.TagSet("gameDifficulty");
    ioOut << m_gameDifficulty;
    ioOut.TagSet("primaryType");
    ioOut << m_primaryType;
    ioOut.TagSet("retinaSpin");
    ioOut << m_retinaSpin;
    ioOut.TagSet("permanentSpin");
    ioOut << m_permanentSpin;
    ioOut.TagSet("permanentThrust");
    ioOut << m_permanentThrust;
    ioOut.TagSet("speedAugmentation");
    ioOut << m_speedAugmentation;
}
//%outOfLineFunctions } Ci9HvrzWE7BpRwFFLu/c0w
