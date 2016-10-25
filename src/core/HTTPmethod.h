/* 
 * File:   HTTPmethod.h
 * Author: amr
 *
 * Created on October 24, 2016, 10:05 PM
 */

#ifndef HTTPMETHOD_H
#define	HTTPMETHOD_H

#include <string>
#include <algorithm>
#include "http.h"

class HTTPmethod {
public:
    HTTPmethod();
    virtual ~HTTPmethod();
    
    void set(std::string);
    void set(Method);
    
    Method get();
    std::string getString();
    
private:
    Method _method;

};

#endif	/* HTTPMETHOD_H */

