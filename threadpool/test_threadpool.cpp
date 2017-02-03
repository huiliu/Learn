#include "test.h"
#include "BlockQueue.h"
#include "ThreadPool.h"
#include <functional>

typedef std::function<int()>   TASK;

std::mutex mtx;

void output()
{
    std::lock_guard<std::mutex> lg(mtx);

    std::cout << "Hello " << std::this_thread::get_id() << std::endl;
}

void test_threadpool()
{
    BEGIN_TEST("threadpool");

    // create two threads
    ThreadPool<TASK> tp(2);

    // dispatch task to thread pool
    tp.DispatchTask([] {
        output();
        return 0;
    });

    // increase thread count
    tp.IncThread(3);

    // decrease thread count
    tp.DecThread(4);

    END_TEST("threadpool");
}
