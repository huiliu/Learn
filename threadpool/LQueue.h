#pragma once
#ifndef __THREAD_POOL_LQUEUE_H__
#define __THREAD_POOL_LQUEUE_H__

#include <queue>
#include <mutex>
#include <condition_variable>

class LQueue
{
public:
	LQueue();
	~LQueue();

public:

	void Push(int val);
	int  Pop();

private:
	std::queue<int> m_queue;
	std::mutex		m_mutex;
	std::condition_variable m_cond;
};

#endif

