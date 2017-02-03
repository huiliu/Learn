#ifndef __LIUHUI_THREADPOOL_H__
#define __LIUHUI_THREADPOOL_H__
#include "BlockQueue.h"

// 退出线程标识
#define EXIT_THREAD     -1

template<typename T>
class ThreadPool
{
public:
    ThreadPool(size_t sz)
    {
        IncThread(sz);
    }

    ~ThreadPool()
    {
        auto count = m_Threads.size();
        DecThread(count);

        for (auto& thr : m_Threads)
            thr.join();
    }

public:
    void DispatchTask(T val)
    {
        m_TaskQueue.Push(val);
    }
    
    void IncThread(size_t num)
    {
        std::function<void()> backend = std::bind(&ThreadPool::Daemon, this);
        for (size_t i = 0; i < num; i++)
        {
            m_Threads.push_back(std::thread(backend));
        }
    }

    void DecThread(size_t num)
    {
        for (size_t i = 0; i < num; i++)
        {
            DispatchTask([] { return EXIT_THREAD; });
        }
    }

private:
    void Daemon()
    {
        std::cout << "new thread " << std::this_thread::get_id() << " created!" << std::endl;

        while (true)
        {
            T func = m_TaskQueue.Pop();
            if (func && func() == EXIT_THREAD)
            {
                std::cout << std::this_thread::get_id() << " thread exit!" << std::endl;
                return;
            }
        }
    }

private:
    BlockQueue<T>               m_TaskQueue;
    std::vector<std::thread>    m_Threads;
};

#endif // !__LIUHUI_THREADPOOL_H__
