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
using namespace std;

//NOTE: noexcept �ȼ��� throw()

void f() noexcept;  // the function f() does not throw
void f() noexcept(true);  // the function f() does not throw
void f1() noexcept(false);  // the function f1() that may throw
void f1();  // the function f1() that may throw
void(*fp)() noexcept(false);  // fp points to a function that may throw
//void(*fp)();    �������ָ���ض���
void g(void pfa() noexcept);  // g takes a pointer to function that doesn't throw
//typedef int (*pf)() noexcept;  // error  �쳣�淶���ܳ�����typedef������


void f2() noexcept;
//void f2(); // error: different exception specification
void g2() noexcept(false);
void g2(); // ok, both declarations for g are potentially-throwing

int main()
{
	return 0;
}