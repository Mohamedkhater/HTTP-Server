/* 
 * File:   http.h
 * Author: amr
 *
 * Created on October 24, 2016, 9:42 PM
 */

#ifndef HTTP_H
#define	HTTP_H

#include <string>

#define SPACE ' '
#define CRLF "\r\n"
#define root "../www/"

enum Method {HEAD, GET, POST, PUT, DELETE, NOT_IMPLEMENTED};
enum Protocol {HTTP1_0, HTTP1_1, UNSUPPORTED};

std::string extractMime(std::string);

#endif	/* HTTP_H */

