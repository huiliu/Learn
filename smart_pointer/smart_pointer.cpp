// smart_pointer.cpp : 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include <memory>
#include <iostream>
#include <fstream>
#include "addressbook.pb.h"
#include "reflect_protobuf.h"


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

void test_smart_pointor()
{
	std::shared_ptr<cTest> sp(new cTest(100));

	sp->show();
}

typedef std::shared_ptr<tutorial::Person> spPersonType;

spPersonType test_protobuf()
{
	spPersonType person(new tutorial::Person());

	person->set_name("liuhui");
	person->set_id(1);
	person->set_email("liuhui@viivgame.cn");

	return person;
}

void test_read_and_write_protobuf()
{
	spPersonType sp = test_protobuf();

	std::ofstream of("hello");

	sp->SerializeToOstream(&of);

	of.close();

	std::fstream ifs("hello", std::ios::in || std::ios::binary);


	tutorial::Person person;
	person.ParseFromIstream(&ifs);
	person.SerializeToOstream(&std::cout);
}

int main()
{
	test_reflect_example();
    return 0;
}

