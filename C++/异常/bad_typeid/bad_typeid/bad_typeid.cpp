/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/22 21:26:10
 */
 // bad_typeid example
#include <iostream>       // std::cout
#include <typeinfo>       // operator typeid, std::bad_typeid

class Polymorphic
{
	virtual void Member()
	{
	}
};

int main()
{
	try
	{
		Polymorphic * pb = 0;
		std::cout << typeid(*pb).name();
	}
	catch(std::bad_typeid& bt)
	{
		std::cerr << "bad_typeid caught: " << bt.what() << '\n';
	}
	return 0;
}