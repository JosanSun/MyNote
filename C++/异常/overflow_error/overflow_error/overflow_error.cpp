/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/22 21:52:39
 */
#include <iostream>
#include <stdexcept>      //overflow_error

 // Integer division, catching divide by zero.

inline int intDivEx(int numerator, int denominator)
{
	if(denominator == 0)
		throw std::overflow_error("Divide by zero exception");
	return numerator / denominator;
}

int main(void)
{
	int i = 42;

	try
	{
		i = intDivEx(10, 2);
	}
	catch(std::overflow_error e)
	{
		std::cout << e.what() << " -> ";
	}
	std::cout << i << std::endl;

	try
	{
		i = intDivEx(10, 0);
	}
	catch(std::overflow_error e)
	{
		std::cout << e.what() << " -> ";
	}
	std::cout << i << std::endl;

	return 0;
}