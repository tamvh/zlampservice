/* 
 * File:   ZUserManager.h
 * Author: huuhoa
 *
 * Created on October 23, 2015, 2:05 PM
 */

#ifndef ZUSERMANAGER_H
#define ZUSERMANAGER_H

#include <zcommon/ZServiceInterface.h>
#include <zdevicemanager/ZLog.h>

class ZCoffeeManager : public ZServiceInterface {
public:
    ZCoffeeManager();
    virtual ~ZCoffeeManager();

public:
    virtual bool initialize();
    virtual bool start();
    virtual bool stop();
    virtual bool cleanup();

public:

    enum class ErrorCode : int32_t {
        OK = 0,
        NotFound,
        InvalidInput
    };

public:
    //writelog
    virtual int32_t create(const std::string& userName, const int16_t& type);

    /// Lấy thông tin về một tài khoản có sẵn
    virtual ZLog::Ptr get(int32_t userId);
    virtual ZLog::Ptr getWithUserKey(const std::string& userkey); //userkey = "users:21"
    virtual ZLog::Ptr get(const std::string& userName); //userName = email

    /// Lấy thông tin một số tài khoản theo danh sách khoá
    virtual ZLog::Map multiGet(const ZLog::KeyList& keyList);

    /// Lấy thông tin một số tài khoản theo danh sách tuần tự
    virtual ZLog::Map list(int32_t start, int32_t count);
   
private:
    void saveToDB(ZLog& logInfo);
};

#endif /* ZUSERMANAGER_H */

