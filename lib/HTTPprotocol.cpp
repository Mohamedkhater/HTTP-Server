/* 
 * File:   HTTPprotocol.cpp
 * Author: amr
 * 
 * Created on October 24, 2016, 11:17 PM
 */

#include "HTTPprotocol.h"

HTTPprotocol::HTTPprotocol() {
}

HTTPprotocol::HTTPprotocol(const HTTPprotocol& orig) {
}

HTTPprotocol::~HTTPprotocol() {
}

void HTTPprotocol::set(Protocol protocol) {
    _protocol = protocol;
}

void HTTPprotocol::set(std::string protocol) {
    if (protocol == "HTTP/1.0") {
        set(HTTP1_0);
    } else if (protocol == "HTTP/1.1") {
        set(HTTP1_1);
    } else {
        set(UNSUPPORTED);
    }
}

Protocol HTTPprotocol::get() {
    return _protocol;
}

std::string HTTPprotocol::getString() {
    if(_protocol == HTTP1_0) {
        return "HTTP/1.0";
    }
    else if(_protocol == HTTP1_1) {
        return "HTTP/1.1";
    }
    else {
        return "UNSUPPORTED";
    }
}
