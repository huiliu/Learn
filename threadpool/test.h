#ifndef __THREADPOOL_TEST_H__
#define __THREADPOOL_TEST_H__
#include <iostream>

#define BEGIN_TEST(name)    std::cout << "��ʼ[" << name << "]����!" << std::endl
#define END_TEST(name)      std::cout << "[" << name << "]�������!" << std::endl

// test case
void test_threadpool();
#endif // !__THREADPOOL_TEST_H__

