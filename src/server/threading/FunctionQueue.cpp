/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FunctionQueue.cpp
 * Author: root
 * 
 * Created on November 3, 2016, 9:02 PM
 */

#include "FunctionQueue.h"

template<typename T>
FunctionQueue<T>::FunctionQueue() {
}

template<typename T>
FunctionQueue<T>::~FunctionQueue() {
}

template<typename T>
void FunctionQueue<T>::clear() {
    std::unique_lock<std::mutex> lock(this->_mutex);
    while (!this->_queue.empty()) {
        this->_queue.pop();
    }
}

template<typename T>
bool FunctionQueue<T>::empty() {
    std::unique_lock<std::mutex> lock(this->_mutex);
    return this->_queue.empty();
}

template<typename T>
T FunctionQueue<T>::pop() {
    std::unique_lock<std::mutex> lock(this->_mutex);
    T value = nullptr;
    if (this->empty()) {
        value = this->_queue.front();
        this->_queue.pop();
    }

    return value;
}

template<typename T>
void FunctionQueue<T>::push(const T& value) {
    std::unique_lock<std::mutex> lock(this->_mutex);
    this->_queue.push(value);
}
