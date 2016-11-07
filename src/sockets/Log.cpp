/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Log.cpp
 * Author: root
 * 
 * Created on November 3, 2016, 8:08 PM
 */

#include "Log.h"

Log::Log(std::string logFileName, bool isTimeStamped) {
    this->_isTimeStamped = isTimeStamped;

    this->_file.open(logFileName, std::fstream::out | std::fstream::app);
}

Log::~Log() {
    this->_file.close();
}

void Log::write(std::string data) {
    if (this->_isTimeStamped) {
        std::time_t t = std::time(NULL);
        this->_file << std::asctime(std::localtime(&t)) << ": " << data << std::endl;
    } else {
        this->_file << data << std::endl;
    }
}
