/*
 * File:   httpCore.h
 * Author: amr
 *
 * Created on October 24, 2016, 9:42 PM
 */

#ifndef HTTPCORE_H
#define HTTPCORE_H

#include <string>
#include <algorithm>

#define SPACE ' '
#define CRLF "\r\n"
//#define root "../../../www"
#define root "/home/amr/NetBeansProjects/http-server/www/"
#define debug_mode true

enum Method {
    HEAD, GET, POST, PUT, DELETE, NOT_IMPLEMENTED
};

enum Protocol {
    HTTP1_0, HTTP1_1, UNSUPPORTED
};

std::string extractMime(std::string);

void log_error(std::string);

std::string trim(std::string);

#endif   /* HTTPCORE_H */
