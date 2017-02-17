/*
 * File:   zusertests.h
 * Author: huuhoa
 *
 * Created on Oct 23, 2015, 2:36:35 PM
 */

#ifndef ZUSERTESTS_H
#define	ZUSERTESTS_H

#include <cppunit/extensions/HelperMacros.h>

class zusertests : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(zusertests);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testAddGetUser);

    CPPUNIT_TEST_SUITE_END();

public:
    zusertests();
    virtual ~zusertests();
    void setUp();
    void tearDown();

private:
    void testMethod();
    void testAddGetUser();
};

#endif	/* ZUSERTESTS_H */

