#include <iostream>
using namespace std;
#define TEST_CASE(name)  static void name()

namespace josan
{
	// TEMPLATE CLASS integral_constant
	template<class T, T v>
	struct integral_constant
	{	// convenient template for integral constant types
		static constexpr T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;  // using injected-class-name
		constexpr operator value_type() const noexcept
		{	// return stored value
			return (value);
		}
		constexpr value_type operator()() const noexcept
		{	// return stored value
			return (value);
		}
	};

	typedef integral_constant<bool, true> trueType;
	typedef integral_constant<bool, false> falseType;

	// ALIAS TEMPLATE bool_constant
	template<bool v>
	using bool_constant = integral_constant<bool, v>;

	bool_constant<true> a;
	bool_constant<false> b;

	template<class _Ty>
	struct is_void
		: falseType
	{	// determine whether _Ty is void
	};

#define _EMPTY_ARGUMENT
#define _CLASS_DEFINE_CV(CLASS) \
	CLASS(_EMPTY_ARGUMENT) \
	CLASS(const) \
	CLASS(volatile) \
	CLASS(const volatile)

#define _IS_VOID(CV_OPT) \
template<> \
	struct is_void<CV_OPT void> \
		: true_type \
	{	/* determine whether _Ty is void */ \
	};

	//这个直接定义了四个true_type
	_CLASS_DEFINE_CV(_IS_VOID)

#undef _IS_VOID

}



template<typename T>
TEST_CASE(test_is_void)
{
	if(josan::is_void<T>::value)
	{
		cout << typeid(T).name() << " is void" << endl;
	}
	else
	{
		cout << typeid(T).name() << " is not void" << endl;
	}
}

class A
{

};

TEST_CASE(test)
{
	test_is_void<int>();
	test_is_void<void>();
	test_is_void<const void>();
	test_is_void<A>();
}

int main()
{

	test();

	return 0;
}

