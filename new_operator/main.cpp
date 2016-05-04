// new_operator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

class Widget
{
public:
	Widget(int i);
	~Widget();

	void	show();
private:
	int32_t m_data;
};

Widget::Widget(int i)
	: m_data(i)
{
}

Widget::~Widget()
{
}

void Widget::show()
{
	std::cout << m_data << std::endl;
}

void test0()
{
	void* pBuff = malloc(sizeof(Widget));
	Widget* pWidget = new(pBuff) Widget(10);

	pWidget->show();

	delete pWidget;
}

void test1()
{
	void* pBuff = operator new(sizeof(Widget));
	Widget* pWidget = new(pBuff)Widget(1000);

	pWidget->show();
	/*pWidget->~Widget();
	operator delete(pBuff);*/
	delete pWidget;
}

void test2()
{
	int32_t buff = 123;
	Widget* pWidget = new(&buff)Widget(1000);

	pWidget->show();

	delete pWidget;
}

void test3()
{
	char abc[] = "abc";
	char c = 'a';

	Widget* pWidget = new(&c)Widget(124);

	pWidget->show();
}

int main()
{
	//test0();
	test2();
    return 0;
}

