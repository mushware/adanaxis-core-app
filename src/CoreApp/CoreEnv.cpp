/*
 * $Id: CoreEnv.cpp,v 1.3 2002/05/10 16:39:39 southa Exp $
 * $Log: CoreEnv.cpp,v $
 * Revision 1.3  2002/05/10 16:39:39  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/03/08 22:48:14  southa
 * Added first avarisse code
 *
 * Revision 1.1  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 */

#include "CoreEnv.h"
#include "CoreApp.h"

void
CoreEnv::Enter(const CoreScript& inScript)
{
    cerr << "Entered script" << endl << inScript << endl;
    for (tSize i=0; i<inScript.SizeGet(); ++i)
    {
        CoreApp::Instance().Process(inScript.Line(i));
    }
}
