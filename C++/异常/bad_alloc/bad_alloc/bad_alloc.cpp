/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/22 21:17:11
 */
// bad_alloc example
#include <iostream>     // std::cout
#include <new>          // std::bad_alloc

int main()
{
	try
	{
		while(1)
		{
			new int[100000000LL];
		}
	}
	catch(std::bad_alloc& ba)
	{
		std::cerr << "bad_alloc caught: " << ba.what() << '\n';
	}
	return 0;
}