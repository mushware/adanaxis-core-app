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
//%Header } XL6LbV8MmQMjjqjPiqIheA

#include "MediaSDL.h"
#include "MediaStandard.h"

//:generate virtual standard ostream xml1
class MediaJob : public MushcoreVirtualObject
{
public:

    enum tJobState {
        kJobStateNew,
        kJobStateWaiting,
        kJobStateQueued,
        kJobStatePreRun,
        kJobStateRunning,
        kJobStatePostRun,
        kJobStateWaitAgain,
        kJobStateQueueAgain,
        kJobStateDone,
        kJobStateAbort,
        kJobStateErrored,
        kJobStateKilled
    };

    enum {
        kJobMagic=0x6f3fa396
    };

    MediaJob();
    MediaJob(std::string& name, const char*jobType);
    virtual ~MediaJob();

    tJobState JobState() const;
    void JobStateSet(tJobState inValue);
    virtual const std::vector<MediaJobId> JobIdsToWaitFor() const;
    virtual void JobIdToWaitForAdd(MediaJobId jobId);
    virtual void JobIdToWaitForAdd(std::vector<MediaJobId>& jobIds);
    virtual bool JobCanStart() const;

    virtual void PrerequisitesCreate();
    virtual void Run();
    virtual void MainThreadPreRun();
    virtual void MainThreadPostRun();

    virtual void RunToCompletionNow();

protected:
    // m_killSwitch is written/read by multiple threads but can only transiton once, false to true
    // and exact synchronisation is not necessary
    bool m_killSwitch; //:readwrite

private:
    MediaJobId m_jobMagic; //:readwrite
    std::string m_jobType; //:read
    MediaJobId m_jobId; //:read

    // Mutex covers the two elements below
    mutable SDL_mutex *m_pStateMutex; //:ignore
    std::vector<MediaJobId> m_JobIdsToWaitFor;
    Mushware::U32 m_jobState;

    std::string m_name; //:readwrite
    std::string m_error; //:readwrite
    Mushware::U64 m_startTime; //:readwrite
    Mushware::U64 m_endTime; //:readwrite

//%classPrototypes {
public:
    const bool& KillSwitch(void) const { return m_killSwitch; }
    void KillSwitchSet(const bool& inValue) { m_killSwitch=inValue; }
    const MediaJobId& JobMagic(void) const { return m_jobMagic; }
    void JobMagicSet(const MediaJobId& inValue) { m_jobMagic=inValue; }
    const std::string& JobType(void) const { return m_jobType; }
    const MediaJobId& JobId(void) const { return m_jobId; }
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
//%classPrototypes } hRB8oUnbp4b3xkYbWHqwmw
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
