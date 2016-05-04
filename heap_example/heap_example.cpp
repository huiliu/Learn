// heap_example.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <algorithm>
#include <vector>
#include <iostream>

template<typename T>
void print(const T& t)
{
	for (auto& item : t)
	{
		std::cout << item << '\t';
	}
	std::cout << std::endl;
}

void test_heap() 
{
	int ia[] = { 0,1,2,3,4,7,9,8,5 };
	std::vector<int> iv(ia, ia + 9);

	std::make_heap(iv.begin(), iv.end());
	print(iv);

	iv.push_back(6);
	std::push_heap(iv.begin(), iv.end());
	print(iv);

	std::pop_heap(iv.begin(), iv.end());
	iv.pop_back();
	print(iv);
}

void test_copy()
{
	char chello[] = "Hello World!";
	char buff[100] = { 0 };

	std::copy(chello, chello + sizeof(chello), buff);
	std::cout << buff << std::endl;
}

int main()
{
	test_copy();
	test_heap();
    return 0;
}

