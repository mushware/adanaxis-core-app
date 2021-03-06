//%includeGuardStart {
#ifndef MUSHGLPROJECTION_H
#define MUSHGLPROJECTION_H
//%includeGuardStart } T38RsetZbekqaRFJwoUBnw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLProjection.h
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
//%Header } itz+rhPs5v6TlmqRESJnWA
/*
 * $Id: MushGLProjection.h,v 1.6 2006/07/25 20:31:04 southa Exp $
 * $Log: MushGLProjection.h,v $
 * Revision 1.6  2006/07/25 20:31:04  southa
 * Scanner work
 *
 * Revision 1.5  2006/07/24 18:46:49  southa
 * Depth sorting
 *
 * Revision 1.4  2006/06/01 15:39:18  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/05 16:35:53  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 * Revision 1.1  2005/07/01 10:03:30  southa
 * Projection work
 *
 */

#include "MushGLStandard.h"

//:generate virtual standard ostream xml1
class MushGLProjection : public MushcoreVirtualObject
{
public:
    MushGLProjection() : m_viewHalfRadians(0) {}
    virtual ~MushGLProjection() {}
    
    virtual void FromAspectNearFarMake(Mushware::tVal inAspect, Mushware::tVal inNear, Mushware::tVal inFar);
    virtual Mushware::tVal FValue(void) const { return FValueFromViewHalfRadians(m_viewHalfRadians); }
    virtual Mushware::tVal XHalfAngle(void) const;
    virtual Mushware::tVal YHalfAngle(void) const { return m_viewHalfRadians; }
    
    void TransformVector(Mushware::t4Val& ioVec) const;
    Mushware::t4Val TransformedVector(const Mushware::t4Val& ioVec) const;

protected:
    virtual Mushware::tVal FValueFromViewHalfRadians(Mushware::tVal inRadians) const;

private:
    Mushware::tVal m_viewHalfRadians; //:readwrite
    Mushware::t4x4o4Val m_mattress; //:readwrite :wref
    Mushware::t4Val m_clipMin; //:read
    Mushware::t4Val m_clipMax; //:read
    Mushware::t4Val m_boundingRadiusFactor; //:read
    Mushware::tVal m_aspectRatio; //:read
    
//%classPrototypes {
public:
    const Mushware::tVal& ViewHalfRadians(void) const { return m_viewHalfRadians; }
    void ViewHalfRadiansSet(const Mushware::tVal& inValue) { m_viewHalfRadians=inValue; }
    const Mushware::t4x4o4Val& Mattress(void) const { return m_mattress; }
    void MattressSet(const Mushware::t4x4o4Val& inValue) { m_mattress=inValue; }
    // Writable reference for m_mattress
    Mushware::t4x4o4Val& MattressWRef(void) { return m_mattress; }
    const Mushware::t4Val& ClipMin(void) const { return m_clipMin; }
    const Mushware::t4Val& ClipMax(void) const { return m_clipMax; }
    const Mushware::t4Val& BoundingRadiusFactor(void) const { return m_boundingRadiusFactor; }
    const Mushware::tVal& AspectRatio(void) const { return m_aspectRatio; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } yGAMx4wZMhlqhtOqqKnjVw
};

inline void
MushGLProjection::TransformVector(Mushware::t4Val& ioVec) const
{
    ioVec = m_mattress * ioVec;
}

inline Mushware::t4Val
MushGLProjection::TransformedVector(const Mushware::t4Val& ioVec) const
{
    Mushware::t4Val retVal(ioVec);
    TransformVector(retVal);
    return retVal;
}

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLProjection& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } sH3eACuAhXVY7WwCWEwifg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
