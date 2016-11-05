/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServerSocket.cpp
 * Author: root
 * 
 * Created on November 4, 2016, 12:56 AM
 */

#include "ServerSocket.h"

ServerSocket::ServerSocket() {
}

ServerSocket::ServerSocket(int port, int keepAlive) {
    listen(port, keepAlive);
}

ServerSocket::~ServerSocket() {
}

void ServerSocket::listen(int port, int keepAlive) {

    serverAddr.sin_port = htons(port);
    serverAddr.sin_family = AF_INET; // IP v4
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // inet_aton("127.0.0.1", &serverAddr.sin_addr);

    setSocket(::socket(AF_INET, SOCK_STREAM, 0));

    if (getSocket() < 0)
        throw SocketException("Server Socket Creation: Error opening socket");
    if (setsockopt(getSocket(), SOL_SOCKET, SO_KEEPALIVE, &keepAlive, sizeof (keepAlive)) < 0)
        // if (setsockopt(getSocket(), SOL_SOCKET, SO_REUSEADDR, &keepAlive, optionLen) < 0)
        throw SocketException("Server Socket Creation: Error setting socket options");
    if (::bind(getSocket(), (struct sockaddr*) &serverAddr, sizeof (serverAddr)) < 0) {
        std::cout << std::strerror(errno) << std::endl;
        throw SocketException("Server Socket Binding: Error binding socket to port");
    }

    ::listen(getSocket(), 5);

    clientLen = sizeof (clientAddr);

    log("Server Socket: Listening for clients on port " + std::to_string(port));
}

int ServerSocket::accept() {
    // use accept that is in global namespace
    int client = ::accept(getSocket(), (struct sockaddr*) &clientAddr, &clientLen);

    if (client < 0) {
        throw SocketException("Server Socket Accepting: Error accepting new client connection");
    }

    log("Server Socket: Accepted new client");

    return client;
}
