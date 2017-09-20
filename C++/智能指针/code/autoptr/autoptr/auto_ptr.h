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
//	//���κμ��ݵ�auto_ptr��Ϊһ���µ�auto_ptr�ĳ�ֵ
//	template<class U>
//	auto_ptr(auto_ptr<U>& rhs);
//	
//	~auto_ptr();
//	//assignment operator member template
//	//���κμ��ݵ�auto_ptr��Ϊ��ֵ�������Ҷ�
//	auto_ptr<T>& operator=(auto_ptr<T>& rhs);
//	//NOTE::���û�������auto_ptr<T>& operator=(auto_ptr<T>& rhs);ֻ��template<class U>
//	//itmp3 = itest;      //�������bitwise�ĸ�ֵ   
//	template<class U>
//	auto_ptr<T>& operator=(auto_ptr<U>& rhs);
//	T& operator*()const;
//	T* operator->()const;
//
//	//���� dumb pointer
//	T* get()const;
//	//���� dumb pointer��ӵ��Ȩ����������ֵ
//	T* release();
//	//��ӵ�е�ָ��ɾ�������е�p��ӵ��Ȩ
//	void reset(T* p=nullptr);
//
//private:
//	T* pointee;
//	//NOTE:://��������Ч
//	//template<class U>
//	//friend class auto_ptr<U>;
//	//�����е�auto_ptr�඼��Ϊ��һ��auto_ptr��friends
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
