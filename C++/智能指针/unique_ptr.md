# unique_ptr测试
写这个是为了熟悉unique_ptr的接口，注意它与auto_ptr的区别。本测试包含三部分。
1. 测试指向POD类型的unique_ptr
2. 测试unique_ptr的各种成员函数  测试用例来自`cplusplus.com`
3. 测试函数参数，返回值为unique_ptr的注意事项。

## 代码
```C++
/*
* ---------------------------------------------------
*  Copyright (c) 2017 josan All rights reserved.
* ---------------------------------------------------
*
*               创建者： Josan
*             创建时间： 2017/9/20 8:37:47
*/
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <memory>   //unique_ptr
#include <iostream>
using namespace std;


//---------------测试指向POD类型的unique_ptr()  test_POD()-------------------
void deleteInt(int* p)
{
	cout << "Ready to delete an int" << endl;
	delete p;
}

void test_POD()
{
	//1 ctor, copy ctor(=delete  不存在拷贝赋值)unique_ptr (const unique_ptr&) = delete;   但可以有移动拷贝复制
	//空unique_ptr
	unique_ptr<int> u1;
	unique_ptr<int> u2(new int{2});
	////error  这个使用模板参数2的构造函数，也就是空指针，这个存在问题，因此错误  因此只有u5是可以运行的
	//unique_ptr<int, decltype(deleteInt)*> u3;
	//unique_ptr<int, decltype(deleteInt)*> u4(new int);       
	unique_ptr<int, decltype(deleteInt)*> u5(new int(3), deleteInt);
	//unique_ptr<int, decltype(deleteInt)*> u6(deleteInt);   //error
	unique_ptr<int, decltype(deleteInt)*> u7(new int(111), deleteInt);
	//u7.reset(u5.release());

	//2 assign  (unique_ptr& operator= (const unique_ptr&) = delete;)
	//释放u指向的对象，同时将u置为空
	u1 = nullptr;
	////error  无法直接赋值
	//u1 = u2;
	u1 = move(u2);

	
	//3 测试 release 和 reset 成员函数
	//WARNINGS: u2释放指针，并返回指针的值。如果没有捉住这个指针，就会产生内存泄漏
	u2.release();  //泄漏
	
	u2.reset(new int{100});
	//u2释放指针
	u2.reset();
	//u2本身指向为空，仍可以继续reset()
	u2.reset(nullptr);
	int * p = new int{123};
	u2.reset(p);

	//常见reset的用法
	u1.reset(u2.release());
}

//---------------测试unique_ptr的各种成员函数  测试用例来自cplusplus.com-------
static void testCtor()
{
	std::default_delete<int> d;
	std::unique_ptr<int> u1;
	std::unique_ptr<int> u2(nullptr);
	std::unique_ptr<int> u3(new int);
	std::unique_ptr<int> u4(new int, d);
	std::unique_ptr<int> u5(new int, std::default_delete<int>());
	//ERROR: 测试不通过，但是cplusplus的意思是测试通过啊。
	//std::unique_ptr<int> u6(std::move(u5));
	//std::unique_ptr<void> u7(std::move(u6));
	std::unique_ptr<int> u8(std::auto_ptr<int>(new int));

	std::cout << "u1: " << (u1 ? "not null" : "null") << '\n';  //null
	std::cout << "u2: " << (u2 ? "not null" : "null") << '\n';  //null
	std::cout << "u3: " << (u3 ? "not null" : "null") << '\n';  //not null
	std::cout << "u4: " << (u4 ? "not null" : "null") << '\n';  //not null
	std::cout << "u5: " << (u5 ? "not null" : "null") << '\n';  //null
	//std::cout << "u6: " << (u6 ? "not null" : "null") << '\n';  //null
	//std::cout << "u7: " << (u7 ? "not null" : "null") << '\n';  //not null
	std::cout << "u8: " << (u8 ? "not null" : "null") << '\n';  //not null
}

static void testCtorWithMyDeleter()
{
	auto deleter = [](int*p) {
		std::cout << "[deleter called]\n";
		delete p;
	};

	std::unique_ptr<int, decltype(deleter)> foo(new int, deleter);

	std::cout << "foo " << (foo ? "is not" : "is") << " empty\n";
}

static void testAssignment()
{
	std::unique_ptr<int> foo;
	std::unique_ptr<int> bar;

	foo = std::unique_ptr<int>(new int(101));  // rvalue
	bar = std::move(foo);                       // using std::move

	std::cout << "foo: ";
	if(foo) std::cout << *foo << '\n'; else std::cout << "empty\n";

	std::cout << "bar: ";
	if(bar) std::cout << *bar << '\n'; else std::cout << "empty\n";

}

//测试成员函数get()
static void testGet()
{
	//01 -------------test get()-------------------------
	void testGet();
	// foo   bar    p
	// ---   ---   ---
	std::unique_ptr<int> foo;                // null
	std::unique_ptr<int> bar;                // null  null
	int* p = nullptr;                        // null  null  null

	foo = std::unique_ptr<int>(new int(10)); // (10)  null  null
	bar = std::move(foo);                    // null  (10)  null
	//NOTE:此时bar依然保存有指针
	p = bar.get();                           // null  (10)  (10)
	*p = 20;                                 // null  (20)  (20)
	p = nullptr;                             // null  (20)  null

	foo = std::unique_ptr<int>(new int(30)); // (30)  (20)  null
	p = foo.release();                       // null  (20)  (30)
	*p = 40;                                 // null  (20)  (40)

	std::cout << "foo: ";
	if(foo) std::cout << *foo << '\n'; else std::cout << "(null)\n";

	std::cout << "bar: ";
	if(bar) std::cout << *bar << '\n'; else std::cout << "(null)\n";

	std::cout << "p: ";
	if(p) std::cout << *p << '\n'; else std::cout << "(null)\n";
	std::cout << '\n';

	delete p;   // the program is now responsible of deleting the object pointed by p
				// bar deletes its managed object automatically
}

class state_deleter
{  // a deleter class with state
	int count_;
public:
	state_deleter() : count_(0)
	{
	}
	template <class T>
	void operator()(T* p)
	{
		std::cout << "[deleted #" << ++count_ << "]\n";
		delete p;
	}
};

//测试成员函数get_deleter()
static void testGet_deleter()
{
	state_deleter del;

	std::unique_ptr<int> p;   // uses default deleter

							  // alpha and beta use independent copies of the deleter:
	std::unique_ptr<int, state_deleter> alpha(new int);
	std::unique_ptr<int, state_deleter> beta(new int, alpha.get_deleter());

	// gamma and delta share the deleter "del" (deleter type is a reference!):
	std::unique_ptr<int, state_deleter&> gamma(new int, del);
	std::unique_ptr<int, state_deleter&> delta(new int, gamma.get_deleter());  //二者共享同一个删除器

	std::cout << "resetting alpha..."; alpha.reset(new int);
	std::cout << "resetting beta..."; beta.reset(new int);
	std::cout << "resetting gamma..."; gamma.reset(new int);
	std::cout << "resetting delta..."; delta.reset(new int);

	std::cout << "calling gamma/delta deleter...";
	gamma.get_deleter()(new int);

	alpha.get_deleter() = state_deleter();  // a brand new deleter for alpha

											// additional deletions when unique_ptr objects reach out of scope
											// (in inverse order of declaration)
	//结束之前，alpha, beta, gamma, delta中的count 分别为0， 1， 3， 3
	//Result:------------------------
	//resetting alpha...[deleted #1]
	//	resetting beta...[deleted #1]
	//	resetting gamma...[deleter #1]
	//	resetting delta...[deleter #2]
	//	calling gamma / delta deleter...[deleted #3]
	//	[deleted #4]
	//[deleted #5]      
	//[deleted #2]
	//[deleter #1]
}

//测试成员函数swap()
static void testSwap()
{
	std::unique_ptr<int> foo(new int(10));
	std::unique_ptr<int> bar(new int(20));

	foo.swap(bar);

	std::cout << "foo: " << *foo << '\n';
	std::cout << "bar: " << *bar << '\n';
}

static void testMemberFunction()
{
	////测试成员函数get()   注意此时源地址未失效
	//testGet();
	////测试成员函数get_deleter()
	//testGet_deleter();
	////测试转换函数，也就是转换成bool
	////略. Oops...
	////测试reset(), release()
	////略. Oops...
	////测试swap
	//testSwap();
}

//从cplusplus摘取的测试用例。
static void testFromCPlusPlus()
{
	//测试构造函数
	testCtor();
	//测试带自定义删除器
	testCtorWithMyDeleter();
	//测试赋值函数
	testAssignment();
	//测试成员函数
	testMemberFunction();
}

unique_ptr<int> fun(unique_ptr<int> u)
{
	cout << "fun: u -> " << *u << endl;
	return u;
}

//return u会报错，无法引用已经删除的u??
unique_ptr<int> fun1(unique_ptr<int>& u)
{
	cout << "fun: u -> " << *u << endl;
	return move(u);    //return u; 报错
}

//返回一个引用，也就是意味着返回的是一个lvalue;
unique_ptr<int>& fun2(unique_ptr<int> u)
{
	cout << "fun: u -> " << *u << endl;
	return u;
}

unique_ptr<int>& fun3(unique_ptr<int>& u)
{
	cout << "fun: u -> " << *u << endl;
	return u;
}

static void testParameterPass()
{
	unique_ptr<int> u1(new int{100});
	////这个会出现无法转换
	//unique_ptr<int> u2 = fun(u1);
	
	unique_ptr<int> u3 = fun(move(u1));   //返回的临时变量是rvalue; 另外，u1指向为空
	//or:  unique_ptr<int> u3 = move(fun(move(u1)));
	cout << *u3 << endl;



	//other test:   For fun.    关于引用相关的测试
	//unique_ptr<int> u4 = fun1(u3);          //u3为空
	//cout << *u4 << endl;                      //100
	//unique_ptr<int> u5 = move(fun2(move(u3)));
	////unique_ptr<int> u5 = fun2(move(u3));    //这个会报错，引用已经删除的变量
	//cout << *u5 << endl;                    //一个随机数   1904870    这种传值是错误的
	//unique_ptr<int> u6 = move(fun3(u3));
	//cout << *u6 << endl;       //100
	
	{
		unique_ptr<int>& u6 = u3;
		cout << *u6 << endl;   //100    *u3---100
	}
	cout << *u3 << endl;    //仍然可以正确输出100
}

//总测试
static void test()
{
	////测试指向POD类型的unique_ptr()
	//test_POD();
	////测试unique_ptr的各种成员函数  测试用例来自cplusplus.com
	//testFromCPlusPlus();
	//测试参数传递
	testParameterPass();
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

- unique_ptr没有直接的拷贝构造函数以及拷贝赋值语句，也就是说`unique_ptr<T> u(u1);`是错的，正确的写法是`unique_ptr<T> u(move(u1));`。
- 对于函数的返回值。如果不是引用，返回值默认是rvalue；如果是引用，返回值默认是lvalue。
- 对于函数参数传递的一个假设。貌似无论直接传参数，还是传引用，都能将实参给销毁掉。