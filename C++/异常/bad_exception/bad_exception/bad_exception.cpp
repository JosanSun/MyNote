/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/22 21:28:09
 */
 // bad_exception example
#include <iostream>       // std::cerr
#include <exception>      // std::bad_exception, std::set_unexpected

void myunexpected()
{
	std::cerr << "unexpected handler called\n";
	throw;
}

void myfunction() throw(int, std::bad_exception)
{
	throw 'x'; // throws char (not in exception-specification)
}

int main(void)
{
	std::set_unexpected(myunexpected);
	try
	{
		myfunction();
	}
	catch(int)
	{
		std::cerr << "caught int\n";
	}
	catch(std::bad_exception be)
	{
		std::cerr << "caught bad_exception\n";
	}
	catch(...)
	{
		std::cerr << "caught some other exception\n";  //输出这个  没有捕获到bad_exception
	}
	return 0;
}