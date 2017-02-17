/* 
 * File:   ZSessionService.h
 * Author: huuhoa
 *
 * Created on November 3, 2015, 4:55 PM
 */

#ifndef ZSESSIONSERVICE_H
#define	ZSESSIONSERVICE_H

#include <zcommon/ErrorCode.h>
#include <string>

class ZSessionService {
public:
    ZSessionService();
    virtual ~ZSessionService();
public:
    /// Validate existing authentication token
    /// @param token: authentication token to be validated
    /// @param userId when token is valid, userId is the id of user associated with token
    /// @return ZErrorCode::Authentication_*
    ZErrorCode validate(const std::string& token, int32_t& userId) const;
    ZErrorCode validate_jwt(const std::string& jwt, int32_t& userId) const;
    
    /// Create new authentication token for given userId
    /// @param token holds authentication token when success
    /// @return ZErrorCode::Authentication_*
    ZErrorCode create(int32_t userId, std::string& token);
    ZErrorCode create_jwt(int32_t userId, const std::string& claims, std::string& token);
private:

};

#endif	/* ZSESSIONSERVICE_H */

