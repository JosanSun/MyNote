/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/22 18:47:38
 */

#include <iostream>
using namespace std;

struct Abstract
{
	virtual void f() = 0; // pure virtual
	virtual void g()
	{
	}; // non-pure virtual
	~Abstract()
	{
		g(); // okay, calls Abstract::g()
		f(); // undefined behavior!  但是Visual Studio 2015可以运行
		Abstract::f(); // okay, non-virtual call
	}
};

//definition of the pure virtual function
void Abstract::f()
{
	std::cout << "A::f()\n";
}

struct Concrete : Abstract
{
	void f() override
	{
		Abstract::f(); // OK: calls pure virtual function
	}
	void g() override
	{
	}
	~Concrete()
	{
		g(); // okay, calls Concrete::g()
		f(); // okay, calls Concrete::f()
	}
};

int main()
{
	Concrete a;
	return 0;
}