#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <chrono>
#include <random>
#include <mutex>
#include "BlockQueue.h"
#include "ThreadPool.h"

#define BEGIN_TEST(name)    std::cout << "开始[" << name << "]测试!" << std::endl
#define END_TEST(name)      std::cout << "[" << name << "]测试完成!" << std::endl

int count = 0;
const int iMax = 100000;

std::mutex mtx;

typedef std::function<void(int)>    CALLBACK;

void print(int val)
{
	std::lock_guard<std::mutex> lg(mtx);
	std::cout << "thread ID: " << std::this_thread::get_id() << " Get From Queu: " << val << std::endl;
}

void test_threadpool()
{
    BEGIN_TEST("threadpool");

    typedef std::function<void()>   TASK;

    ThreadPool<TASK> tp(2);

    tp.DispatchTask([] {
        std::cout << "Hello " << std::this_thread::get_id() << std::endl;
    });

    END_TEST("threadpool");
}

int main()
{
	BlockQueue<CALLBACK> q;
	std::vector<std::thread> vecThread;

	for (int i = 0; i < 5; ++i)
	{
		vecThread.emplace_back([&, i] {
			while (true)
			{
                CALLBACK func = q.Pop();
                func(i);
			}
		});
	}

	for (auto& thr : vecThread)
		thr.detach();

    CALLBACK func = print;
	for (int i = 0; i < 10 ; i++)
	{
		q.Push(func);
	}

	using namespace std::chrono_literals;
	std::this_thread::sleep_for(5s);
	
    test_threadpool();

    return 0;
}

