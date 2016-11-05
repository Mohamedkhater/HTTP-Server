/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Socket.h
 * Author: root
 *
 * Created on November 3, 2016, 8:07 PM
 */

#ifndef GENERIC_SOCKET_H
#define GENERIC_SOCKET_H

#include <iostream>
#include <unistd.h> // POSIX API definitions
#include <sys/types.h> // type (mainly time) definitions
#include <sys/socket.h> // sockets definitions
#include <netinet/in.h> // internet domain addresses definitions
#include <arpa/inet.h>

#include "Log.h"
#include "SocketException.h"

class GenericSocket {
protected:
    GenericSocket();
    GenericSocket(int fileDescriptor);
    virtual ~GenericSocket();

    void setSocket(int fileDescriptor);
    int getSocket();

    void log(const std::string);

private:
    int _fileDescriptor;
    Log socketLogFile;
    bool _debug;
};

#endif /* SOCKET_H */

