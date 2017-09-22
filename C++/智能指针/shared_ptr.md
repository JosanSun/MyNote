# 用例子来学习shared_ptr
写这个是为了熟悉shared_ptr的接口，注意它与其他智能指针的区别。本测试主要来自cplusplus。

## 代码
```C++
/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/20 10:26:42
 */
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <memory>   //shared_ptr
#include <iostream>
#include <set>
using namespace std;

//--------------测试指向POD类型的shared_ptr()
class A1
{
public:
	A1()
	{
		cout << "constructor" << endl;
	}
	~A1()
	{
		cout << "destructor" << endl;
	}
};

class Child;

class Parent
{
public:
	shared_ptr<Child> child;
};

class Child
{
public:
	shared_ptr<Parent> parent;
};



static void test_POD()
{
	////shared_ptr指向数组
	////对于使用new[]进行分配的内存，必须自动以deleter来释放内存
	//shared_ptr<A1> arrayObj1(new A1[5], [](A1 *p) {delete[] p; });
	////unique_ptr如何解决指向数组问题
	//unique_ptr<A1[]> arrayObj2(new A1[4]);

	//测试环形引用
	shared_ptr<Parent> pA(new Parent);
	shared_ptr<Child> pB(new Child);
	pA->child = pB;
	pB->parent = pA;
}


//---------------测试shared_ptr的各种成员函数  测试用例来自cplusplus.com-------

struct C
{
	int* data;
};

static void testCtor()
{
	//default constructor 
	std::shared_ptr<int> p1;
	std::shared_ptr<int> p2(nullptr);
	//ctor from null pointer 
	std::shared_ptr<int> p3(new int);
	//ctor pointer + deleter 
	std::shared_ptr<int> p4(new int, std::default_delete<int>());
	//ctor from pointer + deleter + allocator 
	std::shared_ptr<int> p5(new int, [](int* p) {delete p; }, std::allocator<int>());
	//copy constructors  
	/*
	 * shared_ptr (const shared_ptr& x) noexcept;
	 * template <class U> shared_ptr (const shared_ptr<U>& x) noexcept;   //注意，这是（左）引用，区分unique_ptr
	 */
	std::shared_ptr<int> p6(p5);     //此时，p6.use_count()  == 2
	//move constructors  p6失去指针的所有权
	std::shared_ptr<int> p7(std::move(p6));
	//move from other types of managed pointers    也可以是auto_ptr  注意这里面的传参是右值引用
	std::shared_ptr<int> p8(std::unique_ptr<int>(new int));
	//aliasing ctor
	/*
	 * template <class U> shared_ptr (const shared_ptr<U>& x, element_type* p) noexcept;
	 */
	std::shared_ptr<C> obj(new C);
	std::shared_ptr<int> p9(obj, obj->data);

	//-----output------
	std::cout << "use_count:\n";
	std::cout << "p1: " << p1.use_count() << '\n';  //0
	std::cout << "p2: " << p2.use_count() << '\n';  //0
	std::cout << "p3: " << p3.use_count() << '\n';  //1
	std::cout << "p4: " << p4.use_count() << '\n';  //1
	std::cout << "p5: " << p5.use_count() << '\n';  //2
	std::cout << "p6: " << p6.use_count() << '\n';  //0
	std::cout << "p7: " << p7.use_count() << '\n';  //2
	std::cout << "p8: " << p8.use_count() << '\n';  //1
	std::cout << "p9: " << p9.use_count() << '\n';  //2
}

static void testCtorWithMyDeleter()
{
	auto deleter = [](int*p) {
		std::cout << "[deleter called]\n"; delete p;
	};
	std::shared_ptr<int> foo(new int, deleter);
	std::cout << "use_count: " << foo.use_count() << '\n';
}

static void testAssignment()
{
	std::shared_ptr<int> foo;
	std::shared_ptr<int> bar(new int(10));

	foo = bar;                          // copy
	bar = std::make_shared<int>(20);   // move

	std::unique_ptr<int> unique(new int(30));
	foo = std::move(unique);            // move from unique_ptr

	std::cout << "*foo: " << *foo << '\n';
	std::cout << "*bar: " << *bar << '\n';
}

//element_type* get() const noexcept;
static void testGet()
{
	int* p = new int(10);
	std::shared_ptr<int> a(p);

	if(a.get() == p)
		std::cout << "a and p point to the same location\n";

	// three ways of accessing the same address: 
	std::cout << *a.get() << "\n";  //10
	std::cout << *a << "\n";  //10
	std::cout << *p << "\n";  //10
}

/*
 * (1) void reset() noexcept;
 * (2) template <class U> void reset (U* p);
 * (3) template <class U, class D> void reset (U* p, D del);
 * (4) template <class U, class D, class Alloc> void reset (U* p, D del, Alloc alloc);
 */
static void testReset()
{
	auto deleter = [](int*p) {
		std::cout << "[deleter called]\n"; delete p;
	};
	std::shared_ptr<int> sp(nullptr, deleter);  // empty

	//同时将sp的deleter设置为默认的删除器
	sp.reset(new int);       // takes ownership of pointer
	*sp = 10;
	std::cout << *sp << '\n';  //10

	sp.reset(new int);       // deletes managed object, acquires new pointer
	*sp = 20;
	std::cout << *sp << '\n';  //20

	sp.reset();               // deletes managed object
}

//void swap (shared_ptr& x) noexcept;
static void testSwap()
{
	std::shared_ptr<int> foo(new int(10));
	std::shared_ptr<int> bar(new int(20));

	foo.swap(bar);

	std::cout << "*foo: " << *foo << '\n';  //20
	std::cout << "*bar: " << *bar << '\n';  //10
}

//long int use_count() const noexcept;
/*
 * Returns the number of shared_ptr objects that share ownership over the same pointer as this object (including it).
 * If this is an empty shared_ptr, the function returns zero.
 */
static void testUse_count()
{
	std::shared_ptr<int> p1;
	std::shared_ptr<int> p2(new int);
	std::cout << "p1: " << p1.use_count() << '\n';  //0
	std::cout << "p2: " << p2.use_count() << '\n';  //1
}

//bool unique() const noexcept;
static void testUnique()
{
	std::shared_ptr<int> foo;
	std::shared_ptr<int> bar(new int);

	std::cout << "foo unique?\n" << std::boolalpha;

	std::cout << "1: " << foo.unique() << '\n';  // false (empty)

	foo = bar;
	std::cout << "2: " << foo.unique() << '\n';  // false (shared with bar)

	bar = nullptr;  //释放bar的拥有权
	std::cout << "3: " << foo.unique() << '\n';  // true
}

/* template <class U> bool owner_before (const shared_ptr<U>& x) const;
 * template <class U> bool owner_before(const weak_ptr<U>& x) const;
 * Returns whether the object is considered to go before x following a strict weak owner-based order.
 */
//NOTE:对于这个函数不理解！！！
static void testOwner_before()
{
	int * p = new int(10);

	std::shared_ptr<int> a(new int(20));
	std::shared_ptr<int> b(a, p);  // alias constructor

	std::cout << "comparing a and b...\n" << std::boolalpha;
	//std::cout << "value-based: " << (!(a < b) && !(b < a)) << '\n';
	cout << a.owner_before(b) << endl;
	cout << b.owner_before(a) << endl;
	std::cout << "owner-based: " << (!a.owner_before(b) && !b.owner_before(a)) << '\n';

	std::shared_ptr<int> c(new int(20));
	std::shared_ptr<int> d(c);  // copy constructor
	cout << c.owner_before(d) << endl;
	cout << d.owner_before(c) << endl;
	delete p;
}

//测试成员函数
static void testMemberFunction()
{
	////测试成员函数get()   注意此时源地址未失效
	//testGet();
	//测试成员函数get_deleter()
	//testGet_deleter();
	////测试reset(),        --注意没有release()，因为可能不只是一个占用指针，因此单个shared_ptr没有权利释放
	//testReset();
	////测试swap
	//testSwap();
	////测试use_count()
	//testUse_count();
	////测试unique()
	//testUnique();
	//测试owner_before()
	testOwner_before();
	//其他符号重载函数operator*, ->, bool 
}


static void testNonSwap()
{
	std::shared_ptr<int> foo(new int(10));
	std::shared_ptr<int> bar(new int(20));

	swap(foo, bar);

	std::cout << "foo: " << *foo << '\n';
	std::cout << "bar: " << *bar << '\n';
}

static void testNonRelationalOperators()
{
	std::shared_ptr<int> a, b, c, d;

	a = std::make_shared<int>(10);
	b = std::make_shared<int>(10);
	c = b;

	std::cout << "comparisons:\n" << std::boolalpha;

	std::cout << "a == b: " << (a == b) << '\n';  //false
	std::cout << "b == c: " << (b == c) << '\n';  //true
	std::cout << "c == d: " << (c == d) << '\n';  //false

	std::cout << "a != nullptr: " << (a != nullptr) << '\n';  //true
	std::cout << "b != nullptr: " << (b != nullptr) << '\n';  //true
	std::cout << "c != nullptr: " << (c != nullptr) << '\n';  //true
	std::cout << "d != nullptr: " << (d != nullptr) << '\n';  //false
}

//测试make_shared<>()
static void testNonMake_shared()
{
	std::shared_ptr<int> foo = std::make_shared<int>(10);
	// same as:
	std::shared_ptr<int> foo2(new int(10));

	auto bar = std::make_shared<int>(20);

	auto baz = std::make_shared<std::pair<int, int>>(30, 40);

	std::cout << "*foo: " << *foo << '\n';
	std::cout << "*bar: " << *bar << '\n';
	std::cout << "*baz: " << baz->first << ' ' << baz->second << '\n';
}

//测试static_pointer_cast<>()
struct A
{
	static const char* static_type;
	const char* dynamic_type;
	A()
	{
		dynamic_type = static_type;
	}
};
struct B : A
{
	static const char* static_type;
	B()
	{
		dynamic_type = static_type;
	}
};

const char* A::static_type = "class A";
const char* B::static_type = "class B";

/*
 * template <class T, class U>
 * shared_ptr<T> static_pointer_cast (const shared_ptr<U>& sp) noexcept;
 */
static void testNonStatic_pointer_cast()
{
	std::shared_ptr<A> foo;
	std::shared_ptr<B> bar;

	foo = std::make_shared<A>();

	// statically from A* to B*.
	// cast of potentially incomplete object, but ok as a static cast:
	bar = std::static_pointer_cast<B>(foo);

	std::cout << "foo's static  type: " << foo->static_type << '\n';  //class A
	std::cout << "foo's dynamic type: " << foo->dynamic_type << '\n';  //class A
	std::cout << "bar's static  type: " << bar->static_type << '\n';  //class B
	std::cout << "bar's dynamic type: " << bar->dynamic_type << '\n';  //class A
}

/*
 * template <class T, class U>
 * shared_ptr<T> dynamic_pointer_cast (const shared_ptr<U>& sp) noexcept;
 */
static void testNonDynamic_pointer_cast()
{
	std::shared_ptr<A> foo;
	std::shared_ptr<B> bar;

	bar = std::make_shared<B>();
	//dynamically from B* to A*.
	foo = std::dynamic_pointer_cast<A>(bar);

	std::cout << "foo's static  type: " << foo->static_type << '\n';  //class A
	std::cout << "foo's dynamic type: " << foo->dynamic_type << '\n';  //class B
	std::cout << "bar's static  type: " << bar->static_type << '\n';  //class B
	std::cout << "bar's dynamic type: " << bar->dynamic_type << '\n';  //class B
}

/*
 * template <class T, class U>
 * shared_ptr<T> const_pointer_cast (const shared_ptr<U>& sp) noexcept;
 */
static void testNonConst_pointer_cast()
{
	std::shared_ptr<int> foo;
	std::shared_ptr<const int> bar;

	foo = std::make_shared<int>(10);

	//const casted from int* to const int*.
	bar = std::const_pointer_cast<const int>(foo);


	std::shared_ptr<int> foo1;
	foo1 = std::const_pointer_cast<int>(bar);

	std::cout << "*bar: " << *bar << '\n';  //10
	*foo = 20;
	std::cout << "*bar: " << *bar << '\n';  //20
	*foo1 = 30;
	std::cout << "*foo: " << *foo << '\n';  //30
	std::cout << "*bar: " << *bar << '\n';  //30
	std::cout << "*foo1: " << *foo1 << '\n';  //30
	std::cout << "use_count: " << foo.use_count() << ", " << bar.use_count() << ", " << foo1.use_count() << endl;  //3 3 3
}

struct D
{    // a verbose array deleter:
	void operator()(int* p)
	{
		std::cout << "[deleter called]\n";
		delete[] p;
	}
};

/*
 * template <class D, class T>
 * D* get_deleter (const shared_ptr<T>& sp) noexcept;
 */
static void testNonGet_deleter()
{
	std::shared_ptr<int> foo(new int[10], D());

	int * bar = new int[20];

	// use foo's deleter to delete bar (which is unmanaged):
	(*std::get_deleter<D, int>(foo))(bar);  //[deleter called]
}

/*
 * template <class Ptr> struct owner_less;
 * template <class T> struct owner_less<shared_ptr<T>>;
 * template <class T> struct owner_less<weak_ptr<T>>;
 */
static void testNonOwner_less()
{
	int * p = new int(10);

	std::shared_ptr<int> a(new int(20));
	std::shared_ptr<int> b(a, p);  // alias constructor: co-owns a, points to p

								   // standard set container: cannot contain duplicates.
	std::set < std::shared_ptr<int> > value_based;  // uses std::less
	std::set < std::shared_ptr<int>, std::owner_less<std::shared_ptr<int>> > owner_based;

	value_based.insert(a);
	value_based.insert(b);  // ok, different value

	owner_based.insert(a);
	owner_based.insert(b);  // overwrites (same owned pointer)

	std::cout << "value_based.size() is " << value_based.size() << '\n';
	std::cout << "owner_based.size() is " << owner_based.size() << '\n';
	delete p;
}

struct C1 : std::enable_shared_from_this<C1>
{
};

static void testEnable_shared_from_this()
{
	std::shared_ptr<C1> foo, bar;

	foo = std::make_shared<C1>();

	bar = foo->shared_from_this();

	if(!foo.owner_before(bar) && !bar.owner_before(foo))
		std::cout << "foo and bar share ownership";
}

//测试非成员函数
static void testNonMemberFunction()
{
	/*testNonSwap();
	testNonRelationalOperators();*/
	////测试make_shared()
	//testNonMake_shared();
	////测试static_pointer_cast()
	//testNonStatic_pointer_cast();
	////测试dynamic_pointer_cast()
	//testNonDynamic_pointer_cast();
	////测试const_pointer_cast()
	//testNonConst_pointer_cast();
	////测试get_deleter()
	//testNonGet_deleter();
	////测试类模板owner_less
	//testNonOwner_less();
	//测试类模板enable_shared_from_this
	testEnable_shared_from_this();
}

//从cplusplus摘取的测试用例。
static void testFromCPlusPlus()
{
	////测试构造函数
	//testCtor();
	////测试带自定义删除器
	//testCtorWithMyDeleter();
	////测试赋值函数
	//testAssignment();
	////测试成员函数
	//testMemberFunction();
	//测试非成员函数
	testNonMemberFunction();
}

//总测试
static void test()
{
	//测试指向POD类型的shared_ptr()
	test_POD();
	////测试unique_ptr的各种成员函数  测试用例来自cplusplus.com
	//testFromCPlusPlus();
	////测试参数传递
	//testParameterPass();
	//测试多态，包括指针的upcast，和downcast的转换。
	//wait to test
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	test();
	return 0;
}
```
## 总结

- shared_ptr没有成员函数release()，可以直接进行拷贝和赋值。

- 盲点

成员函数：owner_before()

非成员函数：除了make_shared()

## 参考

1. [cplusplus](http://www.cplusplus.com/reference/memory/shared_ptr/?kw=shared_ptr)
