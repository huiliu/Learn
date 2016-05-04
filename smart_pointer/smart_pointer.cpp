// smart_pointer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <memory>
#include <iostream>

class cTest
{
public:
	cTest(int i);
	~cTest();

	void show() const;
private:
	int m_data;
};

cTest::cTest(int i)
	: m_data(i)
{
}

cTest::~cTest()
{
}

void cTest::show() const
{
	std::cout << m_data << std::endl;
}

int main()
{
	std::shared_ptr<cTest> sp(new cTest(100));

	sp->show();
    return 0;
}

