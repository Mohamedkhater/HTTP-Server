/*
 * File:   Server.h
 * Author: root
 *
 * Created on November 3, 2016, 3:25 AM
 */

#ifndef SERVER_H
#define SERVER_H

#define PORT 3130
#define BUFFER_SIZE 8*1024

#include "../sockets/Socket.h"
#include "../sockets/ServerSocket.h"
#include "../core/http.h"
#include "threading/ThreadPool.h"
#include "threading/EasyThreadPool.h"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>

class Server {
public:
    Server();
    Server(int);
    virtual ~Server();

    void run();
    void handleRequest();


private:
    void readRequest(HTTPrequest*);
    void processRequest(HTTPrequest*, HTTPresponse*);
    void generateResponse(HTTPrequest*, HTTPresponse*);
    void respond(HTTPresponse*);

    void getHandler(HTTPrequest*, HTTPresponse*);
    void postHandler(HTTPrequest*, HTTPresponse*);

    void readFromFile(std::ifstream&);
    void readBinary(std::ifstream&);
    void writeToFile();

    ServerSocket socket;
    Socket* client;
    //    ThreadPool pool;
    EasyThreadPool pool;

    int _port;
    int bufferSize;
    char* buffer;

};
#endif   /* SERVER_H */

