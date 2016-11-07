/*
 * File:   Server.cpp
 * Author: root
 *
 * Created on November 3, 2016, 3:25 AM
 */

#include "Server.h"

Server::Server() : socket(PORT), pool(NUM_THREADS) {
    _port = PORT;
    bufferSize = BUFFER_SIZE;
    buffer = new char[bufferSize];
}

Server::Server(int port) : socket(port), pool(NUM_THREADS) {
    _port = port;
    bufferSize = BUFFER_SIZE;
    buffer = new char[bufferSize];
}

Server::~Server() {
    socket.~ServerSocket();
    client->~Socket();
}

void Server::run() {
    while (true) {
        client = new Socket(socket.accept());

        while (true) {
            try {
                // pool.push(handleRequest);
                // pool.push(&Server::handleRequest);
                pool.push([this]() {
                    return this->handleRequest;
                });
            } catch (SocketException e) {
                std::cout << e.what();

                if (((std::string)e.what()).find("Client disconnected") != std::string::npos) exit(0);

                break;
            }
        }
    }
}

void Server::handleRequest() {
    HTTPrequest* request = new HTTPrequest();
    HTTPresponse* response = new HTTPresponse();

    readRequest(request);
    processRequest(request, response);
    generateResponse(request, response);
    respond(response);
}

void Server::readRequest(HTTPrequest* request) {
    std::string requestStr = client->fetchMessage();
    request->set(requestStr);
}

void Server::processRequest(HTTPrequest* request, HTTPresponse* response) {
    request->Parse();

    Method method = request->getMethod();

    if (method == NOT_IMPLEMENTED) {
        response->setStatusCode(505);
        return;
    }

    switch (method) {
        case GET:
            getHandler(request, response);
            break;
        case POST:
            postHandler(request, response);
            break;
        default:
            // method not implemented
            response->setStatusCode(501);
    }
}

void Server::getHandler(HTTPrequest* request, HTTPresponse* response) {
    std::string fileUrl = root + request->getUrl();
    std::string mime = extractMime(request->getUrl());
    std::ifstream file;
    bool found = false;

    if (mime.find("image") != std::string::npos) {

        int fileSize = client->sendFile(fileUrl);
        if (fileSize != -1) {
            response->setStatusCode(200);
            response->setContentLength(fileSize);
            response->setResponseBody("");
            found = true;
        }
    } else {
        file.open(fileUrl);

        if (file) {
            readFromFile(file);
            response->setStatusCode(200);
            response->setResponseBody(buffer);
            found = true;
        }

        file.close();
    }

    if (!found) {
        fileUrl = (std::string)root + "404.html";
        file.open(fileUrl);
        readFromFile(file);
        file.close();

        response->setStatusCode(404);
        response->setResponseBody(buffer);
    }
}

void Server::generateResponse(HTTPrequest* request, HTTPresponse* response) {
    response->setProtocol(request->getProtocolString());
    if (response->getStatusCode() == 404) {
        response->setMimeType("text/html");
    } else {
        response->setMimeType(extractMime(request->getUrl()));
    }
    response->Build();
}

void Server::respond(HTTPresponse* response) {
    client->sendMessage(response->get());
}

void Server::readFromFile(std::ifstream& file) {
    // get length of file:
    file.seekg(0, std::ifstream::end);
    int length = file.tellg();
    file.seekg(0, std::ifstream::beg);

    if (length > bufferSize) {
        bufferSize = length;
        buffer = new char[bufferSize];
    }

    std::fill(buffer, buffer + bufferSize, 0);

    // read data as a block:
    file.read(buffer, bufferSize);

    file.close();
}

void Server::postHandler(HTTPrequest* request, HTTPresponse* response) {
    std::string content = client->fetchMessage();
    std::string fileNameString = "filename=\"";

    int pos1 = content.find(fileNameString) + fileNameString.length();
    int pos2 = content.find_first_of('\"', pos1);
    int pos3 = content.find_first_of("\r\n\r\n", pos2) + 4;
    int pos4 = content.find_first_of("\r\n\r\n", pos3) + 4;
    int pos5 = content.find_first_of("------", pos4);

    std::string fileName = content.substr(pos1, pos2 - pos1);

    int length = pos5 - pos4;

    if (length > bufferSize) {
        bufferSize = length;
        buffer = new char[bufferSize];
    }

    std::fill(buffer, buffer + bufferSize, 0);
    content.substr(pos4, pos5 - pos4).copy(buffer, length);

    std::string fileUrl = root + fileName;
    std::ofstream file;
    file.open(fileUrl, std::ofstream::out);
    file.write(buffer, length);
    file.close();
}


