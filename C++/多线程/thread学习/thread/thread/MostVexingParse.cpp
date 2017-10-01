/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               �����ߣ� Josan
 *             ����ʱ�䣺 2017/10/1 14:41:57
 */
#include <iostream>
#include <typeinfo>
using namespace std;

#define TEST_CASE(name) static void name()

class Timer
{
public:
	Timer()
	{

	}
};

class TimeKeeper
{
public:
	TimeKeeper(const Timer& t)
	{

	}

	int get_time()
	{
		return 0;
	}
};

TEST_CASE(test_with_classes)
{
	TimeKeeper time_keeper(Timer());  //NOTE:ע���������  Timer()û�н���Ϊ��ʱ����Timer tmp; ���ǽ����ɺ���ָ�룬��������Ϊ�գ�����ֵΪTimer
	TimeKeeper time_keeper1((Timer()));
	TimeKeeper time_keeper2(Timer{});


	cout << typeid(time_keeper).name() << endl;  //class TimeKeeper __cdecl(class Timer  (__cdecl*)(void))
	cout << typeid(time_keeper1).name() << endl;  //class TimeKeeper
	cout << typeid(time_keeper2).name() << endl;  //class TimeKeeper

	//time_keeper.get_time();   //error
	time_keeper1.get_time();  //ok
	time_keeper2.get_time();  //ok
}

void f(double adouble)
{
	//takes an integer and returns an integer
	int i0(int adouble);

	int i(int());

	// declares a variable called 'i'
	int i1((int)adouble);
	// declares a variable called 'i'
	int i2(static_cast<int>(adouble));

	cout << typeid(i0).name() << endl;  //int __cdecl(int)
	cout << typeid(i).name() << endl;  //int __cdecl(int (__cdecl*)(void))
	cout << typeid(i1).name() << endl;  //int
	cout << typeid(i2).name() << endl;  //int

}




TEST_CASE(test_with_functions)
{
	f(5);
}

int main02()
{
	//test_with_classes();
	test_with_functions();
	return 0;
}