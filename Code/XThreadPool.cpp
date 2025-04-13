#include "XThreadPool.h"

XThreadPool* XThreadPool::thread_pool_obj_ = nullptr;

XThreadPool::XThreadPool(size_t numThreads)
    : bStop(false) 
{
    for (size_t i = 0; i < numThreads; ++i) {
        addThread();
    }
}

XThreadPool::~XThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        bStop = true;
    }

    condition.notify_all();

    for (std::thread& worker : workers) {
        worker.join();
    }
}

void XThreadPool::addThread()
{
    workers.emplace_back([this] {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                condition.wait(lock, [this] { return bStop || !tasks.empty(); });

                if (bStop && tasks.empty()) return;

                task = std::move(tasks.front());
                tasks.pop();
            }
            task();
        }
    });
}
