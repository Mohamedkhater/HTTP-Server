/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EasyThreadPool.h
 * Author: root
 *
 * Created on November 7, 2016, 11:38 PM
 */

#ifndef EASYTHREADPOOL_H
#define EASYTHREADPOOL_H

#define NUM_THREADS 3

#include <atomic>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>
#include <functional>
#include <condition_variable>

class EasyThreadPool {
public:
    EasyThreadPool(int ThreadCount = NUM_THREADS);
    virtual ~EasyThreadPool();

    /**
     *  Add a new job to the pool. If there are no jobs in the queue,
     *  a thread is woken up to take the job. If all threads are busy,
     *  the job is added to the end of the queue.
     */
    void AddJob(std::function<void(void) > job);

    /**
     *  Join with all threads. Block until all threads have completed.
     *  Params: WaitForAll: If true, will wait for the queue to empty 
     *          before joining with threads. If false, will complete
     *          current jobs, then inform the threads to exit.
     *  The queue will be empty after this call, and the threads will
     *  be done. After invoking `ThreadPool::JoinAll`, the pool can no
     *  longer be used. If you need the pool to exist past completion
     *  of jobs, look to use `ThreadPool::WaitAll`.
     */
    void JoinAll(bool WaitForAll = true);

    /**
     *  Wait for the pool to empty before continuing. 
     *  This does not call `std::thread::join`, it only waits until
     *  all jobs have finshed executing.
     */
    void WaitAll();

    /**
     *  Get the number of jobs left in the queue.
     */
    inline int JobsRemaining();


private:

    /**
     *  Get the next job; pop the first item in the queue, 
     *  otherwise wait for a signal from the main thread.
     */
    std::function<void(void) > NextJob();

    /**
     *  Take the next job in the queue and run it.
     *  Notify the main thread that a job has completed.
     */
    void Serve();

    std::vector<std::thread> threads;
    std::queue<std::function<void(void) >> queue;

    std::atomic_bool abort;
    std::atomic_bool finished;
    std::condition_variable job_available_var;
    std::condition_variable wait_var;
    std::mutex wait_mutex;
    std::mutex queue_mutex;
    int threadCount;
};

#endif /* EASYTHREADPOOL_H */

