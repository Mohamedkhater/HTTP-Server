/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SocketException.h
 * Author: root
 *
 * Created on November 3, 2016, 8:20 PM
 */

#ifndef SOCKETEXCEPTION_H
#define SOCKETEXCEPTION_H

#include <exception>
#include <string>

class SocketException : public std::exception {
public:
    SocketException(const std::string);
    virtual ~SocketException();

    virtual const char* what() const throw () override;
private:
    std::string message;
};

#endif /* SOCKETEXCEPTION_H */

