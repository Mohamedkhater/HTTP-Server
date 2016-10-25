/* 
 * File:   HTTPstatus.h
 * Author: amr
 *
 * Created on October 25, 2016, 2:15 AM
 */

#ifndef HTTPSTATUS_H
#define	HTTPSTATUS_H

#include <string>

class HTTPstatus {
public:
    HTTPstatus();
    virtual ~HTTPstatus();
    
    int getStatusCode();
    void setStatusCode(int);
    std::string getStatus();
    
    
private:
    int _status_code;
    std::string _status_string;
    
    void setStatus();

};

#endif	/* HTTPSTATUS_H */

