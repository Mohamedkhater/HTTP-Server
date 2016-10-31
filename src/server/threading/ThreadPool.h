/* 
 * File:   ThreadPool.h
 * Author: amr
 *
 * Created on October 25, 2016, 9:14 PM
 */

#ifndef THREADPOOL_H
#define	THREADPOOL_H

#include "FunctionQueue.h"

#include <queue>
#include <mutex>
#include <functional>
#include <future>
#include <thread>
#include <atomic>
#include <vector>
#include <exception>
#include <condition_variable>

class ThreadPool {
public:
    ThreadPool();
    // ThreadPool(int);
    virtual ~ThreadPool();

    // auto multiply (int x, int y) -> int; \\ int multiply (int x, int y);
    // decltype(x) y = x; \\ same thing as auto y = x;


    /**
     * Adds the user defined function to the queue and
     * assigns a thread to it 
     * @param function rvalue of a user defined function
     * @return The returned value after invoking the function in the future
     */
    template<typename Function>
    auto push(Function&& function) -> std::future<decltype(function(0))>;

    /**
     * Adds the user defined function & passed params to the queue and
     * assigns a thread to it 
     * @param function rvalue of a user defined function
     * @return The returned value after invoking the function in the future
     */
    template<typename Function, typename... Params>
    auto push(Function&& function, Params&&... params) -> std::future<decltype(function(0, params...))>;

    // stop all threads
    void interrupt();


private:
    // assign a thread to a task
    void assignThread(int index);


    // attributes
    FunctionQueue<std::function<void(int) > *> _queue;
    std::vector<std::shared_ptr<std::thread>> _threads;
    std::vector<std::shared_ptr<std::atomic<bool>>> _abort; // abort thread

    std::atomic<int> _idleCount;
    std::mutex _mutex;
    std::condition_variable _condition;

};

#endif	/* THREADPOOL_H */

