/* 
 * File:   ZLog.h
 * Author: tamvh
 *
 * Created on October 23, 2015, 2:06 PM
 */

#ifndef ZUSERINFO_H
#define ZUSERINFO_H

#include <map>
#include <list>
#include <string>
#include <vector>
#include <memory>

/// Hold basic user information

class ZLog {
public:
    typedef std::shared_ptr<ZLog> Ptr;
    typedef std::vector<Ptr> List;
    typedef std::map<int32_t, Ptr> Map;
    typedef std::vector<int32_t> KeyList;
public:
    ZLog();
public:
    void setUserName(const std::string& value);
    std::string userName() const;
            
    void setType(const int16_t value);
    int16_t type() const;       
    void setCreatedAt(const int64_t value);
    int64_t createdAt() const;   
private:
    std::string _userName;
    int16_t _type;
    int64_t _createdAt;
};

#endif /* ZUSERINFO_H */

