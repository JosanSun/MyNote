///*
// * ---------------------------------------------------
// *  Copyright (c) 2017 josan All rights reserved.
// * ---------------------------------------------------
// *
// *               创建者： Josan
// *             创建时间： 2017/9/22 14:56:55
// */
//void f(int &x) try
//{
//	throw 10;
//}
//catch(const int &i)
//{
//	x = i;
//}
//
//static void test01()
//{
//	int v = 0;
//	f(v);  //v = 10
//}
//
//class E
//{
//public:
//	const char* error;
//	E(const char* arg) : error(arg)
//	{
//	}
//};
//
//class A
//{
//public: ~A()
//{
//	throw E("Exception in ~A()");
//}
//};
//
//class B
//{
//public: ~B()
//{
//	throw E("Exception in ~B()");
//}
//};
//
//
//static void test02()
//{
//
//}
//
//static void test()
//{
//	test01();
//	test02();
//}
//
//int main()
//{
//	test();
//	return 0;
//}