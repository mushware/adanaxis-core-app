//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRuby.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } yY7ZZkvIHHOoUzJzTAQPOQ
/*
 * $Id: MushGameRuby.cpp,v 1.12 2006/08/01 13:41:15 southa Exp $
 * $Log: MushGameRuby.cpp,v $
 * Revision 1.12  2006/08/01 13:41:15  southa
 * Pre-release updates
 *
 * Revision 1.11  2006/07/31 11:01:38  southa
 * Music and dialogues
 *
 * Revision 1.10  2006/07/28 16:52:24  southa
 * Options work
 *
 * Revision 1.9  2006/07/27 13:51:36  southa
 * Menu and control fixes
 *
 * Revision 1.8  2006/07/26 16:37:23  southa
 * Options menu
 *
 * Revision 1.7  2006/07/12 11:22:43  southa
 * Advanced control menu
 *
 * Revision 1.6  2006/07/11 19:49:06  southa
 * Control menu
 *
 * Revision 1.5  2006/07/11 12:37:52  southa
 * Control configuration
 *
 * Revision 1.4  2006/07/10 16:01:19  southa
 * Control menu work
 *
 * Revision 1.3  2006/07/08 16:05:59  southa
 * Ruby menus and key handling
 *
 * Revision 1.2  2006/07/07 18:13:59  southa
 * Menu start and stop
 *
 * Revision 1.1  2006/07/07 07:57:29  southa
 * Key translation
 *
 */

#include "MushGameRuby.h"

#include "MushGameAppHandler.h"
#include "MushGameAxisDef.h"
#include "MushGameDialogue.h"
#include "MushGameDialogueUtils.h"
#include "MushGameKeyDef.h"
#include "MushGameUtil.h"

#include "API/mushMedia.h"
#include "API/mushPlatform.h"

MUSHRUBYEMPTYOBJ_INSTANCE(4000);

MUSHRUBY_INSTALL(MushGameRuby);

using namespace Mushware;
using namespace std;

Mushware::tRubyValue
MushGameRuby::KeySymbolToName(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    MushRubyValue keyValue(inArg0);
    
    std::string nameStr;
    if (keyValue.U32() == 0)
    {
        nameStr = "none";
    }
    else
    {
        nameStr = MediaKeyboard::KeySymbolToName(keyValue.U32());
    }
    return MushRubyValue(nameStr).Value();
}

Mushware::tRubyValue
MushGameRuby::GameModeEnter(Mushware::tRubyValue inSelf)
{
    MushGameUtil::LogicWRef().GameModeEnter();
    return kRubyQnil;
}

Mushware::tRubyValue
MushGameRuby::NewGameEnter(Mushware::tRubyValue inSelf)
{
    MushGameUtil::AppHandler().GameRestart();
    MushGameUtil::LogicWRef().GameModeEnter();
    return kRubyQnil;
}

Mushware::tRubyValue
MushGameRuby::Quit(Mushware::tRubyValue inSelf)
{
    MushGameUtil::LogicWRef().QuitModeEnter();
    return kRubyQnil;
}  

Mushware::tRubyValue
MushGameRuby::AxisSymbol(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    U32 axisID = 0;
    
    try
    {
        MushRubyValue axisNum(inArg0);
        const MushGameAxisDef& axisRef = MushGameUtil::AppHandler().AxisDef(axisNum.U32());

        axisID = axisRef.DeviceNum() * 16 + axisRef.DeviceAxisNum();
    }
    catch (std::exception& e)
    {
            MushRubyUtil::Raise(e.what());       
    }
    
    return MushRubyValue(axisID).Value();
}

Mushware::tRubyValue
MushGameRuby::AxisSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1)
{
    try
    {
        MushRubyValue newAxis(inArg0);
        U32 newDeviceNum = newAxis.U32() / 16;
        U32 newAxisNum = newAxis.U32() % 16;
        
        MushRubyValue axisNum(inArg1);

        MushGameAxisDef axisDef = MushGameUtil::AppHandler().AxisDef(axisNum.U32());
        
        axisDef.DeviceNumSet(newDeviceNum);
        axisDef.DeviceAxisNumSet(newAxisNum);
        
        if (newDeviceNum > 0)
        {
            axisDef.RequiredKeySet(0);
        }
        
        MushGameUtil::AppHandler().AxisDefSet(axisDef, axisNum.U32());
    }
    catch (std::exception& e)
    {
        MushRubyUtil::Raise(e.what());       
    }
    
    return Mushware::kRubyQnil;
}

Mushware::tRubyValue
MushGameRuby::AxisName(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    MushRubyValue axisID(inArg0);
    
    U32 deviceNum = axisID.U32() / 16;
    U32 axisNum = axisID.U32() % 16;
    
    std::string axisName = "(none)";
    
    switch (deviceNum)
    {
        case MushGameAxisDef::kDeviceMouse0:
        {
            if (axisNum == 0) axisName = "mouse x";
            if (axisNum == 1) axisName = "mouse y";
        }
        break;
            
        case MushGameAxisDef::kDeviceMouse1:
        {
            if (axisNum == 0) axisName = "mouse2 x";
            if (axisNum == 1) axisName = "mouse2 y";
        }
        break;
            
        case MushGameAxisDef::kDeviceStick0:
        {
            axisName = "stick ";
            switch (axisNum)
            {
                case 0: 
                    axisName += "x";
                    break;
                    
                case 1:
                    axisName += "y";
                    break;
                    
                case 2:
                    axisName += "z";
                    break;
                    
                case 3:
                    axisName += "w";
                    break;
                    
                default:
                    ostringstream number;
                    number << axisNum+1;
                    axisName += number.str();
            }
        }
        break;

        case MushGameAxisDef::kDeviceStick1:
        {
            axisName = "stick2 ";
            switch (axisNum)
            {
                case 0: 
                    axisName += "x";
                    break;
                    
                case 1:
                    axisName += "y";
                    break;
                    
                case 2:
                    axisName += "z";
                    break;
                    
                case 3:
                    axisName += "w";
                    break;
                    
                default:
                    ostringstream number;
                    number << axisNum+1;
                    axisName += number.str();
            }
        }
        break;
    }
    return MushRubyValue(axisName).Value();
}

Mushware::tRubyValue
MushGameRuby::AxisKeySymbol(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    MushRubyValue axisID(inArg0);
    
    U32 axisNum = axisID.U32() / 4;
    U32 subType = axisID.U32() % 4;
    
    const MushGameAxisDef& axisRef = MushGameUtil::AppHandler().AxisDef(axisNum);
    
    U32 symbolValue = 0;
    switch (subType)
    {
        case 0:
            symbolValue = axisRef.UpKey();
            break;
            
        case 1:
            symbolValue = axisRef.DownKey();
            break;
            
        case 2:
            symbolValue = axisRef.RequiredKey();
            break;
            
        default:
        {
            ostringstream message;
            message << "Bad axis symbol number " << axisID.U32();
            MushRubyUtil::Raise(message.str());
        }
        break;
    }    
    
    return MushRubyValue(symbolValue).Value();
}

Mushware::tRubyValue
MushGameRuby::AxisKeySet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1)
{
    MushRubyValue axisID(inArg1);
    
    U32 axisNum = axisID.U32() / 4;
    U32 subType = axisID.U32() % 4;
    
    U32 symbolValue = MushRubyValue(inArg0).U32();

    MushGameUtil::AppHandler().KeyPurge(symbolValue);

    MushGameAxisDef axisDef = MushGameUtil::AppHandler().AxisDef(axisNum);
    
    switch (subType)
    {
        case 0:
            axisDef.UpKeySet(symbolValue);
            break;
            
        case 1:
            axisDef.DownKeySet(symbolValue);
            break;
            
        case 2:
            axisDef.RequiredKeySet(symbolValue);
            break;
            
        default:
        {
            ostringstream message;
            message << "Bad axis symbol number " << axisID.U32();
            MushRubyUtil::Raise(message.str());
        }
        break;
    }    
    
    MushGameUtil::AppHandler().AxisDefSet(axisDef, axisNum);
    
    return Mushware::kRubyQnil;
}

Mushware::tRubyValue
MushGameRuby::KeySymbol(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    U32 keySymbol = 0;
    
    try
    {
        MushRubyValue keyID(inArg0);
        
        const MushGameKeyDef& keyRef = MushGameUtil::AppHandler().KeyDef(keyID.U32());  
        
        keySymbol = keyRef.KeyValue();
    }
    catch (std::exception& e)
    {
        MushRubyUtil::Raise(e.what());       
    }
    
    return MushRubyValue(keySymbol).Value();
}

Mushware::tRubyValue
MushGameRuby::KeySet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1)
{
    U32 symbolValue = MushRubyValue(inArg0).U32();
    MushGameUtil::AppHandler().KeyPurge(symbolValue);
    
    try
    {
        MushRubyValue keyID(inArg1);
        
        MushGameKeyDef keyDef = MushGameUtil::AppHandler().KeyDef(keyID.U32());  
        
        keyDef.KeyValueSet(symbolValue);
        
        MushGameUtil::AppHandler().KeyDefSet(keyDef, keyID.U32());
    }
    catch (std::exception& e)
    {
        MushRubyUtil::Raise(e.what());       
    }
    
    return Mushware::kRubyQnil;
}

Mushware::tRubyValue
MushGameRuby::NumJoysticks(Mushware::tRubyValue inSelf)
{
    U32 numSticks = MediaJoystick::Sgl().NumJoysticks();
    return MushRubyValue(numSticks).Value();
}  

Mushware::tRubyValue
MushGameRuby::ControlsToDefaultSet(Mushware::tRubyValue inSelf)
{
    MushGameUtil::AppHandler().ControlsToDefaultSet();
    return Mushware::kRubyQnil;
}  

Mushware::tRubyValue
MushGameRuby::DisplayModeString(Mushware::tRubyValue inSelf)
{
    std::string displayName = "<no mode>";
    try
    {
        U32 modeNum = MushGameUtil::AppHandler().DisplayModeNum();
        displayName = PlatformVideoUtils::Sgl().ModeDefGet(modeNum).NameGet();
    }
    catch (std::exception& e)
    {
        MushRubyUtil::Raise(e.what());       
    }
    
    return MushRubyValue(displayName).Value();
}  

Mushware::tRubyValue
MushGameRuby::PreviousDisplayMode(Mushware::tRubyValue inSelf)
{
    try
    {
        MushGameUtil::AppHandler().PreviousDisplayMode();
    }
    catch (std::exception& e)
    {
        MushRubyUtil::Raise(e.what());       
    }

    return Mushware::kRubyQnil;
}

Mushware::tRubyValue
MushGameRuby::NextDisplayMode(Mushware::tRubyValue inSelf)
{
    try
{
    MushGameUtil::AppHandler().NextDisplayMode();
}
catch (std::exception& e)
{
    MushRubyUtil::Raise(e.what());       
}

return Mushware::kRubyQnil;
}

Mushware::tRubyValue
MushGameRuby::DisplayReset(Mushware::tRubyValue inSelf)
{
    try
    {
        MushGameUtil::AppHandler().DisplayReset();
    }
    catch (std::exception& e)
    {
        MushRubyUtil::Raise(e.what());       
    }
    return Mushware::kRubyQnil;
}

Mushware::tRubyValue
MushGameRuby::AudioVolume(Mushware::tRubyValue inSelf)
{
    U32 retVal = MushGameUtil::AppHandler().Config().AudioVolume();
    return MushRubyValue(retVal).Value();
}

Mushware::tRubyValue
MushGameRuby::AudioVolumeSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    MushRubyValue value(inArg0);
    MushGameUtil::AppHandler().ConfigWRef().AudioVolumeSet(value.U32());
    MediaAudio::Sgl().AudioVolumeSet(value.U32() / 100.0);
    return Mushware::kRubyQnil;
}

Mushware::tRubyValue
MushGameRuby::MusicVolume(Mushware::tRubyValue inSelf)
{
    U32 retVal = MushGameUtil::AppHandler().Config().MusicVolume();
    return MushRubyValue(retVal).Value();
}

Mushware::tRubyValue
MushGameRuby::MusicVolumeSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    MushRubyValue value(inArg0);
    MushGameUtil::AppHandler().ConfigWRef().MusicVolumeSet(value.U32());
    MediaAudio::Sgl().MusicVolumeSet(value.U32() / 100.0);

    return Mushware::kRubyQnil;
}

Mushware::tRubyValue
MushGameRuby::TextureDetail(Mushware::tRubyValue inSelf)
{
    U32 retVal = MushGameUtil::AppHandler().Config().TextureDetail();
    return MushRubyValue(retVal).Value();
}

Mushware::tRubyValue
MushGameRuby::TextureDetailSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    MushRubyValue value(inArg0);
    MushGameUtil::AppHandler().ConfigWRef().TextureDetailSet(value.U32());
    
    // Use compresion at low detail levels only - alpha-mapped textures don't compress well
    if (value.U32() > 1)
    {
        MushGLV::Sgl().UseS3TCSet(false);
    }
    else
    {
        MushGLV::Sgl().UseS3TCSet(true);
    }

    return Mushware::kRubyQnil;
}

Mushware::tRubyValue
MushGameRuby::MouseSensitivity(Mushware::tRubyValue inSelf)
{
    tVal retVal = MushGameUtil::AppHandler().Config().MouseSensitivity();
    return MushRubyValue(retVal).Value();
}

Mushware::tRubyValue
MushGameRuby::MouseSensitivitySet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    MushRubyValue value(inArg0);
    MushGameUtil::AppHandler().ConfigWRef().MouseSensitivitySet(value.Val());
    MushGameUtil::AppHandler().MouseSensitivitySet(value.Val());
    return Mushware::kRubyQnil;
}

Mushware::tRubyValue
MushGameRuby::Brightness(Mushware::tRubyValue inSelf)
{
    tVal retVal = MushGameUtil::AppHandler().Config().Brightness();
    return MushRubyValue(retVal).Value();
}

Mushware::tRubyValue
MushGameRuby::BrightnessSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    MushRubyValue value(inArg0);
    MushGameUtil::AppHandler().ConfigWRef().BrightnessSet(value.Val());
    MushGameUtil::AppHandler().BrightnessSet(value.Val());
    return Mushware::kRubyQnil;
}

Mushware::tRubyValue
MushGameRuby::GameDialoguesLoad(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    MushRubyValue param0(inArg0);
    ifstream fileStream(param0.String().c_str());
    if (!fileStream)
    {
        MushRubyUtil::Raise("Could not open file '"+param0.String()+"'");
    }
    try
    {
        MushcoreXMLIStream xmlIStream(fileStream);
        
        xmlIStream >> MushcoreData<MushGameDialogue>::Sgl();
    }
    catch (std::exception& e)
    {
        MushRubyUtil::Raise(e.what());       
    }
    return Mushware::kRubyQnil;
}

Mushware::tRubyValue
MushGameRuby::NamedDialoguesAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    MushRubyValue param0(inArg0);
    try
    {
        MushGameDialogueUtils::NamedDialoguesAdd(MushGameUtil::AppHandler().LogicWRef().SaveData().DialoguesWRef(), param0.String());
    }
    catch (std::exception& e)
    {
        MushRubyUtil::Raise(e.what());       
    }
    return Mushware::kRubyQnil;
}

Mushware::tRubyValue
MushGameRuby::SoundDefine(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1)
{
    MushRubyValue param0(inArg0);
    MushRubyValue param1(inArg1);
    try
    {
        std::string command = "residentsound('"+param0.String()+"','"+param1.String()+"')";
        MushcoreInterpreter::Sgl().Execute(command);
    }
    catch (std::exception& e)
    {
        MushRubyUtil::Raise(e.what());       
    }
    return Mushware::kRubyQnil;
}

Mushware::tRubyValue
MushGameRuby::SoundStreamDefine(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1)
{
    MushRubyValue param0(inArg0);
    MushRubyValue param1(inArg1);
    try
    {
        std::string command = "soundstream('"+param0.String()+"','"+param1.String()+"')";
        MushcoreInterpreter::Sgl().Execute(command);
    }
    catch (std::exception& e)
    {
        MushRubyUtil::Raise(e.what());       
    }
    return Mushware::kRubyQnil;
}

Mushware::tRubyValue
MushGameRuby::PackageID(Mushware::tRubyValue inSelf)
{
    return MushRubyValue(MushcoreInfo::Sgl().PackageID()).Value();
}

Mushware::tRubyValue
MushGameRuby::GameMsec(Mushware::tRubyValue inSelf)
{
    return MushRubyValue(MushGameUtil::LogicRef().GameMsec()).Value();
}

void
MushGameRuby::MethodsInstall(void)
{
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cKeySymbolToName", KeySymbolToName);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cGameModeEnter", GameModeEnter);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cNewGameEnter", NewGameEnter);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cQuit", Quit);
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cAxisKeySymbol", AxisKeySymbol);
    MushRubyUtil::SingletonMethodDefineTwoParams(Klass(), "cAxisKeySet", AxisKeySet);
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cAxisSymbol", AxisSymbol);
    MushRubyUtil::SingletonMethodDefineTwoParams(Klass(), "cAxisSet", AxisSet);
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cAxisName", AxisName);
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cKeySymbol", KeySymbol);
    MushRubyUtil::SingletonMethodDefineTwoParams(Klass(), "cKeySet", KeySet);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cNumJoysticks", NumJoysticks);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cControlsToDefaultSet", ControlsToDefaultSet);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cDisplayModeString", DisplayModeString);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cPreviousDisplayMode", PreviousDisplayMode);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cNextDisplayMode", NextDisplayMode);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cDisplayReset", DisplayReset);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cAudioVolume", AudioVolume);
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cAudioVolumeSet", AudioVolumeSet);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cMusicVolume", MusicVolume);
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cMusicVolumeSet", MusicVolumeSet);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cTextureDetail", TextureDetail);
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cTextureDetailSet", TextureDetailSet);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cMouseSensitivity", MouseSensitivity);
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cMouseSensitivitySet", MouseSensitivitySet);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cBrightness", Brightness);
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cBrightnessSet", BrightnessSet);
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cGameDialoguesLoad", GameDialoguesLoad);
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cNamedDialoguesAdd", NamedDialoguesAdd);
    MushRubyUtil::SingletonMethodDefineTwoParams(Klass(), "cSoundDefine", SoundDefine);
    MushRubyUtil::SingletonMethodDefineTwoParams(Klass(), "cSoundStreamDefine", SoundStreamDefine);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cPackageID", PackageID);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cGameMsec", GameMsec);
}
