/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServerSocket.h
 * Author: root
 *
 * Created on November 4, 2016, 12:56 AM
 */

#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "GenericSocket.h"

#include <iostream>
#include <cerrno>
#include <cstring>

class ServerSocket : public GenericSocket {
public:
    ServerSocket();
    ServerSocket(int, int keepAlive = 1);
    virtual ~ServerSocket();

    void listen(int, int keepAlive = 1);
    int accept();

private:
    //serverAddr - address of server, clientAddr - address of connected client. 
    struct sockaddr_in serverAddr, clientAddr;
    //Size of the client address.
    socklen_t clientLen;
};

#endif /* SERVERSOCKET_H */

