/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GraphWrangler.cpp,v 1.4 2002/05/31 15:18:16 southa Exp $
 * $Log: GraphWrangler.cpp,v $
 * Revision 1.4  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 * Revision 1.3  2002/05/24 16:24:11  southa
 * Config and typenames
 *
 * Revision 1.2  2002/05/10 16:40:39  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/09 17:08:07  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.3  2002/05/08 16:31:21  southa
 * Created API directory
 *
 * Revision 1.2  2002/03/24 16:35:39  southa
 * Wrangler axis finder
 *
 * Revision 1.1  2002/03/21 22:07:54  southa
 * Initial wrangle application handler
 *
 */

#include "GraphWrangler.h"
#include "mushCore.h"
#include "mushGL.h"

void
GraphWrangler::Process(bool &outRedraw)
{
    switch (m_state)
    {
        case kInit:
            Init();
            m_state=kFindVertAxis;
            break;

        case kFindVertAxis:
            FindVertAxis();
            m_state=kFindHorizAxis;
            outRedraw=true;
            break;

        case kFindHorizAxis:
            FindHorizAxis();
            outRedraw=true;
            break;
    }	
}

void
GraphWrangler::Init(void)
{
    m_width=m_tex.Width();
    m_height=m_tex.Height();
    m_hbytes=4*m_width; // fixme
    m_dataPtr=static_cast<U32 *>(m_tex.DataPtr());
}

void
GraphWrangler::FindVertAxis(void)
{
    /* Step in from the right until we find a column where the
     * predominant pixel colour has changed
     */
    bool first=true;
    U32 predomCol=0;
    for (tSize x=m_width-8; x-->0;)
    {
        U32 col=PredominantColumnColour(x);
        if (first)
        {
            first=false;
            predomCol=col;
        }
        else
        {
            if (predomCol != col)
            {
                m_vertAxis=x;
                ReplaceInColumn(x, col, 0x0000ffff);
                return;
            }
        }
    }
    throw(CommandFail("Couldn't find vertical axis"));
}

void
GraphWrangler::FindHorizAxis(void)
{
    m_dataPtr[m_vertAxis]=0xffffffff;
}

U32
GraphWrangler::PredominantColumnColour(tSize inX)
{
    map<U32, U32> colMap;
    for (tSize y=0; y<m_height; y++)
    {
        U32 col=Pixel(inX, y);
        colMap[col]=colMap[col]+1;
    }

    U32 outCol;
    U32 highest=0;
    for (map<U32, U32>::const_iterator i=colMap.begin();
         i != colMap.end(); ++i)
    {
        // cerr << hex << i->first << dec << " " << i->second << endl;
        if (i->second > highest)
        {
            outCol = i->first;
            highest = i->second;
        }
    }
    // cerr << "Predominant colour was 0x" << hex << outCol << dec;
    // cerr << " (occurred " << highest << " times)" << endl;
    return outCol;
}

void
GraphWrangler::ReplaceInColumn(tSize inX, U32 inSrcCol, U32 inDestCol)
{
    for (tSize y=0; y<m_height; ++y)
    {
        if (Pixel(inX, y) == inSrcCol)
        {
            SetPixel(inX, y, inDestCol);
        }
    }
}

U32
GraphWrangler::Pixel(tSize inX, tSize inY)
{
    COREASSERT(inX < m_width);
    COREASSERT(inY < m_height);

    return m_dataPtr[inX+m_width*inY];
}

void
GraphWrangler::SetPixel(tSize inX, tSize inY, U32 inCol)
{
    COREASSERT(inX < m_width);
    COREASSERT(inY < m_height);

    m_dataPtr[inX+m_width*inY]=inCol;
}
