//%includeGuardStart {
#ifndef MUSHMESHPATCHTYPES_H
#define MUSHMESHPATCHTYPES_H
//%includeGuardStart } 61VEPjhxd/HdAqy8k7NbRA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPatchTypes.h
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
//%Header } 75ssAl2TDcDMhL8+fxO7Ug
/*
 * $Id: MushMeshPatchTypes.h,v 1.4 2006/06/01 15:39:31 southa Exp $
 * $Log: MushMeshPatchTypes.h,v $
 * Revision 1.4  2006/06/01 15:39:31  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/05/19 13:02:10  southa
 * Mac release work
 *
 * Revision 1.2  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/19 12:41:42  southa
 * Connectors
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshArray.h"
#include "MushMeshVector.h"

namespace Mushware
{
    enum
    {
        kMushMeshPositionOrder=3,
        kMushMeshNormalOrder=3,
        kMushMeshGeometryCoordOrder = kMushMeshPositionOrder + kMushMeshNormalOrder,
        kMushMeshTexCoordOrder=4,
    };

    typedef Mushware::tVal tGeometryCoordValue; 
    typedef Mushware::tVal tTexCoordValue;
    typedef MushMeshVector<tGeometryCoordValue, kMushMeshGeometryCoordOrder> tGeometryVector;
    typedef MushMeshArray<tGeometryVector> tGeometryArray;
    typedef MushMeshVector<tTexCoordValue, kMushMeshTexCoordOrder> tTexCoordVector;
    typedef MushMeshArray<tTexCoordVector> tTexCoordArray;
    typedef std::vector<tTexCoordArray> tTexCoordArrayVector;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
