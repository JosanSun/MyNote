#include <iostream>

struct V
{
	virtual void f()
	{
	};  // must be polymorphic to use runtime-checked dynamic_cast
	int a = 250;
};
struct A : virtual V
{
	int b = 10;
};
struct B : virtual V
{
	B(V* v, A* a)
	{
		// casts during construction (see the call in the constructor of D below)
		dynamic_cast<B*>(v); // well-defined: v of type V*, V base of B, results in B*
		dynamic_cast<B*>(a); // undefined behavior: a has type A*, A not a base of B
	}
	int c = 20;
};
struct D : A, B
{
	D() : B((A*)this, this)
	{
	}
};

struct Base
{
	virtual ~Base()
	{
	}
};

struct Derived : Base
{
	virtual void name()
	{
		std::cout << __FUNCDNAME__ << std::endl;
	}
};


static void test1()
{
	D d; // the most derived object
	A& a = d; // upcast, dynamic_cast may be used, but unnecessary
			  //必须使用dynamic_cast,虽然不报错，但是不能正常转换
	D& new_d = dynamic_cast<D&>(a); // downcast
	B& new_b = dynamic_cast<B&>(a); // sidecast
	D& new_d1 = (D&)(a);  //ok  right
	B& new_b1 = (B&)(a);  //ok  但是转换出错  c = 10
}

static void test2()
{
	A a; 
	//D& new_d = dynamic_cast<D&>(a); // downcast  error bad_cast
	//B& new_b = dynamic_cast<B&>(a); // sidecast  error bad_cast
	D& new_d1 = (D&)(a);  //ok, 除了基类正常转换，其他部分都是错误值
	B& new_b1 = (B&)(a);  //ok, 除了基类正常转换，其他部分都是错误值
}

static void test()
{
	//比较test1和test2
	test1();
	test2();
}

//dynamic_cast < new_type > ( expression )		
//Safely converts pointers and references to classes up, down, and sideways along the inheritance hierarchy.
int main()
{
	test();

	Base* b1 = new Base;
	if(Derived* d = dynamic_cast<Derived*>(b1))
	{
		std::cout << "downcast from b1 to d successful\n";
		d->name(); // safe to call
	}

	Base* b2 = new Derived;
	if(Derived* d = dynamic_cast<Derived*>(b2))
	{
		std::cout << "downcast from b2 to d successful\n";
		d->name(); // safe to call
	}

	delete b1;
	delete b2;

	return 0;
}