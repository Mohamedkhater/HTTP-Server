/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClientSocket.h
 * Author: root
 *
 * Created on November 4, 2016, 2:15 AM
 */

#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "Socket.h"

#include <netdb.h>
#include <string.h>

class ClientSocket : public Socket {
public:
    ClientSocket();
    ClientSocket(std::string host, int port, int keepAlive = 1);
    virtual ~ClientSocket();

    void connect(std::string host, int port, int keepAlive = 1);

private:
    struct sockaddr_in serverAddr;
    struct hostent *server;
};

#endif /* CLIENTSOCKET_H */

