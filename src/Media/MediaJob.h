//%includeGuardStart {
#ifndef MEDIAJOB_H
#define MEDIAJOB_H
//%includeGuardStart } ErDTTM9DfaODCSxfXAakNA
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaJob.h
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
//%Header } NcK87obYmZ7Z3JFEpDGIKA

#include "MediaSDL.h"
#include "MediaStandard.h"

//:generate virtual standard ostream xml1
class MediaJob : public MushcoreVirtualObject
{
public:
    MediaJob() {}
    explicit MediaJob(std::string& name);
    virtual ~MediaJob();

    virtual void Run();
    virtual bool MainThreadPreRun();
    virtual bool MainThreadPostRun();

    virtual void RunToCompletionNow();

private:
    std::string m_name; //:readwrite
    std::string m_error; //:readwrite
    Mushware::U64 m_startTime; //:readwrite
    Mushware::U64 m_endTime; //:readwrite

//%classPrototypes {
public:
    const std::string& Name(void) const { return m_name; }
    void NameSet(const std::string& inValue) { m_name=inValue; }
    const std::string& Error(void) const { return m_error; }
    void ErrorSet(const std::string& inValue) { m_error=inValue; }
    const Mushware::U64& StartTime(void) const { return m_startTime; }
    void StartTimeSet(const Mushware::U64& inValue) { m_startTime=inValue; }
    const Mushware::U64& EndTime(void) const { return m_endTime; }
    void EndTimeSet(const Mushware::U64& inValue) { m_endTime=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } KN7Aee4b0IxZoboB4CAePg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MediaJob& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } fpavN8kmzHn8CrlOCJQw+g
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
