//%includeGuardStart {
#ifndef MUSHMESHPATCHPIPE_H
#define MUSHMESHPATCHPIPE_H
//%includeGuardStart } gemvGRbDI5PU4GuNRmK/yQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPatchPipe.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } wf0zYB3KZvgawo6JSeNBUQ

#include "MushMeshStandard.h"

#include "MushMeshArray.h"
#include "MushMeshBox.h"
#include "MushMeshPatch.h"
#include "MushMeshPatchTypes.h"
#include "MushMeshSelection.h"
#include "MushMeshStitchable.h"
#include "MushMeshVector.h"
#include "MushMeshWorkspaceBased.h"

//:generate ostream
class MushMeshPatchPipe : public MushMeshPatch
{
public:
    typedef Mushware::t2BoxU32 tActiveBox;

    virtual const Mushware::tGeometryArray& GeometryGet(void);
    virtual void GeometrySet(const Mushware::tGeometryArray& inArray);
    virtual const Mushware::tTexCoordArray& TexCoordGet(Mushware::U32 inIndex);
    virtual void TexCoordSet(const Mushware::tTexCoordArray& inArray, Mushware::U32 inIndex);

    // virtual void Render(void /* some render context */) = 0;
    virtual void Subdivide(Mushware::tVal inLevel);

    virtual void EdgeStitchableGet(MushMeshStitchable& outStitchable, tEdgeSelector inEdge);

    virtual void NeighbourSet(const MushMeshStitchable& inStitchable, tEdgeSelector inEdge);

protected:
    virtual void NeighbourSelectionGet(MushMeshSelection& outSelection, tEdgeSelector inEdge);

private:

    MushMeshWorkspaceBased<Mushware::tGeometryArray> m_geometry;
    
    MushMeshWorkspaceBased<Mushware::tTexCoordArrayVector> m_texCoords;

    tActiveBox m_activeBox;

    std::vector<MushMeshSelection> m_edgeDefs;
    std::vector<MushMeshSelection> m_neighbourDefs;

//%classPrototypes {
public:
    void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } igNZsqh+Ffme42HZCDZW6Q
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshPatchPipe& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } kYQL8EqY9bCHCgXqtHxUig
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
