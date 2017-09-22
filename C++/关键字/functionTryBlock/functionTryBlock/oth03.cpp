///*
// * ---------------------------------------------------
// *  Copyright (c) 2017 josan All rights reserved.
// * ---------------------------------------------------
// *
// *               创建者： Josan
// *             创建时间： 2017/9/22 15:06:18
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
//class B
//{
//public:
//	B()
//	{
//	};
//	~B()
//	{
//		cout << "~B() called" << endl;
//	};
//};
//
//class D : public B
//{
//public:
//	D();
//	~D()
//	{
//		cout << "~D() called" << endl;
//	};
//};
//
//D::D() try : B()
//{
//	throw E("Exception in D()");
//}
//catch(E& e)
//{
//	cout << "Handler of function try block of D(): " << e.error << endl;
//};
//
//int main()
//{
//	{
//		try
//		{
//			D val;
//		}
//		catch(...)
//		{
//		}
//	}
//	//Output: 
//	//~B() called
//	//Handler of function try block of D() : Exception in D()
//	return 0;
//}