/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               �����ߣ� Josan
 *             ����ʱ�䣺 2017/9/22 10:29:53
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct sometype
{
	void* operator new(std::size_t) = delete;
	static void* operator new[](std::size_t) = delete;

	////����0�� ֻ�ܳ����ں����ĵ�һ��������
	//friend void fun(int a);   //error
	friend void fun1(int a) = delete;  //ok
};

//NOTE: = delete����Ӧ���ڳ�Ա������ͬʱҲ����Ӧ������ͨ����
void fun(int a) = delete;  //ok
void fun1(int a);
static void fun2(int a2) = delete;  //ok

////����2�� =delete  ֻ�ܳ����ں����ĵ�һ��������
//struct sometype2
//{
//	sometype2();
//};
//sometype2::sometype2() = delete; // error: must be deleted on the first declaration

////Or  ����2�� =delete  ֻ�ܳ����ں����ĵ�һ��������
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
////����3�� ����set��������
//void sometype3::set(int aa) 
//{
//	a = aa;
//}

//struct sometype4
//{
//	int a;
//	//����4�� ����������ɾ���ĺ���
//	void set(int aa) = delete{
//		a = aa;
//	}
//};

struct sometype5
{
	sometype5()
	{

	}
	~sometype5() = delete;   //ok,���ǲ�����������
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

////���Զ����غ�����Ӱ��  
//void test(int a) = delete;
//void test(int a, int b) = delete;
//void test(int a, int b, double d)
//{
//	cout << "test is called.\n" << endl;
//}

static void testDeletedFuctions()
{
	////����1�� �޷�����new��������delete�ĺ���
	//sometype* p = new sometype; // error: attempts to call deleted sometype::operator new
	////����5�� ��������~sometype5()�����ɾ���ĺ���
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