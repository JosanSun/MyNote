/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/10/2 15:10:51
 */
#include <iostream>
using namespace std;

int main()
{
	//伪常量测试
	{
		const int a = 100;
		int * b = const_cast<int *>(&a);
		++*b;
		cout << *b << endl;  //101
		cout << a << endl;  //100  编译器优化，其实a的值已经变为101  调试的时候，也可以验证这点
	}
	{
		volatile const int a = 100;
		int * b = const_cast<int *>(&a);
		++*b;
		cout << *b << endl;  //101
		cout << a << endl;  //101  指定volatile 去除编译器优化，可以得到101
	}

	return 0;
}