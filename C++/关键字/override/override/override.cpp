/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               �����ߣ� Josan
 *             ����ʱ�䣺 2017/9/22 17:53:28
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//override specifier
//Specifies that [a virtual function] overrides another virtual function.
//override������д��������Ա����

//��final���жԱ�
/* �﷨
 * declarator virt-specifier-seq(optional) pure-specifier(optional)	(1)
 * declarator virt-specifier-seq(optional) function-body	(2)
 */

struct A
{
	virtual void foo(){ }
	void bar();
	//virtual void fun() override = 0;  //error override������д����ĳ�Ա����
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

//void B::foo() override    //�޷����룬ֻ�ܷ��������������ܷ��ڶ��崦��
//{
//
//}

struct C : B
{
	//void foo() final override;   //error  ������C cc;��˴������ж���
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