/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               �����ߣ� Josan
 *             ����ʱ�䣺 2017/9/22 21:49:34
 */
 // length_error example
#include <iostream>       // std::cerr
#include <stdexcept>      // std::length_error
#include <vector>         // std::vector

int main(void)
{
	try
	{
		// vector throws a length_error if resized above max_size
		std::vector<int> myvector;
		myvector.resize(myvector.max_size() + 1);
	}
	catch(const std::length_error& le)
	{
		//what()��vector����  _Xlength_error("vector<T> too long");
		std::cerr << "Length error: " << le.what() << '\n';
	}
	return 0;
}