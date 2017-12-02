/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               �����ߣ� Josan
 *             ����ʱ�䣺 2017/10/5 14:03:23
 */

#include <iostream>
#include <algorithm>
using namespace std;
#define TEST_CASE(name)  static void name()

namespace josan
{
	// TEMPLATE CLASS remove_reference
	template<class _Ty>
	struct remove_reference
	{	// remove reference
		typedef _Ty type;
	};

	template<class _Ty>
	struct remove_reference<_Ty&>
	{	// remove reference
		typedef _Ty type;
	};

	template<class _Ty>
	struct remove_reference<_Ty&&>
	{	// remove rvalue reference
		typedef _Ty type;
	};
}

TEST_CASE(test_reference)
{
	josan::remove_reference<int>::type a1 = 10;
	josan::remove_reference<int&>::type a2 = 10;
	josan::remove_reference<int&&>::type a3 = 10;
	cin.get();
}

TEST_CASE(test)
{
	//���õ��ԣ����й۲�����
	test_reference();
}

int main()
{

	test();

	return 0;
}