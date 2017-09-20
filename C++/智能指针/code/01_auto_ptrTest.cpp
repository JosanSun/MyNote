/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               �����ߣ� Josan
 *             ����ʱ�䣺 2017/9/1 21:53:11
 */
#define _CRT_SECURE_NO_WARNINGS
#define _WINDOWS 1
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <iostream>
#include <cstdio>
#include "01_auto_ptr.h"
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
	//freopen("out.txt", "w", stdout);
	//����ڴ�й©
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
		//�Ƿ�����
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
		////itmp�����ap�Ѿ���Ϊnullptr
		////cout << *itmp << endl;
		//cout << *itmp2 << endl;
		////�����ᵼ���ڴ�й©,�����delete b
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
		//�޷���A*ת��ΪB*
		//itmp5 = itmp4;
		itmp4 = itmp5;
//		cout << itmp5->a << ", " << itmp5->b << endl;   //itmp5�ͷ�
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
		//const��auto_ptr���ܱ������͸�ֵ��
		//itest1 = itmp8;    ʼ�մ���
		//const auto_ptr<int> itmp9(itmp8);

		//��ʱ��������special֮�󣬿��Ը�ֵ�������ǵ�visual studio ��Ҫ����������չ  ��/Za
		auto_ptr<int> itest2(fun());
		cout << "itest2: " << *itest2 << endl;
		auto_ptr<int> itest3;
		itest3 = fun();
		cout << "itest3: " << *itest3 << endl;
		auto_ptr<A> itest4(fun1());
	}
	
	return 0;
}

