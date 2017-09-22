/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               �����ߣ� Josan
 *             ����ʱ�䣺 2017/9/22 19:17:14
 */
#include <iostream>
using namespace std;

/*
 * Within the function body, the function-local predefined variable __func__ is defined as if by
 * -----  static const char __func__[] = "function-name";  -----
 * This variable has block scope and static storage duration:
 */

struct S
{
	S() : s(__func__)
	{
		cout << s << endl;
	} // okay: initializer-list is part of function body
	const char* s;
};


//������__func__ֻ���ں����ڲ�ʹ��
//void f(const char* s = __func__); // error: parameter-list is part of declarator  

void myFun()
{
	cout << __func__ << endl;  //myFun
}


int main()
{
	S ss;
	myFun();
	return 0;
}