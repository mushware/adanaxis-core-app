/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameConfig.cpp,v 1.4 2002/11/14 17:29:08 southa Exp $
 * $Log: GameConfig.cpp,v $
 * Revision 1.4  2002/11/14 17:29:08  southa
 * Config database
 *
 * Revision 1.3  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.2  2002/10/17 15:50:58  southa
 * Config saving, pause and quit
 *
 * Revision 1.1  2002/10/15 14:02:30  southa
 * Mode changes
 *
 */

#include "GameConfig.h"

#include "GameConfigDef.h"

#include "mushPlatform.h"


GameConfig *GameConfig::m_instance=NULL;

CoreInstaller GameConfigInstaller(GameConfig::Install);

GameConfig::GameConfig()
{
    CoreData<GameConfigDef>::Instance().DataGive("displaymode", new GameConfigDefU32(PlatformVideoUtils::Instance().DefaultModeGet(), 0, PlatformVideoUtils::Instance().NumModesGet()));
    CoreData<GameConfigDef>::Instance().DataGive("displayquality", new GameConfigDefString(
        "medium", "low=Low&medium=Medium&high=High"));
    CoreData<GameConfigDef>::Instance().DataGive("displaylighting", new GameConfigDefString(
        "dynamic", "none=None&dynamic=Dynamic"));
    CoreData<GameConfigDef>::Instance().DataGive("networkperms", new GameConfigDefString(
        "normal", "none=None&normal=Normal&debug=Debug"));
    CoreData<GameConfigDef>::Instance().DataGive("networkspeed", new GameConfigDefString(
        "56k", "56k=56k Modem&cable=Cable/DSL&t1=LAN/T1/Infinite"));

    CoreData<GameConfigDef>::Instance().DataGive("httpproxy", new GameConfigDefString(""));
    
    CoreData<GameConfigDef>::Instance().DataGive("configperms", new GameConfigDefString(
        "allowlocal", "allownone=Always Ask&allowlocal=Allow Localhost&allowall=Allow All"));
    CoreData<GameConfigDef>::Instance().DataGive("configextra", new GameConfigDefString(""));
    CoreData<GameConfigDef>::Instance().DataGive("configport", new GameConfigDefU32(7200,0,65535));
    CoreData<GameConfigDef>::Instance().DataGive("multiport", new GameConfigDefU32(7121,0,65535));
}

U32
GameConfig::DisplayModeGet(void) const
{
    return CoreData<GameConfigDef>::Instance().DataGet("displaymode")->ValueGet().U32Get();
}

void
GameConfig::DisplayModeSet(U32 inMode)
{
    CoreData<GameConfigDef>::Instance().DataGet("displaymode")->ValueSet(CoreScalar(inMode));
    
    try
    {
        SaveToFile();
    }
    catch (exception& e)
    {
        cerr << "Failed to save config: " << e.what() << endl;
    }
}

void
GameConfig::DisplayModeSetDefault(void)
{
    DisplayModeSet(PlatformVideoUtils::Instance().DefaultModeGet());
}

CoreScalar
GameConfig::ParameterGet(const string& inName) const
{
    return CoreData<GameConfigDef>::Instance().DataGet(inName)->ValueGet();
}

void
GameConfig::ParameterSet(const string& inName, const CoreScalar& inValue)
{
    CoreData<GameConfigDef>::Instance().DataGet(inName)->ValueSet(inValue);
}

void
GameConfig::PostDataHandle(const string& inData)
{
    bool found=false;
    
    CoreData<GameConfigDef>::tMapIterator endValue=CoreData<GameConfigDef>::Instance().End();

    for (CoreData<GameConfigDef>::tMapIterator p=CoreData<GameConfigDef>::Instance().Begin();
         p != endValue; ++p)
    {
        if (p->second->FromPostRetrieve(p->first, inData)) found=true;
    }

    if (found)
    {
        SaveToFile();
    }
}

void
GameConfig::SaveToFile(void) const
{
    string filename;
    CoreEnv::Instance().VariableGetIfExists(filename, "CONFIG_FILENAME");
    if (filename != "")
    {
        ofstream outputFile(filename.c_str());
        if (!outputFile) throw(FileFail(filename, "Could not open file"));
        Pickle(outputFile);
    }
}

void
GameConfig::HandleValueEnd(CoreXML& inXML)
{
    string dataName=inXML.GetAttribOrThrow("name").StringGet();
    if (!CoreData<GameConfigDef>::Instance().DataExists(dataName))
    {
        inXML.Throw("Config value '"+dataName+"' does not exist");
    }
    CoreData<GameConfigDef>::Instance().DataGet(dataName)->ValueSet(CoreScalar(inXML.TopData()));
}

void
GameConfig::HandleConfigStart(CoreXML& inXML)
{
    if (inXML.GetAttribOrThrow("version").StringGet() != CoreInfo::PackageIDGet())
    {
        inXML.Throw("Config version ("+inXML.GetAttribOrThrow("version").StringGet()+" differs from application ("+CoreInfo::PackageIDGet()+")");
    }
    m_pickleState=kPickleData;
}

void
GameConfig::HandleConfigEnd(CoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
GameConfig::NullHandler(CoreXML& inXML)
{
}

void
GameConfig::Pickle(ostream& inOut, const string& inPrefix="") const
{
    time_t now(time(NULL));
    inOut << inPrefix << "<!-- GameConfig file saved at " << ctime(&now) << " -->" << endl;
    inOut << inPrefix << "<!-- This is an autogenerated file." << endl << "To override, create a file named userconfig.xml in the same directory -->" << endl;

    inOut << inPrefix << "<config version=\"" << CoreInfo::PackageIDGet() << "\">" << endl;
    
    CoreData<GameConfigDef>::tMapIterator endValue=CoreData<GameConfigDef>::Instance().End();

    for (CoreData<GameConfigDef>::tMapIterator p=CoreData<GameConfigDef>::Instance().Begin();
         p != endValue; ++p)
    {
        inOut << inPrefix << "  <value name=\"" << p->first << "\">";
        if (p->second != NULL)
        {
            inOut << p->second->ValueGet();
        }
        inOut << "</value>" << endl;
    }

    inOut << inPrefix << "</config>" << endl;
}

void
GameConfig::UnpicklePrologue(void)
{
    // Config unpickling appends the pickle config to the current
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleInit]["config"] = &GameConfig::HandleConfigStart;
    m_startTable[kPickleData]["value"] = &GameConfig::NullHandler;
    m_endTable[kPickleData]["value"] = &GameConfig::HandleValueEnd;

    m_endTable[kPickleData]["config"] = &GameConfig::HandleConfigEnd;
    m_pickleState=kPickleInit;
    m_baseThreaded=0;
}

void
GameConfig::Unpickle(CoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
GameConfig::UnpickleEpilogue(void)
{
    m_startTable.resize(0);
    m_endTable.resize(0);
}

void
GameConfig::XMLStartHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        //        if (m_pickleState == kPickleData)
        //        {
        //            GameConfig::XMLStartHandler(inXML);
        //            m_pickleState=kPickleWithinBase;
        //            ++m_baseThreaded;
        //        }
        //        else
        {
            ostringstream message;
            message << "Unexpected tag <" << inXML.TopTag() << "> in Config.  Potential matches are";
            ElementFunctionMap::iterator p = m_startTable[m_pickleState].begin();
            while (p != m_startTable[m_pickleState].end())
            {
                message << " <" << p->first << ">";
                p++;
            }
            inXML.Throw(message.str());
        }
    }
}

void
GameConfig::XMLEndHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        //        if (m_pickleState == kPickleWithinBase)
        //        {
        //          GameConfig::XMLEndHandler(inXML);
        //            --m_baseThreaded;
        //            if (m_baseThreaded == 0)
        //            {
        //                m_pickleState=kPickleData;
        //            }
        //        }
        //        else
        {
            ostringstream message;
            message << "Unexpected end of tag </" << inXML.TopTag() << "> in Config.  Potential matches are";
            ElementFunctionMap::iterator p = m_endTable[m_pickleState].begin();
            while (p != m_endTable[m_pickleState].end())
            {
                message << " <" << p->first << ">";
                p++;
            }
            inXML.Throw(message.str());
        }
    }
}

void
GameConfig::XMLDataHandler(CoreXML& inXML)
{
}

CoreScalar
GameConfig::GameConfigLoad(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    U32 numParams=ioCommand.NumParams();
    if (numParams != 1)
    {
        throw(CommandFail("Usage: gameconfigload(filename)"));
    }
    string filename;
    ioCommand.PopParam(filename);
    ifstream inStream(filename.c_str());
    if (!inStream) throw(LoaderFail(filename, "Could not open file"));
    CoreXML xml(inStream, filename);
    GameConfig::Instance().Unpickle(xml);
    return CoreScalar(0);
}

void
GameConfig::Install(void)
{
    CoreApp::Instance().AddHandler("gameconfigload", GameConfigLoad);
}
