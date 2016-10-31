/* 
 * File:   FunctionQueue.h
 * Author: amr
 *
 * Created on October 25, 2016, 9:24 PM
 */

#ifndef FUNCTIONQUEUE_H
#define	FUNCTIONQUEUE_H

#include <queue>
#include <mutex>

template <typename T>
class FunctionQueue {
public:
    void push(T const&);
    T& pop();
    bool empty();
    void clear();

private:
    std::queue<T> queue;
    std::mutex mutex;

};

#endif	/* FUNCTIONQUEUE_H */

