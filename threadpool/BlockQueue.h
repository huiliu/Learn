#pragma once
#ifndef __THREAD_POOL_LQUEUE_H__
#define __THREAD_POOL_LQUEUE_H__

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class BlockQueue
{
public:
    BlockQueue() {}
    ~BlockQueue() {}

public:

	void Push(T val)
    {
        std::lock_guard<std::mutex> lg(m_mutex);

        m_queue.push(val);

        if (m_queue.size() <= 1)
        {
            m_cond.notify_all();
        }
    }

	T Pop()
    {
        std::unique_lock<std::mutex> ul(m_mutex);

        while (m_queue.size() <= 0)
        {
            m_cond.wait(ul);
        }
        
        T ret = m_queue.front();
        m_queue.pop();
	
        return ret;
    }

private:
	std::queue<T>   m_queue;
	std::mutex		m_mutex;
	std::condition_variable m_cond;
};

#endif

