///*
// * ---------------------------------------------------
// *  Copyright (c) 2017 josan All rights reserved.
// * ---------------------------------------------------
// *
// *               创建者： Josan
// *             创建时间： 2017/9/22 15:08:44
// */
//#include <iostream>
//using namespace std;
//
//class E
//{
//public:
//	const char* error;
//	E(const char* arg) : error(arg)
//	{
//	};
//};
//
//class A
//{
//public:
//	A() try
//	{
//		throw E("Exception in A()");
//	}
//	catch(E& e)
//	{
//		cout << "Handler in A(): " << e.error << endl;
//	}
//};
//
//int f() try
//{
//	throw E("Exception in f()");
//	return 0;
//}
//catch(E& e)
//{
//	cout << "Handler in f(): " << e.error << endl;
//	//NOTE: 此处必须返回一个int型的整数，否则会出现“不是所有的控件路径都有返回值”Warning
//	return 1;
//}
//
///*
// * The run time will rethrow an exception at the end of a function try block's handler of a constructor or destructor. 
// * All other functions will return once they have reached the end of their function try block's handler. 
// * The following example demonstrates this:
// */
//int main()
//{
//	int i = 0;
//	try
//	{
//		A cow;
//	}
//	//此处抓住异常
//	catch(E& e)
//	{
//		cout << "Handler in main(): " << e.error << endl;
//	}
//
//	try
//	{
//		i = f();
//	}
//	//此处没有抓住
//	catch(E& e)
//	{
//		cout << "Another handler in main(): " << e.error << endl;
//	}
//
//	cout << "Returned value of f(): " << i << endl;
//
//	return 0;
//}