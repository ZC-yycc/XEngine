#ifndef XTHREADPOOL_H
#define XTHREADPOOL_H
/*
        线程池类
利用线程池实现Invoke
*/
#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

class XThreadPool {
public:
    XThreadPool(size_t numThreads);

    ~XThreadPool();

    template <class F, class... Args>
    void enqueue(F&& f, const long &&delay = 0, Args &&... args) {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            if (bStop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            tasks.emplace([f, delay, args...] { 
                std::this_thread::sleep_for(std::chrono::milliseconds((long)delay));
                f(args...); 
            });
        }
        condition.notify_one();
    }
    void addThread();
    inline static XThreadPool* getThreadPoolObj() {
        if (thread_pool_obj_ == nullptr) thread_pool_obj_ = new XThreadPool(10);
        return thread_pool_obj_;
    }
private:
    static XThreadPool                      *thread_pool_obj_;
    std::vector<std::thread>                workers;
    std::queue<std::function<void()>>       tasks;
    std::mutex                              queueMutex;
    std::condition_variable                 condition;
    bool                                    bStop;
};

#endif