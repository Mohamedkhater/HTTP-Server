/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FunctionQueue.h
 * Author: root
 *
 * Created on November 3, 2016, 9:02 PM
 */

#ifndef FUNCTIONQUEUE_H
#define FUNCTIONQUEUE_H

#include <queue>
#include <mutex>

template<typename T>
class FunctionQueue {
public:
    FunctionQueue();
    virtual ~FunctionQueue();

    void push(const T& value);
    T pop();
    bool empty();
    void clear();

private:
    std::queue<T> _queue;
    std::mutex _mutex;

};

#endif /* FUNCTIONQUEUE_H */

