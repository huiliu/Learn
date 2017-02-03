#ifndef __THREADPOOL_TEST_H__
#define __THREADPOOL_TEST_H__
#include <iostream>

#define BEGIN_TEST(name)    std::cout << "开始[" << name << "]测试!" << std::endl
#define END_TEST(name)      std::cout << "[" << name << "]测试完成!" << std::endl

// test case
void test_threadpool();
#endif // !__THREADPOOL_TEST_H__

