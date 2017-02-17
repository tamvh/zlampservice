#ifndef __ZDEVICE_ZDBKEY_H__
#define __ZDEVICE_ZDBKEY_H__

#include <string>

class ZDBKey {
public:
    //KEY generator
    static std::string generatorUsers();
    static std::string apiKey();
    
    static std::string UserSet();
    static std::string UserApiKey();
    static std::string UserEmail();
    static std::string UserEntry(int32_t userId);
    static std::string UserSession(int32_t userId);
    
    static std::string CoffeeLog();
};

#endif // __ZDEVICE_ZDBKEY_H__
