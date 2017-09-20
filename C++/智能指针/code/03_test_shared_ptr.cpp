/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               �����ߣ� Josan
 *             ����ʱ�䣺 2017/9/20 10:26:42
 */
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <memory>   //shared_ptr
#include <iostream>
#include <set>
using namespace std;

//---------------����shared_ptr�ĸ��ֳ�Ա����  ������������cplusplus.com-------

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
	 * template <class U> shared_ptr (const shared_ptr<U>& x) noexcept;   //ע�⣬���ǣ������ã�����unique_ptr
	 */
	std::shared_ptr<int> p6(p5);     //��ʱ��p6.use_count()  == 2
	//move constructors  p6ʧȥָ�������Ȩ
	std::shared_ptr<int> p7(std::move(p6));
	//move from other types of managed pointers    Ҳ������auto_ptr  ע��������Ĵ�������ֵ����
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

	//ͬʱ��sp��deleter����ΪĬ�ϵ�ɾ����
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

	bar = nullptr;  //�ͷ�bar��ӵ��Ȩ
	std::cout << "3: " << foo.unique() << '\n';  // true
}

/* template <class U> bool owner_before (const shared_ptr<U>& x) const;
 * template <class U> bool owner_before(const weak_ptr<U>& x) const;
 * Returns whether the object is considered to go before x following a strict weak owner-based order.
 */
//NOTE:���������������⣡����
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

//���Գ�Ա����
static void testMemberFunction()
{
	////���Գ�Ա����get()   ע���ʱԴ��ַδʧЧ
	//testGet();
	//���Գ�Ա����get_deleter()
	//testGet_deleter();
	////����reset(),        --ע��û��release()����Ϊ���ܲ�ֻ��һ��ռ��ָ�룬��˵���shared_ptrû��Ȩ���ͷ�
	//testReset();
	////����swap
	//testSwap();
	////����use_count()
	//testUse_count();
	////����unique()
	//testUnique();
	//����owner_before()
	testOwner_before();
	//�����������غ���operator*, ->, bool 
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

//����make_shared<>()
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

//����static_pointer_cast<>()
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

//���Էǳ�Ա����
static void testNonMemberFunction()
{
	/*testNonSwap();
	testNonRelationalOperators();*/
	////����make_shared()
	//testNonMake_shared();
	////����static_pointer_cast()
	//testNonStatic_pointer_cast();
	////����dynamic_pointer_cast()
	//testNonDynamic_pointer_cast();
	////����const_pointer_cast()
	//testNonConst_pointer_cast();
	////����get_deleter()
	//testNonGet_deleter();
	////������ģ��owner_less
	//testNonOwner_less();
	//������ģ��enable_shared_from_this
	testEnable_shared_from_this();
}

//��cplusplusժȡ�Ĳ���������
static void testFromCPlusPlus()
{
	////���Թ��캯��
	//testCtor();
	////���Դ��Զ���ɾ����
	//testCtorWithMyDeleter();
	////���Ը�ֵ����
	//testAssignment();
	////���Գ�Ա����
	//testMemberFunction();
	//���Էǳ�Ա����
	testNonMemberFunction();
}

//�ܲ���
static void test()
{
	//����shared_ptr�ĸ��ֳ�Ա����  ������������cplusplus.com
	testFromCPlusPlus();
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	test();
	return 0;
}