///*
// * ---------------------------------------------------
// *  Copyright (c) 2017 josan All rights reserved.
// * ---------------------------------------------------
// *
// *               创建者： Josan
// *             创建时间： 2017/9/22 18:45:07
// */
//struct Abstract
//{
//	virtual void f() = 0; // pure virtual
//}; // "Abstract" is abstract
//
//struct Concrete : Abstract
//{
//	void f() override
//	{
//	}; // non-pure virtual
//	virtual void g();     // non-pure virtual
//}; // "Concrete" is non-abstract
//
//struct Abstract2 : Concrete
//{
//	void g() override = 0; // pure virtual overrider
//}; // "Abstract2" is abstract
//
//int main()
//{
//	// Abstract a; // Error: abstract class
//	Concrete b; // OK
//	Abstract& a = b; // OK to reference abstract base
//	a.f(); // virtual dispatch to Concrete::f()
//		   // Abstract2 a2; // Error: abstract class (final overrider of g() is pure)
//	return 0;
//}
