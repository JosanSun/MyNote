///*
// * ---------------------------------------------------
// *  Copyright (c) 2017 josan All rights reserved.
// * ---------------------------------------------------
// *
// *               �����ߣ� Josan
// *             ����ʱ�䣺 2017/9/22 18:41:24
// */
//#include <iostream>
//#include <vector>
//#include <string>
//using namespace std;
//
//struct Base
//{
//	virtual int g(); 
//	virtual ~Base()
//	{
//	}
//};
//struct A : Base
//{
//	// ok, declares three member virtual functions, two of them pure
//	virtual int f() = 0, g() override = 0, h();   //��Ϥ������3������������ʽ
//	 
//	// ok, destructor can be pure too
//	~A() = 0;
//	// error: pure-specifier on a function definition
//	virtual int b() = 0
//	{
//	}
//};
//
//int main()
//{
//
//	return 0;
//}