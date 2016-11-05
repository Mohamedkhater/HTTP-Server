/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Socket.cpp
 * Author: root
 * 
 * Created on November 3, 2016, 8:07 PM
 */

#include "GenericSocket.h"

GenericSocket::GenericSocket() : socketLogFile() {
    _debug = true;
}

GenericSocket::GenericSocket(int fileDescriptor) : socketLogFile() {
    this->setSocket(fileDescriptor);
    _debug = true;
}

GenericSocket::~GenericSocket() {
    ::close(_fileDescriptor);
    this->log("Socket closed");
}

void GenericSocket::setSocket(int fileDescriptor) {
    this->_fileDescriptor = fileDescriptor;
}

int GenericSocket::getSocket() {
    return _fileDescriptor;
}

void GenericSocket::log(const std::string message) {
    if (_debug)
        std::cout << message << std::endl;
    socketLogFile.write(message);
}




