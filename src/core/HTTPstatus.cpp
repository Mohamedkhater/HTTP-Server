/* 
 * File:   HTTPstatus.cpp
 * Author: amr
 * 
 * Created on October 25, 2016, 2:15 AM
 */

#include "HTTPstatus.h"

HTTPstatus::HTTPstatus() {
    _status_code = 0;
    _status_string = "Initializing";
}

HTTPstatus::~HTTPstatus() {
}

std::string HTTPstatus::getStatus() {
    return _status_string;
}

int HTTPstatus::getStatusCode() {
    return _status_code;
}

void HTTPstatus::setStatusCode(int status_code) {
    _status_code = status_code;
    this->setStatus();
}

void HTTPstatus::setStatus() {
    if (_status_code == 100) {
        _status_string = "Continue";
    } else if (_status_code == 101) {
        _status_string = "Switching Protocols";
    } else if (_status_code == 200) {
        _status_string = "OK";
    } else if (_status_code == 201) {
        _status_string = "Created";
    } else if (_status_code == 400) {
        _status_string = "Bad Request";
    } else if (_status_code == 403) {
        _status_string = "Forbidden";
    } else if (_status_code == 404) {
        _status_string = "Not Found";
    } else if (_status_code == 411) {
        _status_string = "Length Required";
    } else if (_status_code == 500) {
        _status_string = "Internal Server Error";
    } else if (_status_code == 501) {
        _status_string = "Not Implemented";
    } else if (_status_code == 502) {
        _status_string = "Bad Gateway";
    } else if (_status_code == 505) {
        _status_string = "HTTP Version Not Supported";
    }
}
