/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Log.h
 * Author: root
 *
 * Created on November 3, 2016, 8:08 PM
 */

#ifndef LOG_H
#define LOG_H

#include <string>
#include <fstream>
#include <ctime>

class Log {
public:
    Log(std::string logFileName = "Log.txt", bool isTimeStamped = true);
    virtual ~Log();
    
    void write(std::string data);
private:
    std::fstream _file;
    bool _isTimeStamped;
};

#endif /* LOG_H */

