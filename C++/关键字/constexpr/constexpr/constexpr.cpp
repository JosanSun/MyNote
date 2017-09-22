/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/22 19:33:57
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

constexpr int f();
const bool b1 = noexcept(f()); // false, undefined constexpr function  注意noexcept()是操作符，不是函数。
constexpr bool b3 = noexcept(f());

int f1()
{
	return 0;
}
const bool B1 = noexcept(f()); // false, undefined constexpr function
constexpr bool B3 = noexcept(f());

constexpr int f()
{
	return 0;
}
constexpr bool b2 = noexcept(f()); // true, f() is a constant expression

template<int N>
class list
{
};

constexpr int sqr1(int arg)
{
	return arg * arg;
}

int sqr2(int arg)
{
	return arg * arg;
}

class A
{
private:
	int x;
public:
	constexpr void fun() const;
	//constexpr void fun1();   //必须显示指定const
};

constexpr void A::fun() const
{
	
}

constexpr const int N = 5;
//等价于 constexpr int N = 5;

static constexpr int N1 = 3;

int main()
{
	//constexpr表示NP不能指向其他元素  const表示NP指向的元素是常量
	constexpr const int *NP = &N1; 
	//NP = &N;  //error
	const int *NP1 = &N1;
	NP1 = &N;  //ok
	
	
	const int X = 2;
	list<sqr1(X)> mylist1;  // OK: sqr1 is constexpr
	//list<sqr2(X)> mylist2;  // wrong: sqr2 is not constexpr
	return 0;
}
