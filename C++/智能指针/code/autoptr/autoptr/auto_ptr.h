//#ifndef AUTO_PTR_H_
//#define AUTO_PTR_H_
//
//#include <iostream>
//using std::cout;
//using std::endl;
//
//template<class T>
//class auto_ptr
//{
//public:
//	explicit auto_ptr(T* p = nullptr);
//	//copy constructor member template
//	auto_ptr(auto_ptr& rhs);
//	//以任何兼容的auto_ptr作为一个新的auto_ptr的初值
//	template<class U>
//	auto_ptr(auto_ptr<U>& rhs);
//	
//	~auto_ptr();
//	//assignment operator member template
//	//以任何兼容的auto_ptr作为赋值动作的右端
//	auto_ptr<T>& operator=(auto_ptr<T>& rhs);
//	//NOTE::如果没有上面的auto_ptr<T>& operator=(auto_ptr<T>& rhs);只有template<class U>
//	//itmp3 = itest;      //这个将是bitwise的赋值   
//	template<class U>
//	auto_ptr<T>& operator=(auto_ptr<U>& rhs);
//	T& operator*()const;
//	T* operator->()const;
//
//	//返回 dumb pointer
//	T* get()const;
//	//撤回 dumb pointer的拥有权，并返回其值
//	T* release();
//	//将拥有的指针删除；并承担p的拥有权
//	void reset(T* p=nullptr);
//
//private:
//	T* pointee;
//	//NOTE:://此声明无效
//	//template<class U>
//	//friend class auto_ptr<U>;
//	//让所有的auto_ptr类都成为另一个auto_ptr的friends
//	template<class U>
//	friend class auto_ptr;
//};
//
//template<class T>
//  auto_ptr<T>::auto_ptr(T* p) :pointee(p)
//{
//
//}
//
//template<class T>
//auto_ptr<T>::auto_ptr(auto_ptr<T>& rhs) :pointee(rhs.release())
//{
//}
//
//template<class T>
//	template<class U>
//	  auto_ptr<T>::auto_ptr(auto_ptr<U>& rhs) :pointee(rhs.release())
//	{
//		
//	}
//
//template<class T>
//  auto_ptr<T>::~auto_ptr()
//{
//	  cout << "dtor is called" << endl;
//	delete pointee;
//}
//
//  template<class T>
//  auto_ptr<T>& auto_ptr<T>::operator=(auto_ptr<T>& rhs)
//  {
//	  if(this != &rhs)
//	  {
//		  reset(rhs.release());
//	  }
//	  return *this;
//  }
//
//template<class T>
//template<class U>
//  auto_ptr<T>& auto_ptr<T>::operator=(auto_ptr<U>& rhs)
//{
//	if(this != &rhs)
//	{
//		reset(rhs.release());
//	}
//	return *this;
//}
//
//template<class T>
//  T& auto_ptr<T>::operator*()const
//{
//	return *pointee;
//}
//
//template<class T>
//  T* auto_ptr<T>::operator->()const
//{
//	return pointee;
//}
//
//template<class T>
//  T* auto_ptr<T>::get()const
//{
//	return pointee;
//}
//
//template<class T>
//  T* auto_ptr<T>::release()
//{
//	T* oldPointee = pointee;
//	pointee = nullptr;
//	return oldPointee;
//}
//
//template<class T>
//  void auto_ptr<T>::reset(T* p)
//{
//	if(p != pointee)
//	{
//		delete pointee;
//		pointee = p;
//	}
//}
//
//#endif
