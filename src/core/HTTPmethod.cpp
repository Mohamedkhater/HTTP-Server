/* 
 * File:   HTTPmethod.cpp
 * Author: amr
 * 
 * Created on October 24, 2016, 10:05 PM
 */

#include "HTTPmethod.h"

HTTPmethod::HTTPmethod() {
}

HTTPmethod::~HTTPmethod() {
}

void HTTPmethod::set(std::string method) {
    std::transform(method.begin(), method.end(), method.begin(), ::toupper);
    if (method == "GET") {
        this->set(GET);
    } else if (method == "POST") {
        this->set(POST);
    } else if (method == "HEAD") {
        this->set(HEAD);
    } else if (method == "PUT") {
        this->set(PUT);
    } else if (method == "DELETE") {
        this->set(DELETE);
    } else {
        this->set(NOT_IMPLEMENTED);
    }
}

void HTTPmethod::set(Method method) {
    _method = method;
}

Method HTTPmethod::get() {
    return _method;
}

std::string HTTPmethod::getString() {
    if (_method == GET) {
        return "GET";
    } else if (_method == POST) {
        return "POST";
    } else if (_method == HEAD) {
        return "HEAD";
    } else if (_method == PUT) {
        return "PUT";
    } else if (_method == DELETE) {
        return "DELETE";
    }
    return "NOT_IMPLEMENTED";
}
