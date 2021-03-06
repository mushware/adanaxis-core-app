//%includeGuardStart {
#ifndef MEDIAAUDIO_H
#define MEDIAAUDIO_H
//%includeGuardStart } 5PPiYxjjZkwpM5mcMQmsaw
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudio.h
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
//%Header } JklERo1Ule8xr8mFt52hJg
/*
 * $Id: MediaAudio.h,v 1.31 2007/03/21 18:06:05 southa Exp $
 * $Log: MediaAudio.h,v $
 * Revision 1.31  2007/03/21 18:06:05  southa
 * Tied sound fixes
 *
 * Revision 1.30  2006/12/11 18:54:18  southa
 * Positional audio
 *
 * Revision 1.29  2006/12/11 15:01:47  southa
 * Snapshot
 *
 * Revision 1.28  2006/12/11 13:28:23  southa
 * Snapshot
 *
 * Revision 1.27  2006/07/26 16:37:22  southa
 * Options menu
 *
 * Revision 1.26  2006/06/01 15:39:13  southa
 * DrawArray verification and fixes
 *
 * Revision 1.25  2005/05/19 13:02:08  southa
 * Mac release work
 *
 * Revision 1.24  2005/04/19 23:25:40  southa
 * Mode switching and recognition
 *
 * Revision 1.23  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.22  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.21  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.20  2003/08/21 23:09:00  southa
 * Fixed file headers
 *
 * Revision 1.19  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.18  2003/01/18 17:05:46  southa
 * Singleton work
 *
 * Revision 1.17  2003/01/18 13:33:57  southa
 * Created MushcoreSingleton
 *
 * Revision 1.16  2002/12/29 20:30:55  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.15  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.14  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.13  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.12  2002/08/26 12:44:37  southa
 * Timed rewards and sound tweaks
 *
 * Revision 1.11  2002/08/24 13:12:31  southa
 * Null MediaAudio device
 *
 */

#include "MediaStandard.h"

#include "MediaAudioChannelDef.h"

class MediaSound;
class MediaSoundStream;

//:generate
class MediaAudio : public MushcoreAbstractSingleton<MediaAudio>
{
public:
    enum
    {
        kFlagsTiedToListener = 1,
        kFlagsPinned = 2
    };
    MediaAudio();
    virtual ~MediaAudio();
    virtual void PlayMusic(const std::string& inName) = 0;
    virtual void Play(MediaSound& inSound) = 0;
    virtual void Play(MediaSound& inSound, Mushware::tVal inVolume, Mushware::t4Val inPosition,
                      Mushware::U32 inFlags) = 0;
    virtual void Play(MediaSoundStream& inSoundStream, Mushware::U32 inLoop=10000) = 0;
    virtual void VoicePlay(MediaSound& inSound) = 0;
    virtual void SoundHalt(MediaSound& inSound) = 0;
    virtual void Load(MediaSound& inSound) const = 0;
    virtual void Load(MediaSoundStream& inSoundStream) = 0;
    virtual void Free(MediaSound& inSound) const = 0;
    virtual void Ticker(void) = 0;
    virtual void MusicFadeIn(Mushware::tVal inMsec) = 0;
    virtual void MusicFadeOut(Mushware::tVal inMsec) = 0;
    virtual void MusicVolumeSet(Mushware::tVal inVolume) = 0;
    virtual void AudioVolumeSet(Mushware::tVal inVolume) = 0;
    virtual void VoiceVolumeSet(Mushware::tVal inVolume) = 0;
    
    const MediaAudioChannelDef& ChannelDef(Mushware::U32 inIndex);
    MediaAudioChannelDef& ChannelDefWRef(Mushware::U32 inIndex);
    void ChannelDefsResize(Mushware::U32 inSize, const MediaAudioChannelDef& inDef);
    bool ChannelSelect(Mushware::U32& outChannel);
    Mushware::tVal ImpliedVolume(const Mushware::t4Val& inPos);
    Mushware::tVal ImpliedVolume(const MediaAudioChannelDef& inDef);
    Mushware::tVal ImpliedPanning(const MediaAudioChannelDef& inDef);
    
    static MediaAudio *SingletonFactory(void);
    
private:
    std::vector<MediaAudioChannelDef *> m_channelDefs;
    MushMeshPosticity m_listenerPost; //:readwrite
    Mushware::tVal m_distanceFactor;
    Mushware::U32 m_nextChannel;
//%classPrototypes {
public:
    const MushMeshPosticity& ListenerPost(void) const { return m_listenerPost; }
    void ListenerPostSet(const MushMeshPosticity& inValue) { m_listenerPost=inValue; }
//%classPrototypes } RSs3c6YdNdTyIqkfQ50X2A
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
