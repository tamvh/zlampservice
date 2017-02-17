/*
 * File:   ErrorCode.h
 * Author: huuhoa
 *
 * Created on November 3, 2015, 4:58 PM
 */

#ifndef ZCOMMON_ERRORCODE_H
#define ZCOMMON_ERRORCODE_H

#include <cstdint>

enum class ZErrorCode : int32_t {
    OK = 0,
    // Common error codes for all services
    /// authentication is not succeeded because of invalid token
    Authentication_InvalidToken = 100,
    /// authentication is not succeeded because of invalid inputs (username, password)
    Authentication_InvalidUserNameOrPassword,
    /// authentication token is valid but expired
    Authentication_TokenExpired,
    /// authentication token is valid but exceeding numbers of allowed signin sessions
    Authentication_OverQuota,
    /// failed to generate authentication token
    Authentication_FailedToGenerateToken,

    // Starting code for HTTP service
    APIHTTP_Start = 1000,
    APIMQTT_Start = 1300,
    APIMQTT_ParameterMissing,
    
    APICOAP_Start = 1600,
    APIUSER_Start = 1900,
    /// Cannot get userinfo with given userId
    User_NotFound,
    User_PasswordIncorrect,
    User_Exists,
    /// Invalid email address
    User_InvalidEmailAddress,
    APIDEVICE_Start = 2500,
    /// Cannot get deviceinfo with given deviceId
    Device_NotFound,
    VarInfo_NotFound,
    APIADMIN_Start = 2800,
    WEBSOCKET_Start = 3000,
    Unknown = 9999
};


#endif /* ZCOMMON_ERRORCODE_H */

