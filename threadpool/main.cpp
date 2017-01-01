#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <chrono>
#include <random>
#include <mutex>
#include "LQueue.h"

int count = 0;
const int iMax = 100000;

std::mutex mtx;

void print(std::thread::id& id, int val)
{
	std::lock_guard<std::mutex> lg(mtx);
	std::cout << "thread ID: " << id << " Get From Queu: " << val << std::endl;
}

int main()
{
	LQueue q;
	std::vector<std::thread> vecThread;

	for (int i = 0; i < 2; ++i)
	{
		vecThread.emplace_back([&] {
			while (true)
			{
				print(std::this_thread::get_id(), q.Pop());
			}
		});
	}

	for (auto& thr : vecThread)
		thr.detach();

	std::random_device rd;
	for (int i = 0; i < 10 ; i++)
	{
		q.Push(i);
	}

	using namespace std::chrono_literals;
	std::this_thread::sleep_for(5s);
	
    return 0;
}

