/* 
 * File:   HTTPresponse.cpp
 * Author: amr
 * 
 * Created on October 25, 2016, 3:05 AM
 */

#include "HTTPresponse.h"

HTTPresponse::HTTPresponse() {
}

HTTPresponse::~HTTPresponse() {
}

int HTTPresponse::getStatusCode() {
    return _status->getStatusCode();
}

void HTTPresponse::setStatusCode(int code) {
    _status->setStatusCode(code);
}

void HTTPresponse::setStatusCode(std::string code_str) {
    int code = atoi(code_str.c_str());
    this->setStatusCode(code);
}

std::string HTTPresponse::getStatus() {
    return _status->getStatus();
}

std::string HTTPresponse::getHeader(std::string key) {
    return _headers.find(key)->second;
}

void HTTPresponse::setHeader(std::string key, std::string value) {
    _headers.insert(std::pair<std::string, std::string>(key, value));
}

Protocol HTTPresponse::getProtocol() {
    return _protocol->get();
}

std::string HTTPresponse::getProtocolString() {
    return _protocol->getString();
}

void HTTPresponse::setProtocol(std::string protocol) {
    _protocol->set(protocol);
}

std::string HTTPresponse::getMimeType() {
    return _mime_type;
}

void HTTPresponse::setMimeType(std::string mime_type) {
    _mime_type = mime_type;
}

void HTTPresponse::generateHeaders() {
    time_t cur_time;
    time(&cur_time);
    std::string cur_time_str = ctime(&cur_time);
    *cur_time_str.rbegin() = '\0';

    setHeader("Date", cur_time_str);
    setHeader("Server", "Bibo HTTP Server");
    setHeader("Accept-Ranges", "bytes");
    setHeader("Content-Type", getMimeType());
    setHeader("Connection", "close");
}

void HTTPresponse::Build() {
    /* Response data format:
     * <version> <status> <reason-phrase> CRLF
     * <header> CRLF
     * CRLF
     * <body> */

    _response = "";
    _response += this->getProtocolString() + SPACE + std::to_string(this->getStatusCode()) +
            SPACE + this->getStatus() + CRLF;

    for (auto header : _headers) {
        _response += header.first + ": " + header.second + CRLF;
    }

    _response += CRLF;
    _response += _responseBody;
}

bool HTTPresponse::Parse() {
    /* Response data format:
     * <version> <status> <reason-phrase> CRLF
     * <headers> CRLF
     * CRLF
     * <body>*/

    size_t current_index = 0, next_index;

    // get protocol
    next_index = _response.find_first_of(SPACE, current_index);
    if (next_index == std::string::npos) {
        log_error("Parse Http Response Failed: Response protocol not implemented.");
        return false;
    }
    this->setProtocol(_response.substr(current_index, next_index - current_index));

    current_index = next_index + 1; // skip space

    // get status code 
    next_index = _response.find_first_of(SPACE, current_index);
    if (next_index == std::string::npos) {
        log_error("Parse Http Response Failed: Status code not implemented.");
        return false;
    }
    this->setStatusCode(_response.substr(current_index, next_index - current_index));

    current_index = next_index + 1; // skip space

    next_index = _response.find_first_of(CRLF, current_index);
    // no need to get status message
    current_index = next_index + 2; // skip CRLF

    if (_response.substr(current_index, 2) == CRLF) {
        log_error("Parse Http Response Failed: No headers");
        return false;
    }

    while (_response.substr(current_index, 2) != CRLF) {
        // extract header 
        next_index = _response.find_first_of(CRLF, current_index);
        if (next_index == std::string::npos) {
            log_error("Parse Http Response Failed: Invalid header.");
            return false;
        }

        size_t temp_index = _response.find_first_of(':', current_index);
        if (temp_index == std::string::npos || temp_index > next_index) {
            log_error("Parse Http Response Failed: Invalid header, no \':\' between key and value.");
            return false;
        }
        this->setHeader(trim(_response.substr(current_index, temp_index - current_index)),
                trim(_response.substr(temp_index + 1, next_index - (temp_index + 1))));

        current_index = next_index + 2;
    }

    // get response body
    if (_response.length() < 2) {
        log_error("Parse Http Response Failed: Wrong format after header.");
        return false;
    }

    current_index += 2; // skip CRLF
    _responseBody = _response.substr(current_index);
    
    return true;
}
