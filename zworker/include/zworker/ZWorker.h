/*
 * File:   ZWorker.h
 * Author: huuhoa
 *
 * Created on November 30, 2015, 9:33 AM
 */

#ifndef ZWORKER_H
#define ZWORKER_H

#include <string>
#include <Poco/Dynamic/Var.h>
#include <Poco/BasicEvent.h>

#include <zcommon/ZServiceInterface.h>
#include <zcommon/ErrorCode.h>

class ZDeviceEvent;
class ZWorkerResult {
public:

    ZWorkerResult(ZErrorCode error) : error_(error) {
    }

    ZWorkerResult(Poco::Dynamic::Var obj) : obj_(obj), error_(ZErrorCode::OK) {
    }
public:

    ZErrorCode errorCode() const {
        return error_;
    }

    bool succeeded() const {
        return errorCode() == ZErrorCode::OK;
    }

    bool failed() const {
        return errorCode() != ZErrorCode::OK;
    }

    template <typename T>
    const T& extract() const {
        return obj_.extract<T>();
    }
private:
    Poco::Dynamic::Var obj_;
    ZErrorCode error_;
};

class ZWorker : public ZServiceInterface {
public:
    ZWorker();
    virtual ~ZWorker();

public:
    virtual bool initialize();
    virtual bool start();
    virtual bool stop();
    virtual bool cleanup();

public:
 
    //support for coffee machine
    ZWorkerResult ChooseCoffee(int32_t type);
    ZWorkerResult writeLogChooseCoffee(const std::string& username);
private:
    bool doesUserExist(int32_t userId);
public:
    //! @session Events
    //! All event broadcasted by worker such as choose coffee type, etc.
    Poco::BasicEvent<const ZDeviceEvent> chooseCoffeeEvent;
};

#endif /* ZWORKER_H */

