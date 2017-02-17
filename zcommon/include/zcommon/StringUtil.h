/*
 * File:   StringUtil.h
 * Author: huuhoa
 *
 * Created on October 30, 2015, 3:19 PM
 */

#ifndef STRINGUTIL_H
#define	STRINGUTIL_H

#include <vector>
#include <map>
#include <string>

class StringUtil {
public:
    static std::string join(const std::vector<std::string> &list, const std::string& separator);
    static std::string join(const std::map<std::string, std::string>& map, const std::string& separator);
    static std::vector<int32_t> convert(const std::vector<std::string> &list);
private:

};

#endif	/* STRINGUTIL_H */

