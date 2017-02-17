/* 
 * File:   ZServiceInterface.h
 * Author: huuhoa
 *
 * Created on October 26, 2015, 2:00 PM
 */

#ifndef ZSERVICEINTERFACE_H
#define	ZSERVICEINTERFACE_H

class ZServiceInterface {
public:
    virtual ~ZServiceInterface() {}
public:
    /// Initialize the service
    virtual bool initialize() = 0;
    
    /// Start service, service will serve until it is stopped by calling stop method
    virtual bool start() = 0;
    
    /// Stop service
    virtual bool stop() = 0;
    
    /// Cleanup resources using by service
    virtual bool cleanup() = 0;
private:

};

#endif	/* ZSERVICEINTERFACE_H */

