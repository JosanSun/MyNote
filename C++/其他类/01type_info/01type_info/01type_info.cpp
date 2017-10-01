/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/30 10:28:28
 */
#include <iostream>
#include <typeinfo>
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
using namespace std;

#define TYPEINFO_TEST_CASE(name) static void name()

TYPEINFO_TEST_CASE(test_operator)
{
	struct Base
	{
	};
	struct Derived : Base
	{
	};
	struct Poly_Base
	{
		virtual void Member()
		{
		}
	};
	struct Poly_Derived : Poly_Base
	{
	};

	typedef int my_int_type;

	std::cout << std::boolalpha;

	//type_info t1{typeid(int)};  //error. copy dtor =delete
	//type_info& t1 = typeid(int);  //error. 不能绑定
	const type_info& t1 = typeid(int);  //ok
	const type_info& t2 = typeid(my_int_type); 
	// fundamental types:
	std::cout << "int vs my_int_type: ";
	std::cout << (t1 == t2) << '\n';  //true
	
	std::cout << (t1 != t2) << '\n';  //false
	
}

//const char* name() const;
TYPEINFO_TEST_CASE(test_name)
{
	int i;
	int * pi;
	std::cout << "int is: " << typeid(int).name() << '\n';
	std::cout << "  i is: " << typeid(i).name() << '\n';
	std::cout << " pi is: " << typeid(pi).name() << '\n';
	std::cout << "*pi is: " << typeid(*pi).name() << '\n';
}

/* bool before (const type_info& rhs) const;
 * Compare order of types
 * Returns whether the type precedes the type identified by rhs in some implementation-specific order.
 * This implementation-specific order is not necessarily related to size, inheritance relations or declaration order, and may differ between programs.
 */
TYPEINFO_TEST_CASE(test_before)
{
	//No-throw guarantee: 
	if(typeid(int).before(typeid(char)))
		std::cout << "int goes before char in this implementation.\n";
	else
		std::cout << "char goes before int in this implementation.\n";
}

//size_t hash_code() const noexcept;
TYPEINFO_TEST_CASE(test_hash_code)
{
	int i1;
	int * pi;
	std::cout << "int is: " << typeid(int).hash_code() << '\n';
	std::cout << "  i is: " << typeid(i1).hash_code() << '\n';
	std::cout << " pi is: " << typeid(pi).hash_code() << '\n';
	std::cout << "*pi is: " << typeid(*pi).hash_code() << '\n';


	//other------
	struct A
	{
		virtual ~A()
		{
		}
	};

	struct B : A
	{
	};
	struct C : A
	{
	};

	using TypeInfoRef = std::reference_wrapper<const std::type_info>;

	struct Hasher
	{
		std::size_t operator()(TypeInfoRef code) const
		{
			return code.get().hash_code();
		}
	};

	struct EqualTo
	{
		bool operator()(TypeInfoRef lhs, TypeInfoRef rhs) const
		{
			return lhs.get() == rhs.get();
		}
	};
	std::unordered_map<TypeInfoRef, std::string, Hasher, EqualTo> type_names;

	type_names[typeid(int)] = "int";
	type_names[typeid(double)] = "double";
	type_names[typeid(A)] = "A";
	type_names[typeid(B)] = "B";
	type_names[typeid(C)] = "C";

	int i;
	double d;
	A a;

	// note that we're storing pointer to type A
	std::unique_ptr<A> b(new B);
	std::unique_ptr<A> c(new C);

	std::cout << "i is " << type_names[typeid(i)] << '\n';  //int
	std::cout << "d is " << type_names[typeid(d)] << '\n';  //double
	std::cout << "a is " << type_names[typeid(a)] << '\n';  //A
	std::cout << "b is " << type_names[typeid(*b)] << '\n';  //B
	std::cout << "c is " << type_names[typeid(*c)] << '\n';  //C
}



TYPEINFO_TEST_CASE(test)
{
	//test_operator();
	//test_name();
	//test_before();
	test_hash_code();
}

int main()
{
	test();
	return 0;
}