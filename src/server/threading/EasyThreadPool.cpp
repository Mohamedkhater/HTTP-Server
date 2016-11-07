/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EasyThreadPool.cpp
 * Author: root
 * 
 * Created on November 7, 2016, 11:38 PM
 */

#include "EasyThreadPool.h"

EasyThreadPool::EasyThreadPool(int ThreadCount) {
    abort = false;
    finished = false;
    threadCount = ThreadCount;

    threads.resize(threadCount);

    for (int i = 0; i < threadCount; i++) {
        threads[i] = std::move(std::thread([this, i]() {
            this->Serve();
        }));
    }
}

EasyThreadPool::~EasyThreadPool() {
    JoinAll();
}

void EasyThreadPool::AddJob(std::function<void(void) > job) {
    std::unique_lock<std::mutex> lock(queue_mutex);
    queue.push(job);
    job_available_var.notify_one();
}

std::function<void(void) > EasyThreadPool::NextJob() {
    std::function<void(void) > res;
    std::unique_lock<std::mutex> job_lock(queue_mutex);

    // Wait for a job if we don't have any.
    job_available_var.wait(job_lock, [this]() ->bool {
        return queue.size() || abort; });

    // Get job from the queue
    if (!abort) {
        res = queue.front();
        queue.pop();
    } else {
        // If we're aborting, 'inject' a job into the queue to keep jobs_left accurate.
        res = [] {
        };
    }
    return res;
}

void EasyThreadPool::Serve() {
    while (!abort) {
        NextJob()();
        wait_var.notify_one();
    }
}

void EasyThreadPool::JoinAll(bool WaitForAll) {
    if (!finished) {
        if (WaitForAll) {
            WaitAll();
        }

        // note that we're done, and wake up any thread that's
        // waiting for a new job
        abort = true;
        job_available_var.notify_all();

        for (auto &thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }

        finished = true;
    }
}

void EasyThreadPool::WaitAll() {
    if (JobsRemaining() > 0) {
        std::unique_lock<std::mutex> lock(wait_mutex);
        wait_var.wait(lock, [this] {
            return !this->JobsRemaining();
        });
        lock.unlock();
    }
}

int EasyThreadPool::JobsRemaining() {
    std::unique_lock<std::mutex> lock(queue_mutex);
    return queue.size();
}
