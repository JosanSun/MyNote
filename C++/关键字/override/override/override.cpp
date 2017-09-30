/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/22 17:53:28
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//override specifier
//Specifies that [a virtual function] overrides another virtual function.
//override不能重写基类的虚成员函数

//与final进行对比
/* 语法
 * declarator virt-specifier-seq(optional) pure-specifier(optional)	(1)
 * declarator virt-specifier-seq(optional) function-body	(2)
 */

struct A
{
	virtual void foo(){ }
	void bar();
	//virtual void fun() override = 0;  //error override不能重写基类的成员函数
	//virtual void fun1() override;  //error
	virtual void fun2() = 0
	{
		cout << "Hello2" << endl;
	}
	virtual void fun3() = 0
	{
		cout << "Hello3" << endl;
	}
};

struct B : A
{
	//void foo() const override; // Error: B::foo does not override A::foo
							   // (signature mismatch)
	void foo() override; // OK: B::foo overrides A::foo
	//void bar() override; // Error: A::bar is not virtual
	virtual void fun2() override
	{
		cout << "B:fun2" << endl;
	}
	virtual void fun3() override = 0;
};

void B::foo()
{

}

//void B::foo() override    //无法编译，只能放在声明处，不能放在定义处。
//{
//
//}

struct C : B
{
	//void foo() final override;   //error  若声明C cc;则此处必须有定义
	void foo() final override{ }
	void fun3() final override
	{
		cout << "C: fun3" << endl;
	}
};

int main()
{
	C cc;
	cc.fun3();
	return 0;
}