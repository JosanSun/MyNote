/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               �����ߣ� Josan
 *             ����ʱ�䣺 2017/9/22 16:16:19
 */
#include <iostream>
#include <vector>
#include <string>
#include <exception>
using namespace std;

//NOTE: noexcept �ȼ��� throw()

void f() noexcept
{
	try
	{
		throw exception("my test");
	}
	catch(exception& e)
	{
		cout << e.what() << endl;
		//throw(e);   //noexcept�����throw()��������
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
//void(*fp)();    �������ָ���ض���
void g(void pfa() noexcept);  // g takes a pointer to function that doesn't throw
//typedef int (*pf)() noexcept;  // error  �쳣�淶���ܳ�����typedef������


void f2() noexcept;
//void f2(); // error: different exception specification
void g2() noexcept(false);
void g2(); // ok, both declarations for g are potentially-throwing

class Base
{
public:
	virtual double f1(double) noexcept;  //�����׳��쳣
	virtual int f2() noexcept(false);  //�����׳��쳣
	virtual void f3();  //�����׳��쳣
};

class Derived : public Base
{
public:
	//double f1(double);  //error  �����쳣�淶��������
	int f2() noexcept(false);  //ok  һ��
	void f3()noexcept;  //ok  ��һ�£����ǿ���ͨ��
};


int main()
{
	void(*p1)()noexcept = f;
	void(*p2)() = f;

	//void(*p3)()noexcept = f1;  //�����ݵ��쳣�淶
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