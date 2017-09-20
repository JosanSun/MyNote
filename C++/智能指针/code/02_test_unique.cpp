/*
* ---------------------------------------------------
*  Copyright (c) 2017 josan All rights reserved.
* ---------------------------------------------------
*
*               �����ߣ� Josan
*             ����ʱ�䣺 2017/9/20 8:37:47
*/
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <memory>   //unique_ptr
#include <iostream>
using namespace std;


//---------------����ָ��POD���͵�unique_ptr()  test_POD()-------------------
void deleteInt(int* p)
{
	cout << "Ready to delete an int" << endl;
	delete p;
}

void test_POD()
{
	//1 ctor, copy ctor(=delete  �����ڿ�����ֵ)unique_ptr (const unique_ptr&) = delete;   ���������ƶ���������
	//��unique_ptr
	unique_ptr<int> u1;
	unique_ptr<int> u2(new int{2});
	////error  ���ʹ��ģ�����2�Ĺ��캯����Ҳ���ǿ�ָ�룬����������⣬��˴���  ���ֻ��u5�ǿ������е�
	//unique_ptr<int, decltype(deleteInt)*> u3;
	//unique_ptr<int, decltype(deleteInt)*> u4(new int);       
	unique_ptr<int, decltype(deleteInt)*> u5(new int(3), deleteInt);
	//unique_ptr<int, decltype(deleteInt)*> u6(deleteInt);   //error
	unique_ptr<int, decltype(deleteInt)*> u7(new int(111), deleteInt);
	//u7.reset(u5.release());

	//2 assign  (unique_ptr& operator= (const unique_ptr&) = delete;)
	//�ͷ�uָ��Ķ���ͬʱ��u��Ϊ��
	u1 = nullptr;
	////error  �޷�ֱ�Ӹ�ֵ
	//u1 = u2;
	u1 = move(u2);

	
	//3 ���� release �� reset ��Ա����
	//WARNINGS: u2�ͷ�ָ�룬������ָ���ֵ�����û��׽ס���ָ�룬�ͻ�����ڴ�й©
	u2.release();  //й©
	
	u2.reset(new int{100});
	//u2�ͷ�ָ��
	u2.reset();
	//u2����ָ��Ϊ�գ��Կ��Լ���reset()
	u2.reset(nullptr);
	int * p = new int{123};
	u2.reset(p);

	//����reset���÷�
	u1.reset(u2.release());
}

//---------------����unique_ptr�ĸ��ֳ�Ա����  ������������cplusplus.com-------
static void testCtor()
{
	std::default_delete<int> d;
	std::unique_ptr<int> u1;
	std::unique_ptr<int> u2(nullptr);
	std::unique_ptr<int> u3(new int);
	std::unique_ptr<int> u4(new int, d);
	std::unique_ptr<int> u5(new int, std::default_delete<int>());
	//ERROR: ���Բ�ͨ��������cplusplus����˼�ǲ���ͨ������
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

//���Գ�Ա����get()
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
	//NOTE:��ʱbar��Ȼ������ָ��
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

//���Գ�Ա����get_deleter()
static void testGet_deleter()
{
	state_deleter del;

	std::unique_ptr<int> p;   // uses default deleter

							  // alpha and beta use independent copies of the deleter:
	std::unique_ptr<int, state_deleter> alpha(new int);
	std::unique_ptr<int, state_deleter> beta(new int, alpha.get_deleter());

	// gamma and delta share the deleter "del" (deleter type is a reference!):
	std::unique_ptr<int, state_deleter&> gamma(new int, del);
	std::unique_ptr<int, state_deleter&> delta(new int, gamma.get_deleter());  //���߹���ͬһ��ɾ����

	std::cout << "resetting alpha..."; alpha.reset(new int);
	std::cout << "resetting beta..."; beta.reset(new int);
	std::cout << "resetting gamma..."; gamma.reset(new int);
	std::cout << "resetting delta..."; delta.reset(new int);

	std::cout << "calling gamma/delta deleter...";
	gamma.get_deleter()(new int);

	alpha.get_deleter() = state_deleter();  // a brand new deleter for alpha

											// additional deletions when unique_ptr objects reach out of scope
											// (in inverse order of declaration)
	//����֮ǰ��alpha, beta, gamma, delta�е�count �ֱ�Ϊ0�� 1�� 3�� 3
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

//���Գ�Ա����swap()
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
	////���Գ�Ա����get()   ע���ʱԴ��ַδʧЧ
	//testGet();
	////���Գ�Ա����get_deleter()
	//testGet_deleter();
	////����ת��������Ҳ����ת����bool
	////��. Oops...
	////����reset(), release()
	////��. Oops...
	////����swap
	//testSwap();
}

//��cplusplusժȡ�Ĳ���������
static void testFromCPlusPlus()
{
	//���Թ��캯��
	testCtor();
	//���Դ��Զ���ɾ����
	testCtorWithMyDeleter();
	//���Ը�ֵ����
	testAssignment();
	//���Գ�Ա����
	testMemberFunction();
}

unique_ptr<int> fun(unique_ptr<int> u)
{
	cout << "fun: u -> " << *u << endl;
	return u;
}

//return u�ᱨ���޷������Ѿ�ɾ����u??
unique_ptr<int> fun1(unique_ptr<int>& u)
{
	cout << "fun: u -> " << *u << endl;
	return move(u);    //return u; ����
}

//����һ�����ã�Ҳ������ζ�ŷ��ص���һ��lvalue;
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
	////���������޷�ת��
	//unique_ptr<int> u2 = fun(u1);
	
	unique_ptr<int> u3 = fun(move(u1));   //���ص���ʱ������rvalue; ���⣬u1ָ��Ϊ��
	//or:  unique_ptr<int> u3 = move(fun(move(u1)));
	cout << *u3 << endl;



	//other test:   For fun.    ����������صĲ���
	//unique_ptr<int> u4 = fun1(u3);          //u3Ϊ��
	//cout << *u4 << endl;                      //100
	//unique_ptr<int> u5 = move(fun2(move(u3)));
	////unique_ptr<int> u5 = fun2(move(u3));    //����ᱨ�������Ѿ�ɾ���ı���
	//cout << *u5 << endl;                    //һ�������   1904870    ���ִ�ֵ�Ǵ����
	//unique_ptr<int> u6 = move(fun3(u3));
	//cout << *u6 << endl;       //100
	
	{
		unique_ptr<int>& u6 = u3;
		cout << *u6 << endl;   //100    *u3---100
	}
	cout << *u3 << endl;    //��Ȼ������ȷ���100
}

//�ܲ���
static void test()
{
	////����ָ��POD���͵�unique_ptr()
	//test_POD();
	////����unique_ptr�ĸ��ֳ�Ա����  ������������cplusplus.com
	//testFromCPlusPlus();
	//���Բ�������
	testParameterPass();
	//���Զ�̬������ָ���upcast����downcast��ת����
	//wait to test
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	test();
	return 0;
}