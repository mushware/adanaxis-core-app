/*
 * $Id: GameConfig.cpp,v 1.1 2002/10/15 14:02:30 southa Exp $
 * $Log: GameConfig.cpp,v $
 * Revision 1.1  2002/10/15 14:02:30  southa
 * Mode changes
 *
 */

#include "GameConfig.h"
#include "mushPlatform.h"

GameConfig *GameConfig::m_instance=NULL;

GameConfig::GameConfig()
{
    m_displayMode=PlatformVideoUtils::Instance().DefaultModeGet();
    CoreEnv::Instance().VariableGetIfExists(m_displayMode, "DISPLAY_MODE");
}

void
GameConfig::DisplayModeSet(U32 inMode)
{
    m_displayMode=inMode;
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
    m_displayMode=PlatformVideoUtils::Instance().DefaultModeGet();
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
GameConfig::SaveToFile(void) const
{
    string filename;
    CoreEnv::Instance().VariableGetIfExists(filename, "CONFIG_FILENAME");
    if (filename != "")
    {
        ofstream outputFile(filename.c_str());
        if (!outputFile) throw(FileFail(filename, "Could not open file"));
        outputFile << "# Autogenerated file.  Please create a file user.txt if you wish" << endl;
        outputFile << "# to override the contents of this file." << endl << endl;
            
        time_t now(time(NULL));
        outputFile << "# Config saved at " << ctime(&now) << endl;
        outputFile << "configset(\"DISPLAY_MODE\", " << m_displayMode << ")" << endl;
    }
}
