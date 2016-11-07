/*
 * File:   HTTPrequest.h
 * Author: amr
 *
 * Created on October 24, 2016, 9:31 PM
 */

#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>
#include <map>
#include "httpCore.h"
#include "HTTPmethod.h"
#include "HTTPprotocol.h"

class HTTPrequest {
public:
    HTTPrequest();
    virtual ~HTTPrequest();

    void set(std::string);
    std::string get();
    void setHeader(std::string, std::string);
    bool Parse();
    void Build();

    // helpers
    void setProtocol(std::string);
    std::string getProtocolString();
    Protocol getProtocol();

    void setMethod(std::string);
    std::string getMethodString();
    Method getMethod();

    void setUrl(std::string);
    std::string getUrl();

    std::string getRequestBody();


private:
    std::string _url;
    std::string _requestBody;
    std::string _request;
    HTTPmethod* _method;
    HTTPprotocol* _protocol;
    std::map<std::string, std::string> _headers;
};

#endif /* HTTPREQUEST_H */
