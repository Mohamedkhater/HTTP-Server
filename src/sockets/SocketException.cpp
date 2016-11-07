/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SocketException.cpp
 * Author: root
 * 
 * Created on November 3, 2016, 8:20 PM
 */


#include "SocketException.h"

SocketException::SocketException(const std::string message) {
    this->message = message + "\n";
}

SocketException::~SocketException() {
}

const char* SocketException::what() const throw () {
    return this->message.c_str();
}
