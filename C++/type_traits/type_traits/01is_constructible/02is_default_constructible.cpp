/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/29 11:02:59
 */
#include <iostream>
#include <type_traits>

struct Ex1
{
	std::string str; // member has a non-trivial default ctor
};
struct Ex2
{
	int n;
	Ex2() = default; // trivial and non-throwing
};

static void test()
{
	std::cout << std::boolalpha << "Ex1 is default-constructible? "
		<< std::is_default_constructible<Ex1>::value << '\n' //true
		<< "Ex1 is trivially default-constructible? "
		<< std::is_trivially_default_constructible<Ex1>::value << '\n'  //false
		<< "Ex2 is trivially default-constructible? "
		<< std::is_trivially_default_constructible<Ex2>::value << '\n'  //true
		<< "Ex2 is nothrow default-constructible? "
		<< std::is_nothrow_default_constructible<Ex2>::value << '\n';  //true
	
	std::cout << std::boolalpha << "Ex1 is nothrow default-constructible? "
		<< std::is_nothrow_default_constructible<Ex1>::value << '\n';  //true
}

int main02()
{
	test();
	
	return 0;
}