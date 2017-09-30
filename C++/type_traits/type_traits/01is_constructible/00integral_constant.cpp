/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/29 11:08:56
 */


/*
 * template<class T, T v>
 * struct integral_constant {
 * 	static constexpr T value = v;
 * 	typedef T value_type;
 * 	typedef integral_constant type; // using injected-class-name
 * 	constexpr operator value_type() const noexcept { return value; }
 * 	constexpr value_type operator()() const noexcept { return value; } //since c++14
};
 */
#include <iostream>
#include <type_traits>

int main()
{
	typedef std::integral_constant<int, 2> two_t;
	typedef std::integral_constant<int, 4> four_t;

	//  static_assert(std::is_same<two_t, four_t>::value,
	//                "two_t and four_t are not equal!"); 
	//  error: static assertion failed: "two_t and four_t are not equal!"

	static_assert(two_t::value * 2 == four_t::value,
				  "2*2 != 4"
				  );

	enum class my_e
	{
		e1,
		e2
	};
	typedef std::integral_constant<my_e, my_e::e1> my_e_e1;
	typedef std::integral_constant<my_e, my_e::e2> my_e_e2;

	//  static_assert(my_e_e1::value == my_e::e2,
	//               "my_e_e1::value != my_e::e2");
	//  error: static assertion failed: "my_e_e1::value != my_e::e2"

	static_assert(std::is_same<my_e_e2, my_e_e2>::value,
				  "my_e_e2 != my_e_e2");
	return 0;
}