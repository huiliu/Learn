#include "Polynomial.h"
#include <iostream>


void test1()
{
	Polynomial p(10);

	p.Attach(1.0, 1);
	p.Attach(2.0, 3);
	p.Attach(4.0, 5);
	p.Attach(8.0, 7);
	p.Attach(16.0, 9);

	p.Display();
}

void test0()
{
	Polynomial p(1);

	p.Attach(1.0, 1);
	p.Attach(2.0, 3);
	p.Attach(4.0, 5);

	p.Display();
}

void test2()
{
	Polynomial p1(5);

	p1.Attach(1.0, 1);
	p1.Attach(2.0, 3);
	p1.Attach(4.0, 5);

	p1.Display();

	Polynomial p2(5);

	p2.Attach(2.0, 3);
	p2.Attach(4.0, 5);

	p2.Display();

	p1.Add(p2);

	p1.Display();
	
}

void test3()
{
	Polynomial p1(5);

	p1.Attach(1.0, 1);
	p1.Attach(2.0, 3);
	p1.Attach(4.0, 4);

	p1.Display();
	p1.SingleMult(5.0, 1);

	p1.Display();
}

void test4()
{
	Polynomial p1(5);

	p1.Attach(1.0, 0);
	p1.Attach(2.0, 1);

	Polynomial p2(5);

	p2.Attach(1.0, 0);
	p2.Attach(2.0, 1);

	p1.Mult(p2);

	p1.Display();
}




int
main(int argc, char* argv[])
{
	test4();

	return 0;
}