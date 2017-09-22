/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/22 21:20:49
 */
 // bad_cast example
#include <iostream>       // std::cout
#include <typeinfo>       // std::bad_cast

class Base
{
	virtual void member()
	{
	}
};
class Derived : Base
{
};

int main()
{
	try
	{
		Base b;
		Derived& rd = dynamic_cast<Derived&>(b);
	}
	catch(std::bad_cast& bc)
	{
		std::cerr << "bad_cast caught: " << bc.what() << '\n';
	}
	return 0;
}