/*
 * File:   zdbproxytests.cpp
 * Author: huuhoa
 *
 * Created on Oct 31, 2015, 9:08:48 AM
 */

#include "zdbproxytests.h"
#include <Poco/Util/ServerApplication.h>
#include <zdb/ZDBProxy.h>
#include <string>

CPPUNIT_TEST_SUITE_REGISTRATION(zdbproxytests);

zdbproxytests::zdbproxytests() {
}

zdbproxytests::~zdbproxytests() {
}

void zdbproxytests::setUp() {
    app = new Poco::Util::ServerApplication;
}

void zdbproxytests::tearDown() {
    delete app;
}

void zdbproxytests::testMethod() {
    CPPUNIT_ASSERT(true);
}

void zdbproxytests::testDBConnection() {
    std::shared_ptr<ZDBProxy> db(new ZDBProxy());
    db->connect("localhost", 6379);
    
    CPPUNIT_ASSERT(db->isConnected());
}

void zdbproxytests::testDBGetSet() {
    std::shared_ptr<ZDBProxy> db(new ZDBProxy());
    db->connect("localhost", 6379);
    
    std::string key = "mykey";
    std::string value = "myvalue";
    std::string expected = "myvalue";
    
    CPPUNIT_ASSERT(db->SET(key, value));
    CPPUNIT_ASSERT(db->GET(key) == expected);
}

void zdbproxytests::testDBHash() {
    std::shared_ptr<ZDBProxy> db(new ZDBProxy());
    db->connect("localhost", 6379);
    
    std::string key = "myhash";
    std::string field = "email";
    std::string value = "huuhoa@gmail.com";
    std::string expected = "huuhoa@gmail.com";
    
    CPPUNIT_ASSERT(db->HSET(key, field, value));
    CPPUNIT_ASSERT(db->HGET(key, field) == expected);
}

void zdbproxytests::testDBSets() {
    std::shared_ptr<ZDBProxy> db(new ZDBProxy());
    db->connect("localhost", 6379);

    std::string key = "list:doors:id";
    std::vector<std::string> list;
    for (int i=1; i<10; i++) {
        std::string s = std::to_string(i);
        list.push_back(s);
    }
    
    db->SADD(key, list);
    CPPUNIT_ASSERT(db->SISMEMBER(key, std::to_string(8)));
    CPPUNIT_ASSERT(db->SREM(key, { std::to_string(4) }) == 1);
    CPPUNIT_ASSERT(!db->SISMEMBER(key, std::to_string(4)));
    CPPUNIT_ASSERT(db->DEL({key}) == 1);
}
