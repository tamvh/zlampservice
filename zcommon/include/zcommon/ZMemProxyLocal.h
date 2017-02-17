/* 
 * File:   ZMemProxyLocal.h
 * Author: huuhoa
 *
 * Created on October 23, 2015, 1:48 PM
 */

#ifndef ZMEMPROXYLOCAL_H
#define	ZMEMPROXYLOCAL_H

#include <map>
#include <string>

#include "ZMemProxy.h"

class ZMemProxyLocal : public ZMemProxy {
public:
    ZMemProxyLocal();
    virtual ~ZMemProxyLocal();
public:
    virtual bool get(const std::string& collectionName, const std::string& key, std::string& value);
    virtual bool add(const std::string& collectionName, const std::string& key, const std::string& value);
    virtual bool remove(const std::string& collectionName, const std::string& key);
    virtual bool update(const std::string& collectionName, const std::string& key, const std::string& value);
private:
    typedef std::map<std::string, std::string> KeyValueCollection;
    typedef std::map<std::string, KeyValueCollection> Database;

    Database _database;
};

#endif	/* ZMEMPROXYLOCAL_H */

