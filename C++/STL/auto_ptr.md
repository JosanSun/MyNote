[TOC]
# auto_ptr源码解析以及例子 --auto_ptr_ref
## 一、头文件
```C++
#ifndef AUTO_PTR02_H_
#define AUTO_PTR02_H_
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>    
#include <crtdbg.h>

namespace josan{ 
#include <iostream>
	using std::cout;
	using std::endl;

	template<class U>
	struct auto_ptr_ref
	{
		U* up;
		auto_ptr_ref(U* rhs) :up(rhs)
		{
		}
	};

	template<class T>
	class auto_ptr
	{
	private:
		//refers to the actual owned object
		T* ap;
	public:
		//type names for the value
		typedef T element_type;
		//ctor
		explicit inline auto_ptr(T* ptr = nullptr)noexcept;

		//copy ctor (with implicit conversion)
		//note: nonconstant parameter
		auto_ptr(auto_ptr&)noexcept;
		//这个主要用于继承机制，但无法实现auto_ptr<double*> --> auto_ptr<int*>
		template<class U>
		auto_ptr(auto_ptr<U>&) noexcept;

		//assignments (with implicit conversion)
		//note: nonconstant parameter
		auto_ptr& operator=(auto_ptr&)noexcept;
		//这个主要用于继承机制之间指针的转换
		//NOTE::如果没有上面的auto_ptr<T>& operator=(auto_ptr<T>& rhs);只有template<class U>
		//itmp3 = itest;    这两个都是auto_ptr<int>  //这个将是bitwise的赋值   
		template<class U>
		auto_ptr& operator=(auto_ptr<U>&)noexcept;
		//dtor
		~auto_ptr() noexcept;

		//value access
		T* get()const noexcept;
		//noexcept const是一个错误的写法，const必须在前面
		T& operator*()const noexcept;
		T* operator->() const noexcept;
		//release ownership
		T* release()noexcept;
		//reset value
		void reset(T* ptr = nullptr)noexcept;

		//special conversions to enable copies and assignment
		//控制拷贝、赋值。
		auto_ptr(auto_ptr_ref<T> rhs)noexcept;
		auto_ptr& operator=(auto_ptr_ref<T> rhs) noexcept;	
		//同类型的临时变量可以调用这个转换函数，进行类型转换   技巧之处
		template<class U>
		operator auto_ptr_ref<U>()noexcept;
		//配合上面一个转换函数，将派生类的临时变量转换成基类的临时变量
		template<class U>
		operator auto_ptr<U>()noexcept;
	};

	template<class T>
	inline auto_ptr<T>::auto_ptr(T* ptr)noexcept: ap(ptr)
	{

	}

	//完整版
	//template<class T>
	//auto_ptr<T>::auto_ptr(auto_ptr<T>& rhs)noexcept:ap(rhs.release())
	//{
	//
	//}

	//简化版  去掉<T>
	template<class T>
	inline auto_ptr<T>::auto_ptr(auto_ptr& rhs)noexcept:ap(rhs.release())
	{

	}

	template<class T>
	template<class U>
	inline auto_ptr<T>::auto_ptr(auto_ptr<U>& rhs)noexcept :ap(rhs.release())
	{

	}

	template<class T>
	inline auto_ptr<T>& auto_ptr<T>::operator=(auto_ptr& rhs)noexcept
	{
		reset(rhs.release());
		return *this;
	}

	template<class T>
	template<class U>
	inline auto_ptr<T>&  auto_ptr<T>::operator=(auto_ptr<U>& rhs)noexcept
	{
		reset(rhs.release());
		return *this;
	}

	//NOTE:奇怪，为什么dtor没有或者有noexcept都能正常运行，而其他成员函数却不可以，包括ctor
	template<class T>
	inline auto_ptr<T>::~auto_ptr()  noexcept
	{
		cout << "dtor is called" << endl;
		delete ap;
	}

	template<class T>
	inline T* auto_ptr<T>::get()const noexcept
	{
		return ap;
	}

	template<class T>
	inline T& auto_ptr<T>::operator*()const noexcept
	{
		return *ap;
	}

	template<class T>
	inline T* auto_ptr<T>::operator->()const noexcept
	{
		return ap;
	}

	template<class T>
	inline T* auto_ptr<T>::release() noexcept
	{
		T* tmp(ap);
		ap = nullptr;
		return tmp;
	}

	template<class T>
	inline void auto_ptr<T>::reset(T* ptr) noexcept
	{
		if(ap != ptr)
		{
			delete ap;
			ap = ptr;
		}
	}

	//----------------special
	template<class T>
	inline auto_ptr<T>::auto_ptr(auto_ptr_ref<T> rhs)noexcept:ap(rhs.up)
	{

	}

	template<class T>
	inline auto_ptr<T>& auto_ptr<T>::operator=(auto_ptr_ref<T> rhs)noexcept
	{
		reset(rhs.up);
		return *this;
	}

	template<class T>
	template<class U>
	inline auto_ptr<T>::operator auto_ptr_ref<U>() noexcept
	{
		return auto_ptr_ref<U>(release());
	}

	template<class T>
	template<class U>
	inline auto_ptr<T>::operator auto_ptr<U>() noexcept
	{
		cout << "DONE" << endl;
		return auto_ptr<U>(release());
	}
}
#endif // !AUTO_PTR02_H_
```

## 二、测试用例
```C++
/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/1 21:53:11
 */
#define _CRT_SECURE_NO_WARNINGS
#define _WINDOWS 1
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <iostream>
#include <cstdio>
#include "auto_ptr02.h"
using namespace std;
using namespace josan;
class A
{
public:
	int a;
	A(int aa = 0):a(aa){ }
};

class B :public A
{
public:
	int b;
	B(int aa = 10, int bb = 10) :A(aa), b(bb)
	{

	}
};

auto_ptr<int> fun()
{
	return auto_ptr<int>(new int{789});
}

auto_ptr<A> fun1()
{
	return auto_ptr<B>(new B);
}

int main()
{
	freopen("out.txt", "w", stdout);
	//检查内存泄漏
#ifdef _WINDOWS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	{
		auto_ptr<int> iptr(new int);
		*iptr = 100;
		auto_ptr<double> dptr(new double);
		*dptr = 123.25;
		cout << *iptr << endl;
		cout << *dptr << endl;
		//非法操作
		//dptr = iptr;

		//---------section 1 --------------
		//auto_ptr<int> itmp(new int);
		//*itmp = 50;
		//int* a = itmp.get();
		//cout << *a << endl;

		//itmp.reset(new int);
		//*itmp = 80;
		//
		//auto_ptr<int> itmp2(itmp);
		////itmp里面的ap已经变为nullptr
		////cout << *itmp << endl;
		//cout << *itmp2 << endl;
		////这样会导致内存泄漏,需加入delete b
		//int* b = itmp2.release();
		//cout << *b << endl;
		//delete b;

		//---------section 2 --------------
		auto_ptr<int> itest(new int);
		*itest = 20;
		auto_ptr<int> itmp3;
		itmp3 = itest;
		//cout << *itest << endl;
		cout << *itmp3 << endl;
		
		auto_ptr<A> itmp4(new A);
		itmp4->a = -10;
		////error
		//cout << *itmp4 << endl;
		cout << itmp4->a << endl;

		auto_ptr<B>  itmp5(new B);
		cout << itmp5->a << ", " << itmp5->b << endl;
		//无法从A*转换为B*
		//itmp5 = itmp4;
		itmp4 = itmp5;
//		cout << itmp5->a << ", " << itmp5->b << endl;   //itmp5释放
		cout << itmp4->a << endl;

		auto_ptr<B>  itmp6(new B);
		auto_ptr<A> itmp7(itmp6);
//		cout << itmp6->a << ", " << itmp6->b << endl;
		cout << itmp7->a << endl;
		
		//---------section 3 -------------- special 		
		auto_ptr<int> itest1(new int);
		*itest1 = 20;
		int* a1 = new int(123);
		const auto_ptr<int> itmp8(a1);
		//const的auto_ptr不能被拷贝和赋值。
		//itest1 = itmp8;    始终错误
		//const auto_ptr<int> itmp9(itmp8);

		//临时变量加入special之后，可以赋值！！！记得visual studio 需要禁用语言扩展  打开/Za
		auto_ptr<int> itest2(fun());
		cout << "itest2: " << *itest2 << endl;
		auto_ptr<int> itest3;
		itest3 = fun();
		cout << "itest3: " << *itest3 << endl;
		auto_ptr<A> itest4(fun1());
	}
	
	return 0;
}
```

## 三、结果

```
100
123.25
20
-10
10, 10
10
10
dtor is called
dtor is called
itest2: 789
dtor is called
dtor is called
itest3: 789
DONE
dtor is called
dtor is called
dtor is called
dtor is called
dtor is called
dtor is called
dtor is called
dtor is called
dtor is called
dtor is called
dtor is called
dtor is called
dtor is called
dtor is called
dtor is called
dtor is called
dtor is called
```

## 四、分析

- 未加入special conversions也就是auto_ptr_ref的情况

可以拷贝和赋值non-const的auto_ptr 。同时，禁止拷贝和赋值const的auto_ptr的功能。但无法拷贝和赋值临时变量。（auto_ptr(右值)）

- 加入special conversions也就是auto_ptr_ref的情况
仍然不能对const的auto_ptr也能被拷贝和赋值，但是支持拷贝和赋值临时变量。
```
临时变量具有以下特点：[参考1]
1. 临时变量不能绑定到带有非常量的引用。（移动引用可以解决这类问题）
2. 临时变量可以调用非const成员函数。（正常的const常量无法调用非const成员函数）
总结，临时变量似const常量，但却不是const常量。
```
再来看**测试程序**

`auto_ptr<int> itest2(fun());`这里fun()中return语句会产生临时变量，临时变量由于以上特性会自动调用`template<class U>  operator auto_ptr_ref<U>()noexcept;`进行类型转换，然后调用`auto_ptr(auto_ptr_ref<T> rhs)noexcept;`。注意：此处的U和T都被实例化为int。
`itest3 = fun();`这里fun()中return语句会产生临时变量，临时变量由于以上特性会自动调用`template<class U>  operator auto_ptr_ref<U>()noexcept;`进行类型转换，然后调用`auto_ptr& operator=(auto_ptr_ref<T> rhs) noexcept;`。注意：此处的U和T都被实例化为int。
`auto_ptr<A> itest4(fun1());`这里fun()中return语句会产生临时变量，临时变量由于以上特性会先调用`template<class U>  operator auto_ptr<U>()noexcept;`此处的U被实例化为A；然后，调用`template<class U>  operator auto_ptr_ref<U>()noexcept;`进行类型转换，此处的U被实例化为A；最后，调用`auto_ptr& operator=(auto_ptr_ref<T> rhs) noexcept;`，此处的T都被实例化为A。
PS:如果找不到一手资料的话，单凭C++基础根本无法理解这个trick！国内写的auto_ptr都避开了这个问题，于是查stackoverflow查到最终想要的结果。这个过程虽然费时，但是知道结果的感觉真的很棒！
## 五、注意点
visual studio默认是打开语言扩展的，因此它会对程序进行优化，从而过滤掉临时变量。因此，必须禁用语言扩展功能。具体设置方法，点项目属性-> C/C++ -> 语言 -> 禁用语言扩展 -> 是

gcc编译器的话，为了观察临时变量，需要打开`--no-elide-constructors`选项。

## 六、总结收获
1. 加深了对explicit, throw(), noexcept, inline的理解
2. 模板类中包含模板成员函数
3. 模板类中的成员函数在类外定义
4. 临时变量的理解


## 七、参考资料
1. [More C++ Idioms/Move Constructor](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Move_Constructor)--详细介绍了临时变量的特性
2. [Can you give me an example when auto_ptr_ref is really necessary?](https://stackoverflow.com/questions/6266014/can-you-give-me-an-example-when-auto-ptr-ref-is-really-necessary)
3. [what is auto_ptr_ref, what it achieves and how it achieves it](https://stackoverflow.com/questions/2121844/what-is-auto-ptr-ref-what-it-achieves-and-how-it-achieves-it)