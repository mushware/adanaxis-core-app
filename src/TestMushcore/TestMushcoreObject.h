//%includeGuardStart {
#ifndef TESTMUSHCOREOBJECT_H
#define TESTMUSHCOREOBJECT_H
//%includeGuardStart } ZbgVXkoAm05vlwSoai7fLw
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObject.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 6Pvz7HiimjBXCxXQxlnIcA
/*
 * $Id: TestMushcoreObject.h,v 1.12 2003/09/29 21:48:37 southa Exp $
 * $Log: TestMushcoreObject.h,v $
 * Revision 1.12  2003/09/29 21:48:37  southa
 * XML work
 *
 * Revision 1.11  2003/09/27 17:50:49  southa
 * XML null pointer handling
 *
 * Revision 1.10  2003/09/26 19:18:09  southa
 * XML null pointer handling
 *
 * Revision 1.9  2003/09/25 20:02:25  southa
 * XML pointer work
 *
 * Revision 1.8  2003/09/24 19:03:23  southa
 * XML map IO
 *
 * Revision 1.7  2003/09/23 22:57:57  southa
 * XML vector handling
 *
 * Revision 1.6  2003/09/22 19:40:36  southa
 * XML I/O work
 *
 * Revision 1.5  2003/09/21 23:15:08  southa
 * XML input stream improvements
 *
 * Revision 1.4  2003/09/21 18:49:41  southa
 * XML input stream work
 *
 * Revision 1.3  2003/09/21 15:57:12  southa
 * XML autogenerator work
 *
 * Revision 1.2  2003/09/21 11:46:12  southa
 * XML input stream
 *
 * Revision 1.1  2003/09/21 09:51:10  southa
 * Stream autogenerators
 *
 */

#include "TestMushcoreStandard.h"

//:generate standard ostream xml1 basic
class TestMushcoreObject : public MushcoreObject, public MushcoreXMLConsumer
{
public:
    explicit TestMushcoreObject(Mushware::U32 inNum) :
        m_u8(1),
        m_u32(2),
        m_string("&<>&lt;ab&am,p;cde\"f</string>&,&"),
        m_pNull(NULL),
        m_testObject(NULL)
    {
            m_u8Vector.push_back(4);
            m_u8Vector.push_back(16);
            m_u8Vector.push_back(7);
            m_u32Vector.push_back(3);
            m_u32Vector.push_back(15);
            m_u32Vector.push_back(9);
            m_stringVector.push_back("hams\"ter");
            m_stringVector.push_back("ger,bil");
            m_stringVector.push_back("bad|ger");

            m_vectorVector.push_back();
            m_vectorVector.push_back();
            m_vectorVector.push_back();
            m_vectorVector[0].push_back(3);
            m_vectorVector[0].push_back(5);
            m_vectorVector[0].push_back(7);
            m_vectorVector[2].push_back(8);
            m_vectorVector[2].push_back(35);
            m_vectorVector[2].push_back(1);

            m_mapVector[3].push_back("three");
            m_mapVector[6] = vector<std::string>();
            m_mapVector[15].push_back("\"fifteen-one");
            m_mapVector[15].push_back("fifteen-two\"");

            m_vectorMap.push_back();
            m_vectorMap.push_back();
            m_vectorMap.push_back();

            m_vectorMap[0][6] = "six";
            m_vectorMap[0][7] = "seven";
            m_vectorMap[2][14] = "fourt,)(\"een";

            m_pU32 = new Mushware::U32(2);
            m_pVectorU32 = new vector<Mushware::U32>;
            m_pVectorU32->push_back(4);
            m_pVectorU32->push_back(18);
            m_pVectorU32->push_back(1);

            m_vectorpU32.push_back(new Mushware::U32(2));
            m_vectorpU32.push_back(NULL);
            m_vectorpU32.push_back(new Mushware::U32(19));

            m_testObject = new TestMushcoreObject;
            // m_testObjectVector.push_back(new TestMushcoreObject(0));
    }

    TestMushcoreObject() :
        m_u8(0),
        m_u32(0),
        m_pU32(NULL),
        m_pVectorU32(NULL),
        m_pNull(NULL),
        m_testObject(NULL)
    {
    }

    virtual ~TestMushcoreObject() {}
    
private:
    Mushware::U8 m_u8;
    Mushware::U32 m_u32;
    std::string m_string;
    std::vector<Mushware::U8> m_u8Vector;
    std::vector<Mushware::U32> m_u32Vector;
    std::vector<std::string> m_stringVector;
    std::vector<Mushware::U8> m_u8EmptyVector;
    std::vector<Mushware::U32> m_uEmpty32Vector;
    std::vector<std::string> m_stringEmptyVector;

    std::vector< std::vector<Mushware::U32> > m_vectorVector;
    std::map< Mushware::U32, std::vector<std::string> > m_mapVector;
    std::vector< std::map<Mushware::U32, std::string> > m_vectorMap;

    Mushware::U32 *m_pU32;
    std::vector<Mushware::U32> *m_pVectorU32;
    std::vector<Mushware::U32 *> m_vectorpU32; // nobasic

    Mushware::U32 *m_pNull;


    TestMushcoreObject *m_testObject;
    //vector<TestMushcoreObject *> m_testObjectVector;
    
//%classPrototypes {
public:
    virtual const char *AutoNameGet(void) const;
    virtual TestMushcoreObject *AutoClone(void) const;
    virtual TestMushcoreObject *AutoCreate(void) const;
    static TestMushcoreObject *AutoFactory(void);
    bool AutoEquals(const TestMushcoreObject& inObj) const;
    void AutoPrint(std::ostream& ioOut) const;
    void AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } P51yokolc3e17bhKpojB8Q
};
//%inlineHeader {
inline bool
operator==(const TestMushcoreObject& inA, const TestMushcoreObject& inB)
{
    return inA.AutoEquals(inB);
}
inline std::ostream&
operator<<(std::ostream& ioOut, const TestMushcoreObject& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
#if 0
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const TestMushcoreObject& inObj)
{
    inObj.AutoXMLPrint(ioOut, "");
    return ioOut;
}
#endif
//%inlineHeader } ikvElCmBt/z6dJAPO9xNgw


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
