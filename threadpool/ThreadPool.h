#pragma once
#ifndef __LIUHUI_THREADPOOL_H__
#define __LIUHUI_THREADPOOL_H__
#include "BlockQueue.h"

template<typename T>
class ThreadPool
{
public:
    ThreadPool(size_t sz)
        : m_PoolSize(sz)
    {
        std::function<void()> backend = std::bind(&ThreadPool::Daemon, this);
        for (size_t i = 0; i < sz; i++)
        {
            m_Threads.push_back(std::thread(backend));
        }
    }

    ~ThreadPool()
    {
        for (size_t i = 0; i < m_PoolSize; i++)
        {
            m_TaskQueue.Push(T());
        }

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
        m_PoolSize += num;

        for (size_t i = 0; i < num; i++)
        {
            m_Threads.push_back(std::thread(Daemon));
        }
    }

    void DecThread(size_t num)
    {
        m_PoolSize -= num;

        for (size_t i = 0; i < num; i++)
        {
            m_TaskQueue.Push(T());
        }
    }

private:
    void Daemon()
    {
        while (true)
        {
            T func = m_TaskQueue.Pop();
            if (func)
            {
                func();
            }
            else
            {
                break;
            }
        }
    }

private:
    size_t                      m_PoolSize;
    BlockQueue<T>               m_TaskQueue;
    std::vector<std::thread>    m_Threads;
};

#endif // !__LIUHUI_THREADPOOL_H__
