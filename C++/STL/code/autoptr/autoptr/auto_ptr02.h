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

