/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/22 16:58:59
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//final有3个语法

/* declarator virt-specifier-seq(optional) pure-specifier(optional)	(1)
 * declarator virt-specifier-seq(optional) function-body	(2)
 * class-key attr(optional) class-head-name class-virt-specifier(optional) base-clause(optional)	(3)
 */

/* 使用说明
 * In the cases (1,2), virt-specifier-seq, if used, is either override or final, or final override or override final. In the case (3), the only allowed value of class-virt-specifier, if used, is final
 */
struct Base
{
	virtual void foo();
	virtual void funTest() final = 0;   //(1)
};

struct A : Base
{
	void foo() final; //(2) A::foo is overridden and it is the final override
	//void bar() final; // Error01: non-virtual function cannot be overridden or be final
};

struct B final : A //(3) struct B is final
{
	//void foo() override; // Error02: foo cannot be overridden as it's final in A
};

struct C //: B // Error03: B is final
{
};

int main()
{
	return 0;
}