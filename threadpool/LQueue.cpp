#include "LQueue.h"



LQueue::LQueue()
{
}


LQueue::~LQueue()
{
}

void LQueue::Push(int val)
{
	std::lock_guard<std::mutex> lg(m_mutex);

	if (m_queue.size() <= 0)
	{
		m_queue.push(val);
		m_cond.notify_all();

		return;
	}

	m_queue.push(val);
}

int LQueue::Pop()
{
	std::unique_lock<std::mutex> ul(m_mutex);

	while (m_queue.size() <= 0)
	{
		m_cond.wait(ul);
	}
	
	int ret = m_queue.front();
	m_queue.pop();
	
	return ret;
}
