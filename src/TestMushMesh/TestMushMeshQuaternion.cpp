//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshQuaternion.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Y0heUUMv/8rG89Ya6G1wZg
/*
 * $Id$
 * $Log$
 */

#include "TestMushMeshQuaternion.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshQuaternion(TestMushMeshQuaternion::Install);

void
TestMushMeshQuaternion::RandomRotationGet(t4x4Val& outMatrix, tVal inSeed)
{
    t4x4Val aMatrix =
        t4x4Val(t4Val( cos(2*inSeed), -sin(2*inSeed),              0,             0),
                t4Val( sin(2*inSeed),  cos(2*inSeed),              0,             0),
                t4Val(             0,              0,  cos(5*inSeed), -sin(5*inSeed)),
                t4Val(             0,              0,  sin(5*inSeed),  cos(5*inSeed))
                );
  
    t4x4Val bMatrix =
        t4x4Val(t4Val( cos(3*inSeed), -sin(3*inSeed),              0,             0),
                t4Val( sin(3*inSeed),  cos(3*inSeed),              0,             0),
                t4Val(             0,              0,  cos(7*inSeed), -sin(7*inSeed)),
                t4Val(             0,              0,  sin(7*inSeed),  cos(7*inSeed))
                );
    
    outMatrix = aMatrix * bMatrix;                
}

MushcoreScalar
TestMushMeshQuaternion::TestQuaternion(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    tQVal aQuat(7, 5, 3, 1);
    tQVal bQuat, cQuat;
    tVal length = std::sqrt(7*7+5*5+3*3+1.0);
    tQVal resultQuat(7/length, 5/length, 3/length, 1/length);
    
    MushMeshOps::Normalise(aQuat);
    
    if (resultQuat != aQuat)
    {
        ostringstream message;
        message << "Normalise failed : Normalise(" << aQuat << ") != " << resultQuat;
        throw MushcoreLogicFail(message.str());
    }
    
    aQuat = tQVal(1, 2, 3, 4);
    bQuat = tQVal(5, 6, 7, 8);
    
    resultQuat = tQVal(1*5-2*6-3*7-4*8,
                       1*6+2*5+3*8-4*7,
                       1*7+3*5-2*8+4*6,
                       1*8+4*5+2*7-3*6);
    
    if (aQuat * bQuat != resultQuat)
    {
        ostringstream message;
        message << "operator tQVal * tQVal failed : " << aQuat << " * " << bQuat << " == " << aQuat * bQuat;
        message << " (expected " << resultQuat << ")";
        throw MushcoreLogicFail(message.str());
    }
    
    cQuat = aQuat;
    cQuat.PostMultiplyBy(bQuat);
    
    if (cQuat != resultQuat)
    {
        ostringstream message;
        message << "Quat.PostMultiplyBy failed : " << aQuat << ".PostMultiplyBy(" << bQuat << ") == " << cQuat;
        message << " (expected " << resultQuat << ")";
        throw MushcoreLogicFail(message.str());
    }
    
    cQuat = bQuat;
    cQuat.PreMultiplyBy(aQuat);
    
    if (cQuat != resultQuat)
    {
        ostringstream message;
        message << "Quat.PreMultiplyBy failed : " << bQuat << ".PreMultiplyBy(" << aQuat << ") == " << cQuat;
        message << " (expected " << resultQuat << ")";
        throw MushcoreLogicFail(message.str());
    }
    
    tQValPair aQuatPair;
    
    return MushcoreScalar(0);
}

void
TestMushMeshQuaternion::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmeshrquaternion", TestQuaternion);
}
