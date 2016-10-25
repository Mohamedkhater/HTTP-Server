/* 
 * File:   HTTPrequest.cpp
 * Author: amr
 * 
 * Created on October 24, 2016, 9:31 PM
 */

#include "HTTPrequest.h"

HTTPrequest::HTTPrequest() {
    _method = new HTTPmethod();
    _protocol = new HTTPprotocol();
    _headers.clear();
    _request.clear();
    _requestBody.clear();
    _url.clear();
}

HTTPrequest::~HTTPrequest() {
}

void HTTPrequest::setHeader(std::string key, std::string value) {
    // _headers[key] = value;
    _headers.insert(std::pair<std::string, std::string>(key, value));
}

void HTTPrequest::set(std::string request) {
    _request = request;
}

std::string HTTPrequest::get() {
    return _request;
}

void HTTPrequest::setMethod(std::string method) {
    _method->set(method);
}

std::string HTTPrequest::getProtocolString() {
    return _protocol->getString();
}

Protocol HTTPrequest::getProtocol() {
    return _protocol->get();
}

void HTTPrequest::setProtocol(std::string protocol) {
    _protocol->set(protocol);
}

std::string HTTPrequest::getMethodString() {
    return _method->getString();
}

Method HTTPrequest::getMethod() {
    return _method->get();
}

bool HTTPrequest::Parse() {
    /* http request format:
     * <method> <request-URL> <version> CRLF
     * <headers> CRLF
     * CRLF
     * <request-body>*/

    size_t current_index = 0, next_index;

    // get method
    next_index = _request.find_first_of(SPACE);
    if (next_index == std::string::npos) {
        log_error("Parse Http Request Failed: Request method not implemented");
        return false;
    }
    setMethod(_request.substr(current_index, next_index - current_index));

    current_index = next_index + 1; // skip space

    // get url
    next_index = _request.find_first_of(SPACE, current_index);
    _url = _request.substr(current_index, next_index - current_index);

    current_index = next_index + 1; // skip space

    // get protocol
    next_index = _request.find_first_of(CRLF, current_index);
    if (next_index == std::string::npos) {
        log_error("Parse Http Request Failed: HTTP protocol not supported");
        return false;
    }
    _protocol->set(_request.substr(current_index, next_index - current_index));

    current_index = next_index + 2; // skip CRLF '\r\n'
    if (_request.substr(current_index, 2) == CRLF) {
        log_error("Parse Http Request Failed: No headers");
        return false;
    }

    // get headers
    while (_request.substr(current_index, 2) != CRLF) {
        // get each header
        next_index = _request.find_first_of(CRLF, current_index);
        if (next_index == std::string::npos) {
            log_error("Parse Http Request Failed: Invalid header");
            return false;
        }

        int temp_index = _request.find_first_of(':', current_index);
        if (temp_index == std::string::npos || temp_index > next_index) {
            log_error("Parse Http Request Failed: Invalid header, no \':\' between key and value.");
            return false;
        }

        this->setHeader(trim(_request.substr(current_index, temp_index - current_index)),
                trim(_request.substr(temp_index + 1, next_index - (temp_index + 1))));
        // temp_index + 1 to skip ':'

        current_index = next_index + 2;
    }

    // get request body
    if (_request.length() < 2) {
        log_error("Parse Http Request Failed: Wrong format after header.");
        return false;
    }
    current_index += 2; // skip CRLF
    _requestBody = _request.substr(current_index);
    
    return true;
}

void HTTPrequest::Build() {
    /* http request format:
     * <method> <request-URL> <version> CRLF
     * <headers> CRLF
     * CRLF
     * <request-body>*/
    
    _request = "";
    _request += getMethodString() + SPACE + _url + SPACE + getProtocolString() + CRLF;
    
    for (auto header: _headers) {
        _request += header.first + ": " + header.second + CRLF;
    }
    
    _request += CRLF;
    _request += _requestBody;
    
}
