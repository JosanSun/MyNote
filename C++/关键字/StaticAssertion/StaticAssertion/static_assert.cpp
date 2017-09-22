/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/22 16:50:35
 */
#include <type_traits>
/*
 * Syntax
 * static_assert ( bool_constexpr , message )		(since C++11)
 * static_assert ( bool_constexpr )		(since C++17)
 *
 * bool_constexpr	-	a contextually converted constant expression of type bool
 * message	        -	optional (since C++17)string literal that will appear as compiler error if bool_constexpr is false
 * optional(since C++17)string literal that will appear as compiler error if bool_constexpr is false
 */

template <class T>
void swap(T& a, T& b)
{
	static_assert(std::is_copy_constructible<T>::value,
				  "Swap requires copying");
	static_assert(std::is_nothrow_copy_constructible<T>::value
				  && std::is_nothrow_copy_assignable<T>::value,
				  "Swap may throw");
	auto c = b;
	b = a;
	a = c;
}

//template <class T>
//struct data_structure
//{
//	static_assert(std::is_default_constructible<T>::value,
//				  "Data Structure requires default-constructible elements");
//};

struct no_copy
{
	no_copy(const no_copy&) = delete;
	no_copy() = default;
};

struct no_default
{
	no_default() = delete;
};

int main()
{
	int a, b;
	swap(a, b);

	no_copy nc_a, nc_b;
	swap(nc_a, nc_b); // 1

	//data_structure<int> ds_ok;
	//data_structure<no_default> ds_error; // 2
	return 0;
}

//output:
//1: error: static assertion failed: Swap requires copying
//2: error: static assertion failed : Data Structure requires default - constructible elements