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

	//��������
	{
		int a = 1000000000;
		long long int b = 10LL * a;
		cout << a << endl;
		cout << b << endl;
	}
	

	return 0;
}