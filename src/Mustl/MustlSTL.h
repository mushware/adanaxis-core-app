//%includeGuardStart {
#ifndef MUSTLSTL_H
#define MUSTLSTL_H
//%includeGuardStart } qEJO43CDwFVG76SYdxRp1w
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlSTL.h
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
//%Header } iR6a1fUsajua3d19JosZpQ
/*
 * $Id: MustlSTL.h,v 1.9 2006/06/01 15:39:54 southa Exp $
 * $Log: MustlSTL.h,v $
 * Revision 1.9  2006/06/01 15:39:54  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/05/19 13:02:19  southa
 * Mac release work
 *
 * Revision 1.7  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.6  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:31  southa
 * Fixed file headers
 *
 * Revision 1.4  2003/01/17 00:41:05  southa
 * Configuration updates from POST data
 *
 * Revision 1.3  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 * Revision 1.2  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/12/12 18:38:25  southa
 * Mustl separation
 *
 */

#include "MustlStandard.h"

#include "MustlAssert.h"

#include <stack>
#include <stdexcept>

#ifdef HAVE_SSTREAM
#include <sstream>
#else
#include "sstream"
#endif

#include <fstream>
#include <iomanip>
#include <iostream>

#include <typeinfo>

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <ctime>

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
