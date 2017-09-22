/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/22 14:47:06
 */
#include <iostream>
#include <cassert>
#include <string>
using namespace std;

/* Function-try-block
 * Establishes an exception handler around the body of a function.
 */

struct S
{
	std::string m;
	S(const std::string& arg) try : m(arg, 100)
	{
		std::cout << "constructed, mn = " << m << '\n';
	}
	catch(const std::exception& e)
	{
		std::cerr << "arg=" << arg << " failed: " << e.what() << '\n';
	} // implicit throw; here
};

int f(int n = 2) try
{
	++n; // increments the function parameter
	throw n;
}
catch(...)
{
	++n; // n is in scope and still refers to the function parameter
	assert(n == 4);
	return n;
}

/*
 * 在ctor和dtor的异常会自动rethrow。
 * Any exceptions caught in constructors or destructors are rethrown implicitly: "The currently handled exception is rethrown if control reaches the end of a handler of the function-try-block of a constructor or destructor" (15.3.15 C++ International Standard (Draft)/n3337). Hence, the most you can do when catching an exception in such context is to log it and possibly run some clean-up code. This is a good thing. If the construction of an object fails for whatever reason, you should not attempt to "save" that instance.
 * 
 * A return statement in the catch block of a function acts as if it were a return statement in the function.
 * 对于有返回值的函数而言，需要在catch中，继续return。否则，会造成UB.
 * The function returns when the control flow reaches the end of the catch block. If there is no return statement there and the function return type is non-void, the behavior is undefined.
 * Be aware that the function try block of main() has some non-intuitive behavior: Exceptions from constructors of objects defined on the namespace scope are not caught, and exceptions from destructors of objects with static duration are not caught.
 */

int main()
{
	return 0;
}