/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/22 10:29:53
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct sometype
{
	void* operator new(std::size_t) = delete;
	static void* operator new[](std::size_t) = delete;

	////错误0： 只能出现在函数的第一个声明中
	//friend void fun(int a);   //error
	friend void fun1(int a) = delete;  //ok
};

//NOTE: = delete可以应用于成员函数，同时也可以应用于普通函数
void fun(int a) = delete;  //ok
void fun1(int a);
static void fun2(int a2) = delete;  //ok

////错误2： =delete  只能出现在函数的第一个声明中
//struct sometype2
//{
//	sometype2();
//};
//sometype2::sometype2() = delete; // error: must be deleted on the first declaration

////Or  错误2： =delete  只能出现在函数的第一个声明中
//struct sometype2
//{
//	sometype2() = delete;
//};
//sometype2::sometype2() = delete{
//
//}// error: must be deleted on the first declaration

//struct sometype3
//{
//	int a;
//	void set(int aa) = delete;
//};
//
////错误3： 函数set已有主体
//void sometype3::set(int aa) 
//{
//	a = aa;
//}

//struct sometype4
//{
//	int a;
//	//错误4： 尝试引用已删除的函数
//	void set(int aa) = delete{
//		a = aa;
//	}
//};

struct sometype5
{
	sometype5()
	{

	}
	~sometype5() = delete;   //ok,但是不能声明对象
};

class Shape
{
public:
	Shape(const Shape&) = delete; // no copy operations
	Shape& operator=(const Shape&) = delete;

	Shape(Shape&&) = delete; // no move operations
	Shape& operator=(Shape&&) = delete;
	~Shape()
	{

	}
	// ...
};

////测试对重载函数的影响  
//void test(int a) = delete;
//void test(int a, int b) = delete;
//void test(int a, int b, double d)
//{
//	cout << "test is called.\n" << endl;
//}

static void testDeletedFuctions()
{
	////错误1： 无法引用new，它是已delete的函数
	//sometype* p = new sometype; // error: attempts to call deleted sometype::operator new
	////错误5： 尝试引用~sometype5()这个已删除的函数
	//sometype5 aa;

	//test(1);  //error
	//test(1, 2);  //error
	//test(1, 2, 3);  //ok
}

int main()
{
	testDeletedFuctions();
	
	return 0;
}