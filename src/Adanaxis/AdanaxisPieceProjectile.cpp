//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceProjectile.cpp
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
//%Header } AKn0HlU4NeCX3ptHFWodSQ
/*
 * $Id: AdanaxisPieceProjectile.cpp,v 1.9 2006/07/24 18:46:47 southa Exp $
 * $Log: AdanaxisPieceProjectile.cpp,v $
 * Revision 1.9  2006/07/24 18:46:47  southa
 * Depth sorting
 *
 * Revision 1.8  2006/07/19 14:34:51  southa
 * Flare effects
 *
 * Revision 1.7  2006/06/30 15:05:32  southa
 * Texture and buffer purge
 *
 * Revision 1.6  2006/06/21 12:17:55  southa
 * Ruby object generation
 *
 * Revision 1.5  2006/06/01 15:38:48  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/08/01 13:09:57  southa
 * Collision messaging
 *
 * Revision 1.3  2005/07/19 10:08:06  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.1  2005/07/12 12:18:17  southa
 * Projectile work
 *
 */

#include "AdanaxisPieceProjectile.h"

#include "AdanaxisUtil.h"

using namespace Mushware;
using namespace std;

AdanaxisPieceProjectile::AdanaxisPieceProjectile(const std::string& inID) :
    MushGamePiece(inID),
    m_initialVelocity(1),
    m_lifeMsec(10000),
    m_moveCtr(0)
{
}

void
AdanaxisPieceProjectile::Move(MushGameLogic& ioLogic, const tVal inFrameslice)
{
    if (m_moveCtr == 0)
    {

    }
    
    PostWRef().InPlaceVelocityAdd();
    if (ioLogic.FrameMsec() > m_expiryMsec)
    {
        Explode(ioLogic);
        ExpireFlagSet(true);
    }

    m_moveCtr++;
}

bool
AdanaxisPieceProjectile::Render(MushGLJobRender& outRender,
    MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera)
{
    MushRenderSpec renderSpec;
    renderSpec.BuffersRefSet(BuffersRef());
    renderSpec.TexCoordBuffersRefSet(TexCoordBuffersRef());
    
    MushMeshOps::PosticityToMattress(renderSpec.ModelWRef(), Post());
    MushMeshOps::PosticityToMattress(renderSpec.ViewWRef(), inCamera.Post());
    renderSpec.ViewWRef().InPlaceInvert();
    
    renderSpec.ProjectionSet(inCamera.Projection());
    
    bool jobCreated = inRender.RenderJobCreate(outRender, renderSpec, Mesh());
    return jobCreated;
}

void
AdanaxisPieceProjectile::CollisionFatalConsume(MushGameLogic& ioLogic, const MushGameMessageCollisionFatal& inMessage)
{
    Explode(ioLogic);
    ExpireFlagSet(true);
}    

void
AdanaxisPieceProjectile::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    const MushGameMessageCollisionFatal *pCollisionFatal;
    
    if ((pCollisionFatal = dynamic_cast<const MushGameMessageCollisionFatal *>(&inMessage)) != NULL)
    {
        CollisionFatalConsume(ioLogic, *pCollisionFatal);
    }
    else
    {
        // Pass to base class
        MushGamePiece::MessageConsume(ioLogic, inMessage);
    }
}

void
AdanaxisPieceProjectile::Explode(MushGameLogic& ioLogic)
{
    MushMeshPosticity flarePost = Post();
    flarePost.VelWRef().ToAdditiveIdentitySet();
    
    AdanaxisUtil::FlareCreate(dynamic_cast<AdanaxisLogic&>(ioLogic), flarePost, 3, 0);
    for (U32 i=0; i<3; ++i)
    {
        AdanaxisUtil::EmberCreate(dynamic_cast<AdanaxisLogic&>(ioLogic),
                                  Post(),
                                  MushMeshTools::Random(0.1, 0.4), // size
                                  MushMeshTools::Random(0.1, 1)  // speed
                                  );
    }
}

//%outOfLineFunctions {

const char *AdanaxisPieceProjectile::AutoName(void) const
{
    return "AdanaxisPieceProjectile";
}

MushcoreVirtualObject *AdanaxisPieceProjectile::AutoClone(void) const
{
    return new AdanaxisPieceProjectile(*this);
}

MushcoreVirtualObject *AdanaxisPieceProjectile::AutoCreate(void) const
{
    return new AdanaxisPieceProjectile;
}

MushcoreVirtualObject *AdanaxisPieceProjectile::AutoVirtualFactory(void)
{
    return new AdanaxisPieceProjectile;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisPieceProjectile", AdanaxisPieceProjectile::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisPieceProjectile::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGamePiece::AutoPrint(ioOut);
    ioOut << "owner=" << m_owner << ", ";
    ioOut << "initialVelocity=" << m_initialVelocity << ", ";
    ioOut << "lifeMsec=" << m_lifeMsec << ", ";
    ioOut << "expiryMsec=" << m_expiryMsec << ", ";
    ioOut << "moveCtr=" << m_moveCtr;
    ioOut << "]";
}
bool
AdanaxisPieceProjectile::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "owner")
    {
        ioIn >> m_owner;
    }
    else if (inTagStr == "initialVelocity")
    {
        ioIn >> m_initialVelocity;
    }
    else if (inTagStr == "lifeMsec")
    {
        ioIn >> m_lifeMsec;
    }
    else if (inTagStr == "expiryMsec")
    {
        ioIn >> m_expiryMsec;
    }
    else if (inTagStr == "moveCtr")
    {
        ioIn >> m_moveCtr;
    }
    else if (MushGamePiece::AutoXMLDataProcess(ioIn, inTagStr))
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
AdanaxisPieceProjectile::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGamePiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("owner");
    ioOut << m_owner;
    ioOut.TagSet("initialVelocity");
    ioOut << m_initialVelocity;
    ioOut.TagSet("lifeMsec");
    ioOut << m_lifeMsec;
    ioOut.TagSet("expiryMsec");
    ioOut << m_expiryMsec;
    ioOut.TagSet("moveCtr");
    ioOut << m_moveCtr;
}
//%outOfLineFunctions } +aZ4m66cvd68PwWcqvFUgg
