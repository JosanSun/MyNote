/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               �����ߣ� Josan
 *             ����ʱ�䣺 2017/10/2 15:10:51
 */
#include <iostream>
using namespace std;

int main()
{
	//α��������
	{
		const int a = 100;
		int * b = const_cast<int *>(&a);
		++*b;
		cout << *b << endl;  //101
		cout << a << endl;  //100  �������Ż�����ʵa��ֵ�Ѿ���Ϊ101  ���Ե�ʱ��Ҳ������֤���
	}
	{
		volatile const int a = 100;
		int * b = const_cast<int *>(&a);
		++*b;
		cout << *b << endl;  //101
		cout << a << endl;  //101  ָ��volatile ȥ���������Ż������Եõ�101
	}

	return 0;
}