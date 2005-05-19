//%includeGuardStart {
#ifndef TESTMUSHMESHPOSTMATRIX_H
#define TESTMUSHMESHPOSTMATRIX_H
//%includeGuardStart } 7Lxc5UoUlhH7X+YSVRetNg
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshPostMatrix.h
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
//%Header } Hfypx//33ernWQcnyippuA
/*
 * $Id: TestMushMeshPostMatrix.h,v 1.1 2004/12/06 20:44:18 southa Exp $
 * $Log: TestMushMeshPostMatrix.h,v $
 * Revision 1.1  2004/12/06 20:44:18  southa
 * Quaternion and matrix operations
 *
 */
#include "TestMushMeshStandard.h"

class TestMushMeshPostMatrix
{
public:
    static MushcoreScalar TestPostMatrix(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
