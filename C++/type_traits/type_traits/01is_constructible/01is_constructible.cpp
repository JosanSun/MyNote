/*
* ---------------------------------------------------
*  Copyright (c) 2017 josan All rights reserved.
* ---------------------------------------------------
*
*               创建者： Josan
*             创建时间： 2017/9/29 10:35:57
*/

// test is_constructible, is_trivially_constructible  and is_nothrow_constructible
#include <iostream>
#include <type_traits>

class Foo
{
	int v1;
	double v2;
public:
	Foo(int n) : v1(n), v2()
	{
	}
	Foo(int n, double f) noexcept : v1(n), v2(f)
	{
	}
};

static void test_is_constructible()
{
	std::cout << "Foo is ...\n" << std::boolalpha
		<< "\tConstructible from int? "
		<< std::is_constructible<Foo, int>::value << '\n'  //true
		<< "\tConstructible from int double? "
		<< std::is_constructible<Foo, int, double>::value << '\n'  //true
		<< typeid(std::is_constructible<Foo, int, double>::type).name() << '\n'
		<< typeid(std::is_constructible<Foo, int, double>::value_type).name() << '\n'
		<< "\tConstructible from const Foo&? "
		<< std::is_constructible<Foo, const Foo&>::value << '\n';  //true

	//-----------other--------------
	std::cout << "Foo is ...\n" << std::boolalpha
		<< "\tConstructible from double int? "
		<< std::is_constructible<Foo, double, int>::value << '\n';  //true   因为存在类型转换
	std::cout << "Foo is ...\n" << std::boolalpha
		<< "\tConstructible from double* int? "
		<< std::is_constructible<Foo, double*, int>::value << '\n';  //false
	std::cout << "Foo is ...\n" << std::boolalpha
		<< "\tConstructible from double int int? "
		<< std::is_constructible<Foo, double, int, int>::value << '\n';  //false
	std::cout << "Foo is ...\n" << std::boolalpha
		<< "\tConstructible from double int? "
		<< std::is_constructible<Foo, double, int>::value << '\n';
}

static void test_is_trivially_constructible()
{
	std::cout << "Foo is ...\n" << std::boolalpha
		<< "\tTrivially-constructible from const Foo&? "
		<< std::is_trivially_constructible<Foo, const Foo&>::value << '\n'  //true
		<< "\tTrivially-constructible from int? "
		<< std::is_trivially_constructible<Foo, int>::value << '\n'  //false
		<< "\tTrivially-constructible from int and double? "
		<< std::is_trivially_constructible<Foo, int, double>::value << '\n'; //false
}

static void test_is_nothrow_constructible()
{
	std::cout << "Foo is ...\n" << std::boolalpha
		<< "\tNothrow-constructible from int? "
		<< std::is_nothrow_constructible<Foo, int>::value << '\n'  //false
		<< "\tNothrow-constructible from int and double? "
		<< std::is_nothrow_constructible<Foo, int, double>::value << '\n'  //true
		<< "\tNothrow-constructible from const Foo&? "
		<< std::is_nothrow_constructible<Foo, const Foo&>::value << '\n';  //Note: true
}

static void test()
{
	test_is_constructible();
	//test_is_trivially_constructible();
	//test_is_nothrow_constructible();
}

int main01()
{
	test();
	return 0;
}