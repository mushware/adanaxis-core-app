//%includeGuardStart {
#ifndef MUSHRENDERMESHWIREFRAME_H
#define MUSHRENDERMESHWIREFRAME_H
//%includeGuardStart } yWUi9oXnokdSM/hurSycsQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderMeshWireframe.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } tS7SXrOHlPA5Gu5Vj1LZkg
/*
 * $Id: MushRenderMeshWireframe.h,v 1.1 2005/07/04 11:10:43 southa Exp $
 * $Log: MushRenderMeshWireframe.h,v $
 * Revision 1.1  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 */

#include "MushRenderStandard.h"

#include "MushRenderMesh.h"

class MushRenderMeshWireframe : public MushRenderMesh
{
public:
    typedef std::vector<Mushware::t4x4Val> tVertices;
    virtual ~MushRenderMeshWireframe() {}

    virtual void MeshRender(const MushRenderSpec& inSpec, const MushMeshMesh& inMesh);
    
private:
    bool OutputBufferGenerate(const MushRenderSpec& inSpec, const MushMeshMesh& inMesh);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
