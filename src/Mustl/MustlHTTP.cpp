//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlHTTP.cpp
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
//%Header } nfUq0CRxzP6Dw+4d5BxSYw
/*
 * $Id: MustlHTTP.cpp,v 1.10 2006/06/01 15:39:52 southa Exp $
 * $Log: MustlHTTP.cpp,v $
 * Revision 1.10  2006/06/01 15:39:52  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/05/19 13:02:18  southa
 * Mac release work
 *
 * Revision 1.8  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.7  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:09:25  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 * Revision 1.4  2002/12/29 20:59:58  southa
 * More build fixes
 *
 * Revision 1.3  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
 * Revision 1.4  2002/11/20 22:35:27  southa
 * Multiplayer setup
 *
 * Revision 1.3  2002/11/12 17:05:01  southa
 * Tidied localweb server
 *
 * Revision 1.2  2002/11/08 00:15:30  southa
 * Fixed errors
 *
 * Revision 1.1  2002/11/07 00:53:37  southa
 * localweb work
 *
 */

#include "MustlHTTP.h"

#include "MustlData.h"
#include "MustlSTL.h"

using namespace Mustl;
using namespace std;

const char MustlHTTP::m_endl[3]={0x0d, 0x0a, 0};

MustlHTTP::MustlHTTP() :
    m_refresh(0),
    m_title("mushware"),
    m_allowCaching(false)
{
    m_content = new ostringstream;
}

MustlHTTP::~MustlHTTP()
{
    delete m_content;
}

void
MustlHTTP::Reply200(void)
{
    *m_content << "HTTP/1.1 200 OK" << m_endl;
}

void
MustlHTTP::ContentTypeHTML(void)
{
    *m_content << "Content-Type: text/html; charset=ISO-8859-1" << m_endl;
    *m_content << "Connection: close" << m_endl;
    if (!m_allowCaching) *m_content << "Expires: 0" << m_endl;
}

void
MustlHTTP::ContentType(const string& inStr)
{
    *m_content << "Content-Type: " << inStr << m_endl;
    *m_content << "Connection: close" << m_endl;
    if (!m_allowCaching) *m_content << "Expires: 0" << m_endl;
}

void
MustlHTTP::Endl(void)
{
    *m_content << m_endl;
}

void
MustlHTTP::Header(void)
{
    *m_content << "<html>" << m_endl;
    *m_content << "<head>" << m_endl;
    // Need optional stylesheet here
    *m_content << "<link rel=\"StyleSheet\" href=\"/style.css\" type=\"text/css\">" << m_endl;
    *m_content << "<title>" << m_title << "</title>" << m_endl;
    if (m_refresh != 0)
    {
        *m_content << "<meta http-equiv=Refresh content=\"";
        *m_content << m_refresh << "\">" << m_endl;
    }
    *m_content << "</head>" << m_endl << "<body>" << m_endl;
}

void
MustlHTTP::Footer(void)
{
    *m_content << "</body>" << m_endl << "</html>" << m_endl;
}

void
MustlHTTP::ContentGet(MustlData& outData)
{
    outData.Write(dynamic_cast<ostringstream *>(m_content)->str());
}
