/* 
 * File:   ZMemProxy.h
 * Author: huuhoa
 *
 * Created on October 23, 2015, 1:42 PM
 */

#ifndef ZMEMPROXY_H
#define	ZMEMPROXY_H

#include <map>
#include <string>

class ZMemProxy {
public:
    ZMemProxy();
    virtual ~ZMemProxy();
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

#endif	/* ZMEMPROXY_H */

