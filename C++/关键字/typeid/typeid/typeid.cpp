/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/30 9:19:47
 */

/* typeid operator   RTTI
 * Queries information of a type.
 * Used where the dynamic type of a polymorphic object must be known and for static type identification.
 */
#include <iostream>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <cassert>
#include <typeindex>
#define TYPEID_TEST_CASE(name) static void name()

struct Base
{
}; // non-polymorphic
struct Derived : Base
{
};

struct Base2
{
	virtual void foo()
	{
	}
}; // polymorphic
struct Derived2 : Base2
{
};

/* typeid( type )	(1)
 * 1) Refers to a std::type_info object representing the type type. If type is a reference type, the result refers to a std::type_info object representing the referenced type.
 */
TYPEID_TEST_CASE(test_typeid_type)
{
	int myint = 50;
	const int myint1 = 50;
	/* In all cases, cv-qualifiers are ignored by typeid (that is, typeid(T) == typeid(const T))
	*/
	std::cout << "myint has type: " << typeid(myint).name() << "\n";  //int
	std::cout << "myint1 has type: " << typeid(myint1).name() << "\n";  //int

	/* 左值引用与右值引用
	* Refers to a std::type_info object representing the type type. If type is a reference type, the result refers to a std::type_info object representing the referenced type.
	*/
	int& iTest = myint;
	std::cout << "iTest has type: " << typeid(iTest).name() << "\n";  //int
	std::cout << "myint has type: " << typeid((myint)).name() << "\n";  //int
	std::cout << "myint has type: " << typeid(std::move(myint)).name() << "\n";  //int  注意这是typeid( expression )

	/* Lvalue-to-rvalue, array-to-pointer, or function-to-pointer conversions are not performed.
	 */
	int a[5], *pa = a;
	std::cout << "a[5] has type: " << typeid(a).name() << "\n";  //int [5]  数组没有转化为指针
	std::cout << "pa has type: " << typeid(pa).name() << "\n";  //int *


	std::string mystr = "string";
	double *mydoubleptr = nullptr;
	std::cout << "mystr has type: " << typeid(mystr).name() << '\n'
		<< "mydoubleptr has type: " << typeid(mydoubleptr).name() << '\n';
	double *mydoubleptr1 = nullptr;
	//注意这是typeid( expression )  并且不报错，因为使用的是static type identification
	std::cout << "mydoubleptr1 has type: " << typeid(*mydoubleptr1).name() << '\n';  //double

	// -------If type is a reference type, the result refers to a std::type_info object 
	// representing the referenced type.---------
	
	// Non-polymorphic lvalue is a static type
	Derived d1;
	Base& b1 = d1;
	std::cout << "reference to non-polymorphic base: " << typeid(b1).name() << '\n';

	// Polymorphic lvalue is a dynamic type
	Derived2 d2;
	Base2& b2 = d2;
	std::cout << "reference to polymorphic base: " << typeid(b2).name() << '\n';
}

TYPEID_TEST_CASE(test_typeid_expression)
{
	int myint = 50;
	// std::cout << myint is a glvalue expression of polymorphic type; it is evaluated
	const std::type_info& r1 = typeid(std::cout << myint);
	std::cout << '\n' << "std::cout<<myint has type : " << r1.name() << '\n';

	// std::printf() is not a glvalue expression of polymorphic type; NOT evaluated
	const std::type_info& r2 = typeid(std::printf("%d\n", myint));
	std::cout << "printf(\"%d\\n\",myint) has type : " << r2.name() << '\n';

	double *mydoubleptr = nullptr;
	try
	{
		// dereferencing a null pointer: okay for a non-polymorphic expression
		std::cout << "mydoubleptr points to " << typeid(*mydoubleptr).name() << '\n';
		// dereferencing a null pointer: not okay for a polymorphic lvalue
		Derived2* bad_ptr = nullptr;
		std::cout << "bad_ptr points to... ";
		std::cout << typeid(*bad_ptr).name() << '\n';
	}
	catch(const std::bad_typeid& e)
	{
		std::cout << " caught " << e.what() << '\n';
	}

	Derived2 d2;
	Base2& b2 = d2;
	const std::type_info& ti1 = typeid(d2);
	const std::type_info& ti2 = typeid(b2);

	assert(&ti1 == &ti2); // not guaranteed
	assert(ti1.hash_code() == ti2.hash_code()); // guaranteed
	assert(std::type_index(ti1) == std::type_index(ti2)); // guaranteed


	Derived d1;
	Base& b1 = d1;
	const std::type_info& tii1 = typeid(d1);
	const std::type_info& tii2 = typeid(b1);
	//assert(&tii1 == &tii2);  //error
	//assert(tii1.hash_code() == tii2.hash_code()); //error
	//assert(std::type_index(tii1) == std::type_index(tii2)); //  error
}


TYPEID_TEST_CASE(test)
{
	test_typeid_type();
	test_typeid_expression();
}

int main()
{
	test();
	return 0;
}