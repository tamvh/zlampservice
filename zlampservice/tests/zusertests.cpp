/*
 * File:   zusertests.cpp
 * Author: huuhoa
 *
 * Created on Oct 23, 2015, 2:36:35 PM
 */

#include "zusertests.h"
#include <zcommon/ZDBProxy.h>
#include <zuser/ZUserInfo.h>

#include <string>
#include <sstream>
#include <memory>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(zusertests);

zusertests::zusertests() {
}

zusertests::~zusertests() {
}

void zusertests::setUp() {
}

void zusertests::tearDown() {
}

void zusertests::testMethod() {
    CPPUNIT_ASSERT(true);
}

void zusertests::testAddGetUser() {
    string collectionName = "users";
    
    shared_ptr<ZDBProxy> userDb = make_shared<ZDBProxy>();
    userDb->connect("localhost", 6379);

    ZUserInfo user;
    user.userId = 100;
    user.userName = "huuhoa";
    user.displayName = "Nguyen Huu Hoa";
    user.avatar = "none";
    user.password = "112233";
    user.createdAt = time(NULL);
    user.updatedAt = time(NULL);
    
    stringstream ikey;
    ikey << "users:" << user.userId;
    string key = ikey.str();
    
    CPPUNIT_ASSERT(userDb->SET(key, user.toString()));
    
    ZUserInfo nUser;
    string buffer;
    buffer = userDb->GET(key);
    nUser.fromString(buffer);
    
    CPPUNIT_ASSERT(user == nUser);

}