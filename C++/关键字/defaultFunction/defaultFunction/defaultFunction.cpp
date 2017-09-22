/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/22 11:02:50
 */
#include <iostream>
#include <type_traits>
using namespace std;

struct X
{
	X() = default;
};

struct Y
{
	Y()
	{
	};
};

//NOYE: 只有以下六类特殊函数可以声明为 = default
/*
 * Special member functions
 * constructors and destructors are non-static member functions that use a special syntax for their declarations (see their pages for details).
 * Some member functions are special: under certain circumstances they are defined by the compiler even if not defined by the user. They are:

 * Default constructor
 * Copy constructor
 * Move constructor (since C++11)
 * Copy assignment operator
 * Move assignment operator (since C++11)
 * Destructor

 * Special member functions are the only functions that can be defaulted, that is, defined using = default instead of the function body (see their pages for details)
 */

class C
{
public:
	////错误1： 类型对于默认构造函数无效
	//C(int x) = default;
	C(int x) :a(x)
	{

	}
	C() = default;
	//错误2： C(C&) = default;和C(const C&) = default; 只能存在一个，如果二者都出现，就会报错。
	//C(C&) = default;
	C(const C&) = default;
	//错误3： C(const C&&) = default; 不是可默认为的特殊成员函数
	//C(const C&&) = default;
	C(C&&) = default;
	C& operator=(const C&) & = default;
	C& operator=(C&&) & = default;
	virtual ~C()
	{
	}
private:
	int a;
};

void testDefaultFunction()
{
	static_assert(std::is_trivial<X>::value, "X should be trivial");  //X是平凡的
	static_assert(std::is_pod<X>::value, "X should be POD");
	static_assert(!std::is_trivial<Y>::value, "Y should not be trivial");  //Y是普通类
	static_assert(!std::is_pod<Y>::value, "Y should not be POD");
	C c1;
	C c2(2);
}

int main()
{
	testDefaultFunction();
	return 0;
}

