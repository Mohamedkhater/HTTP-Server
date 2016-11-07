/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClientSocket.cpp
 * Author: root
 * 
 * Created on November 4, 2016, 2:15 AM
 */

#include "ClientSocket.h"

ClientSocket::ClientSocket() {
}

ClientSocket::ClientSocket(std::string host, int port, int keepAlive) {
    connect(host, port, keepAlive);
}

ClientSocket::~ClientSocket() {
}

void ClientSocket::connect(std::string host, int port, int keepAlive) {

    server = gethostbyname(host.c_str());
    if (server == NULL)
        throw SocketException("Client Socket Creation: Error resolving hostname");

    serverAddr.sin_port = htons(port);
    serverAddr.sin_family = AF_INET;
    bcopy((char*) server->h_addr, (char*) &serverAddr.sin_addr.s_addr, server->h_length);

    setSocket(::socket(AF_INET, SOCK_STREAM, 0));

    if (getSocket() < 0)
        throw SocketException("Client Socket Creation: Error opening socket");
    if (setsockopt(getSocket(), SOL_SOCKET, SO_KEEPALIVE, &keepAlive, sizeof (keepAlive)) < 0) //Set TCP keepalive option.
        throw SocketException("Client Socket Creation: Error setting socket options");
    if (::connect(getSocket(), (struct sockaddr*) &serverAddr, sizeof (serverAddr)) < 0) //Connect to server.
        throw SocketException("Client Socket Connection: Error connecting to server");

    log("Client Socket: Connected to host");
}
