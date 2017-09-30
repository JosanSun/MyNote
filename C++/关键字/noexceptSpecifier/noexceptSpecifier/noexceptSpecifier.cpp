/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/22 16:16:19
 */
#include <iostream>
#include <vector>
#include <string>
#include <exception>
using namespace std;

//NOTE: noexcept 等价于 throw()

void f() noexcept
{
	try
	{
		throw exception("my test");
	}
	catch(exception& e)
	{
		cout << e.what() << endl;
		//throw(e);   //noexcept对这个throw()进行限制
	}
}  // the function f() does not throw
void f() noexcept(true);  // the function f() does not throw
void f1() noexcept(false);  // the function f1() that may throw
void f1()
{
	try
	{
		throw exception("my test");
	}
	catch(exception& e)
	{
		cout << e.what() << endl;
		throw(e);
	}
}  // the function f1() that may throw
void(*fp)() noexcept(false);  // fp points to a function that may throw
//void(*fp)();    这个属于指针重定义
void g(void pfa() noexcept);  // g takes a pointer to function that doesn't throw
//typedef int (*pf)() noexcept;  // error  异常规范不能出现在typedef声明中


void f2() noexcept;
//void f2(); // error: different exception specification
void g2() noexcept(false);
void g2(); // ok, both declarations for g are potentially-throwing

class Base
{
public:
	virtual double f1(double) noexcept;  //不会抛出异常
	virtual int f2() noexcept(false);  //可能抛出异常
	virtual void f3();  //可能抛出异常
};

class Derived : public Base
{
public:
	//double f1(double);  //error  错误，异常规范发生错误
	int f2() noexcept(false);  //ok  一致
	void f3()noexcept;  //ok  不一致，但是可以通过
};


int main()
{
	void(*p1)()noexcept = f;
	void(*p2)() = f;

	//void(*p3)()noexcept = f1;  //不兼容的异常规范
	void(*p4)() = f1;

	try
	{
		p1();
	}
	catch(exception& e)
	{
		cout << e.what() << endl;
	}

	try
	{
		p4();
	}
	catch(exception& e)
	{
		cout << e.what() << endl;
	}

	
	return 0;
}