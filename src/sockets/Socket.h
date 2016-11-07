/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Socket.h
 * Author: root
 *
 * Created on November 3, 2016, 9:00 PM
 */

#ifndef SOCKET_H
#define SOCKET_H

#define BUFFER_SIZE 8*1024

#include "GenericSocket.h"

#include <string>

class Socket : public GenericSocket {
    /**
     * message format:
     * <message length> in 4 bits followed by
     * <message> message itself of specified length
     */
public:

    Socket(int);
    virtual ~Socket();

    void sendMessage(std::string);
    int sendFile(std::string);
    std::string fetchMessage();
    
    virtual void setSocket(int) override;
    virtual int getSocket() override;

protected:
    Socket();

    // Read incoming message and return buffer
    const unsigned char* getMessage();

    // Send raw message of length
    void sendMessage(const unsigned char*, int);

private:
    void readMessage(int);
    void writeMessage(const unsigned char*, int);

    int bufferSize;
    unsigned char* buffer;
    
    // for timeout
    fd_set readfds;
    struct timeval tv;
};

#endif /* SOCKET_H */

