/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Socket.cpp
 * Author: root
 * 
 * Created on November 3, 2016, 9:00 PM
 */

#include <string.h>

#include "Socket.h"

Socket::Socket() {
    bufferSize = BUFFER_SIZE;
    buffer = new unsigned char [bufferSize];

    FD_ZERO(&readfds);
    FD_SET(getSocket(), &readfds);

    tv.tv_sec = 5;
    tv.tv_usec = 500000;
}

Socket::~Socket() {
    delete[] buffer;
}

void Socket::setSocket(int socket) {
    GenericSocket::setSocket(socket);
}

int Socket::getSocket() {
    return GenericSocket::getSocket();
}

void Socket::readMessage(int length) {
    // resize buffer
    if (length > bufferSize) {
        delete[] buffer;
        bufferSize = length + 1;
        buffer = new unsigned char[bufferSize];
    }

    int bytesRead = 0; //Bytes read on last pass.
    int totalBytesRead = 0;

    std::fill(buffer, buffer + bufferSize, 0);

    while (totalBytesRead < length) {

        int rv = ::select(getSocket() + 1, &readfds, NULL, NULL, &tv);

        if (rv == 0) {
            ::close(getSocket());
        }

        bytesRead = read(getSocket(), buffer + totalBytesRead, length - totalBytesRead); //Read the sent message.

        if (bytesRead < 0)
            throw SocketException("Message Reading: Error reading sent message");
        else if (bytesRead == 0)
            throw SocketException("Message Reading: Client disconnected");

        totalBytesRead += bytesRead;

        if (bytesRead < length)
            break;
    }

    std::string message((char*) buffer, length);
    log("Received message: \n" + message);
}

void Socket::writeMessage(const unsigned char* message, int length) {
    int bytesWritten = 0; //Bytes written on last pass.
    int totalBytesWritten = 0;

    while (totalBytesWritten < length) {
        bytesWritten = write(getSocket(), message + totalBytesWritten, length - totalBytesWritten);

        if (bytesWritten < 0)
            throw SocketException("Message Writing: Error writing message");
        else if (bytesWritten == 0)
            throw SocketException("Message Writing: Client disconnected");

        totalBytesWritten += bytesWritten;

        if (bytesWritten < length)
            break;
    }
}

int Socket::sendFile(std::string fileUrl) {
    int f = open(fileUrl.c_str(), O_RDONLY);
    if (f > 0) {
        struct stat stat_buf;
        fstat(f, &stat_buf);
        sendfile(getSocket(), f, 0, stat_buf.st_size);
        close(f);

        return (int) (stat_buf.st_size);
    }
    return -1;
}

const unsigned char* Socket::getMessage() {
    readMessage(bufferSize);
    return buffer;
}

void Socket::sendMessage(const unsigned char* message, int length) {
    writeMessage(message, length);

    std::string msg((char*) message, length);
    log("Sent message: \n" + msg);
}

Socket::Socket(int socket) : GenericSocket(socket) {
    bufferSize = BUFFER_SIZE;
    buffer = new unsigned char [bufferSize];

    FD_ZERO(&readfds);
    FD_SET(getSocket(), &readfds);

    tv.tv_sec = 5;
    tv.tv_usec = 500000;
}

void Socket::sendMessage(std::string message) {
    sendMessage((const unsigned char*) message.c_str(), message.length());
}

std::string Socket::fetchMessage() {
    std::string message((const char*) getMessage());
    return message;
}
