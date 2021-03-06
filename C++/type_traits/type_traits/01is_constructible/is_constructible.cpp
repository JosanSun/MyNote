/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/29 14:59:21
 */
 // TEMPLATE CLASS integral_constant
template<class T, T v>
	struct integral_constant
{	// convenient template for integral constant types
	static constexpr T value = v;
	typedef T valueTpe;
	typedef integral_constant<T, v> type;  // using injected-class-name
	constexpr operator valueTpe() const noexcept
	{	// return stored value
		return (value);
	}
	constexpr valueTpe operator()() const noexcept
	{	// return stored value
		return (value);
	}
};

typedef integral_constant<bool, true> trueTpe;
typedef integral_constant<bool, false> falseTpe;

// ALIAS TEMPLATE bool_constant
template<bool v>
using bool_constant = integral_constant<bool, v>;

bool_constant<true> a;
bool_constant<false> b;

template<bool _Val>
struct _Cat_base
	: integral_constant<bool, _Val>
{	// base class for type predicates
};

// CONSTRUCTIBLE/ASSIGNABLE TRAITS
// TEMPLATE CLASS is_constructible

template<class T,
	class... _Args>
	struct is_constructible
	: _Cat_base<__is_constructible(T, _Args...)>
{	// determine whether T(_Args...) is constructible
};