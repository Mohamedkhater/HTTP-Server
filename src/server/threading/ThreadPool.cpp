/* 
 * File:   ThreadPool.cpp
 * Author: amr
 * 
 * Created on October 25, 2016, 9:14 PM
 */

#include "ThreadPool.h"

ThreadPool::ThreadPool() {
    this->_idleCount = 0;
}

ThreadPool::~ThreadPool() {
}

template<typename Function>
auto ThreadPool::push(Function&& function) -> std::future<decltype(function(0))> {
    // make a pointer to the packaged (wrapped) task
    // we pass the function using std::forward to pass as rvalue
    auto package =
            std::make_shared < std::packaged_task < decltype(function(0)) (size_t)>> (std::forward<Function>(function));

    // send thread id to the task
    auto _function = new std::function<void(int) >([package](int id) {
        (*package)(id);
    });

    // add to queue
    this->_queue.push(_function);

    std::unique_lock<std::mutex> lock(this->_mutex);
    // wake up a thread to run the function
    this->_condition.notify_one();

    // return function return value
    return package->get_future();
}

template<typename Function, typename... Params>
auto ThreadPool::push(Function&& function, Params&&... params) -> std::future<decltype(function(0, params...))> {
    // make a pointer to the packaged (wrapped) task
    // we pass the function using std::forward to pass as rvalue
    auto package = std::make_shared < std::packaged_task < decltype(function(0)) (size_t)>> (
            std::bind(std::forward<Function>(function), std::placeholders::_1, std::forward<Params>(params)...)
            );

    // send thread id to the task
    auto _function = new std::function<void(int) >([package](int id) {
        (*package)(id);
    });

    // add to queue
    this->_queue.push(_function);

    std::unique_lock<std::mutex> lock(this->_mutex);
    // wake up a thread to run the function
    this->_condition.notify_one();

    // return function return value
    return package->get_future();
};

void ThreadPool::assignThread(int index) {
    std::shared_ptr < std::atomic<bool>> abort_ptr(this->_abort[index]);

    auto f = [this, index, abort_ptr]() {
        std::atomic<bool> & abort = *abort_ptr;

        // get a task from queue
        std::function<void(int) > * _function = nullptr;
        _function = this->_queue.pop();

        // always pop a function from the queue
        // as long as it is not empty or there is no abort command
        while (true) {
            while (_function != nullptr) {
                // convert _function to a smart pointer to 
                // delete ptr after thread finishes
                std::unique_ptr < std::function<void(int) >> func(_function);

                // call the function
                (*_function)(index);

                if (abort)
                    return;
                else
                    _function = this->_queue.pop();
            }

            // queue is empty, wait for a function to be pushed
            // and a signal to wake up a thread
            std::unique_lock<std::mutex> lock(this->_mutex);
            ++this->_idleCount;
            this->_condition.wait(lock, [this, &_function, &abort]() {
                _function = this->_queue.pop();
                return abort || (_function != nullptr);
            });
            --this->_idleCount;

            if (_function == nullptr)
                return;

        }

    };
}

void ThreadPool::interrupt() {
    
}

