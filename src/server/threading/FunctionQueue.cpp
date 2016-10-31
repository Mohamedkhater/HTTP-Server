/* 
 * File:   FunctionQueue.cpp
 * Author: amr
 * 
 * Created on October 25, 2016, 9:24 PM
 */

#include "FunctionQueue.h"

template<typename T>
bool FunctionQueue<T>::empty() {
    std::unique_lock<std::mutex> lock(this->mutex);
    return this->queue.empty();
}

template<typename T>
T& FunctionQueue<T>::pop() {
    std::unique_lock<std::mutex> lock(this->mutex);
    if (this->empty()) {
        return nullptr;
    }

    T& value = this->queue.front();

    this->queue.pop();

    return value;
}

template<typename T>
void FunctionQueue<T>::push(const T& value) {
    std::unique_lock<std::mutex> lock(this->mutex);
    this->queue.push(value);
}

template<typename T>
void FunctionQueue<T>::clear() {
    T* t;
    while (this->queue.pop(t)) {
        delete t;
    }
}
