//////template <int I> struct X
//////{
//////};
//////template <template <class T> class> struct Z
//////{
//////};
//////template <class T> void f(typename T::Y*)
//////{
//////}
//////template <class T> void g(X<T::N>*)
//////{
//////}
//////template <class T> void h(Z<T::template TT>*)
//////{
//////}
//////struct A
//////{
//////};
//////struct B
//////{
//////	int Y;
//////};
//////struct C
//////{
//////	typedef int N;
//////};
//////struct D
//////{
//////	typedef int TT;
//////};
//////struct B1
//////{
//////	typedef int Y;
//////};
//////struct C1
//////{
//////	static const int N = 0;
//////};
//////struct D1
//////{
//////	template <typename T>
//////	struct TT
//////	{
//////	};
//////};
//////int main()
//////{
//////	// Deduction fails in each of these cases:
//////	//f<A>(0); // A does not contain a member Y
//////	//f<B>(0); // The Y member of B is not a type
//////	//g<C>(0); // The N member of C is not a non-type
//////	//h<D>(0); // The TT member of D is not a template
//////
//////			 // Deduction succeeds in each of these cases:
//////	f<B1>(0);
//////	g<C1>(0);
//////	;
//////}
////
////
//////template <class T, T> struct S
//////{
//////};
//////template <class T> int f(S<T, T()>*);
//////struct X
//////{
//////};
//////int i0 = f<X>(0);
////
//////template <class T, T*> int f(int);
//////int i1 = f<int, 12>(0); // can’t conv 1 to int*
//////int i2 = f<int, 0>(0); // can’t conv 1 to int*
////
////struct X
////{
////};
////struct Y
////{
////	Y(X)
////	{
////	}
////}; // X is convertible to Y
////
////template <class T>
////auto f(T t1, T t2) -> decltype(t1 + t2); // overload #1
////
////X f(Y, Y);  // overload #2
////
////X x1, x2;
////X x3 = f(x1, x2);  // deduction fails on #1 (expression x1+x2 is ill-formed)
////				   // only #2 is in the overload set, and is called
//
//
//#include <iostream>
//
//template <typename T>
//struct has_typedef_foobar
//{
//	// Types "yes" and "no" are guaranteed to have different sizes,
//	// specifically sizeof(yes) == 1 and sizeof(no) == 2.
//	typedef char yes[1];
//	typedef char no[2];
//
//	//这两个test的声明顺序对测试没有影响。
//	template <typename>
//	static no& test(...);
//	template <typename C>
//	static yes& test(typename C::foobar*);
//
//	// If the "sizeof" of the result of calling test<T>(nullptr) is equal to sizeof(yes),
//	// the first overload worked and T has a nested type named foobar.
//	static const bool value = sizeof(test<T>(nullptr)) == sizeof(yes);
//};
//
//struct foo
//{
//	typedef float foobar;
//};
//
//int main()
//{
//	std::cout << std::boolalpha;
//	std::cout << has_typedef_foobar<int>::value << std::endl;
//	std::cout << has_typedef_foobar<foo>::value << std::endl;
//	return 0;
//}

//
//#include <iostream>
//#include <type_traits>
//
//template <typename... Ts> using void_t = void;
//
//template <typename T, typename = void>
//struct has_typedef_foobar : std::false_type
//{
//};
//
//template <typename T>
//struct has_typedef_foobar<T, void_t<typename T::foobar>> : std::true_type
//{
//};
//
//struct foo
//{
//	using foobar = float;
//};
//
//int main()
//{
//	std::cout << std::boolalpha;
//	std::cout << has_typedef_foobar<int>::value << std::endl;
//	std::cout << has_typedef_foobar<foo>::value << std::endl;
//	return 0;
//}

#include <iostream>
#include <experimental/type_traits>

template <typename T>
using has_typedef_foobar_t = decltype(T::foobar);

struct foo
{
	using foobar = float;
};

int main()
{
	std::cout << std::boolalpha;
	std::cout << std::is_detected<has_typedef_foobar_t, int>::value << std::endl;
	std::cout << std::is_detected<has_typedef_foobar_t, foo>::value << std::endl;
}
