/*
 * File:   zdbproxytests.h
 * Author: huuhoa
 *
 * Created on Oct 31, 2015, 9:08:48 AM
 */

#ifndef ZDBPROXYTESTS_H
#define	ZDBPROXYTESTS_H

#include <cppunit/extensions/HelperMacros.h>
#include <Poco/Util/ServerApplication.h>

class zdbproxytests : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(zdbproxytests);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testDBConnection);
    CPPUNIT_TEST(testDBGetSet);
    CPPUNIT_TEST(testDBHash);
    CPPUNIT_TEST(testDBSets);

    CPPUNIT_TEST_SUITE_END();

public:
    zdbproxytests();
    virtual ~zdbproxytests();
    void setUp();
    void tearDown();

private:
    void testMethod();
    void testDBConnection();
    void testDBGetSet();
    void testDBHash();
    void testDBSets();
private:
    Poco::Util::ServerApplication *app;
};

#endif	/* ZDBPROXYTESTS_H */

