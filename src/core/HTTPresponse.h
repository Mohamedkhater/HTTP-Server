/* 
 * File:   HTTPresponse.h
 * Author: amr
 *
 * Created on October 25, 2016, 3:05 AM
 */

#ifndef HTTPRESPONSE_H
#define	HTTPRESPONSE_H

#include <string>
#include <map>
#include "HTTPprotocol.h"
#include "HTTPstatus.h"

class HTTPresponse {
public:
    HTTPresponse();
    virtual ~HTTPresponse();
    
    void setHeader(std::string, std::string);
    std::string getHeader(std::string);
    void generateHeaders();
    bool Parse();
    void Build();
    
    // helpers
    void setStatusCode(int);
    void setStatusCode(std::string);
    int getStatusCode();
    std::string getStatus();
    
    void setProtocol(std::string);
    std::string getProtocolString();
    Protocol getProtocol();
    
    void setMimeType(std::string);
    std::string getMimeType();
    
private:
    HTTPstatus* _status;
    HTTPprotocol* _protocol;
    std::string _mime_type;
    std::string _responseBody;
    std::string _response;
    std::map<std::string, std::string> _headers;

};

#endif	/* HTTPRESPONSE_H */

