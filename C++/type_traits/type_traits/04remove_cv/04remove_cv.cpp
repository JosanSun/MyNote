/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/10/5 13:39:36
 */

#include <iostream>
using namespace std;
#define TEST_CASE(name)  static void name()

namespace josan
{
	// TEMPLATE CLASS remove_const
	template<class _Ty>
	struct remove_const
	{	// remove top level const qualifier
		typedef _Ty type;
	};

	template<class _Ty>
	struct remove_const<const _Ty>
	{	// remove top level const qualifier
		typedef _Ty type;
	};

	// TEMPLATE CLASS remove_volatile
	template<class _Ty>
	struct remove_volatile
	{	// remove top level volatile qualifier
		typedef _Ty type;
	};

	template<class _Ty>
	struct remove_volatile<volatile _Ty>
	{	// remove top level volatile qualifier
		typedef _Ty type;
	};

	// TEMPLATE CLASS remove_cv
	template<class _Ty>
	struct remove_cv
	{	// remove top level const and volatile qualifiers
		typedef typename remove_const<typename remove_volatile<_Ty>::type>::type
			type;
	};

}

TEST_CASE(test_remove_const)
{
	josan::remove_const<int>::type a1 = 10.0;
	josan::remove_const<const int>::type a2 = 10;
	josan::remove_const<volatile int>::type a3 = 10.0;
	josan::remove_const<const volatile int>::type a4 = 10.0;
	cin.get();
}

TEST_CASE(test_remove_volatile)
{
	josan::remove_volatile<int>::type a1 = 10.0;
	josan::remove_volatile<const int>::type a2 = 10;
	josan::remove_volatile<volatile int>::type a3 = 10.0;
	josan::remove_volatile<const volatile int>::type a4 = 10.0;
	cin.get();
}

TEST_CASE(test_remove_cv)
{
	josan::remove_cv<int>::type a1 = 10.0;
	josan::remove_cv<const int>::type a2 = 10;
	josan::remove_cv<volatile int>::type a3 = 10.0;
	josan::remove_cv<const volatile int>::type a4 = 10.0;
	cin.get();
}

TEST_CASE(test)
{
	//利用调试，进行观察类型
	test_remove_const();
	test_remove_volatile();
	test_remove_cv();
}

int main()
{

	test();

	return 0;
}