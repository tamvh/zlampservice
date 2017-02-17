/*
 * File:   ZApiHTTP.h
 * Author: huuhoa
 *
 * Created on October 24, 2015, 3:18 PM
 */

#ifndef ZAPIHTTP_H
#define	ZAPIHTTP_H

#include <memory>
#include <zcommon/ZServiceInterface.h>

class ZApiHTTP : public ZServiceInterface {
public:
    ZApiHTTP();
    virtual ~ZApiHTTP();

public:
    virtual bool initialize();
    virtual bool start();
    virtual bool stop();
    virtual bool cleanup();
public:
    void writeserial(const std::string & lamp);
    std::string getSTTLamp1();
    std::string getSTTLamp2();
private:
    class Impl;
    std::shared_ptr<Impl> d_ptr;    
    
};

#endif	/* ZAPIHTTP_H */

