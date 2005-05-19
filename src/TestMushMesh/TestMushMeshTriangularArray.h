//%includeGuardStart {
#ifndef TESTMUSHMESHTRIANGULARARRAY_H
#define TESTMUSHMESHTRIANGULARARRAY_H
//%includeGuardStart } lyinEX4LVI++dsjzRARngQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshTriangularArray.h
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
//%Header } mpDZjcoC+N4HErLx57yRNQ
/*
 * $Id: TestMushMeshTriangularArray.h,v 1.2 2004/01/02 21:13:17 southa Exp $
 * $Log: TestMushMeshTriangularArray.h,v $
 * Revision 1.2  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/23 20:03:59  southa
 * End mesh work
 *
 * Revision 1.5  2003/10/20 13:02:55  southa
 * Patch fixes and testing
 *
 * Revision 1.4  2003/10/17 19:33:11  southa
 * Mesh patches
 *
 * Revision 1.3  2003/10/15 12:23:10  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.2  2003/10/15 11:54:54  southa
 * MushMeshArray neighbour testing and subdivision
 *
 * Revision 1.1  2003/10/15 07:08:29  southa
 * MushMeshArray creation
 *
 */

#include "TestMushMeshStandard.h"

class TestMushMeshTriangularArray
{
public:
    static MushcoreScalar TestTriangularArray(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

private:
    enum
    {
        kXMax = 5,
        kOrder = 3
    };

    static void ArrayVerify(const MushMeshTriangularArray<Mushware::U32>& inArray, const std::string& inName);
    static Mushware::U32 ValueFunction(Mushware::U32 inX, Mushware::U32 inY);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
