# ����37���������¶���̳ж�����ȱʡ����ֵ

![](https://github.com/JosanSun/MyNote/blob/master/book/effective%20C++%203rd/pic/item37-02.png?raw=true)

## ��������
����ţ���������һ����Ŀ�������������������37����Ѻ��⣬����˳�����һ���������ۡ���Ŀ���£�

![](https://github.com/JosanSun/MyNote/blob/master/book/effective%20C++%203rd/pic/item37-01.png?raw=true)

PS: ��ȷ��B

## �������

```C++
#include <iostream>
using namespace std;
class A
{
public:
	virtual void func(int val = 1)
	{
		std::cout << "A->" << val << std::endl;
	}
	virtual void test()
	{
		func();
	}
};
class B : public A
{
public:
	void func(int val = 0)
	{
		std::cout << "B->" << val << std::endl;
	}
};
int main(int argc, char* argv[])
{
	A*p1 = new A;
	A*p2 = new B;
	//B*p3 = new A;    //error
	//B*p3 = dynamic_cast<B*> (new A);   //dynamic_cast<B*>ת���� p3 = nullptr;
	B*p3 =  reinterpret_cast<B*> (new A);
	B*p4 = new B;
	//test()
	p1->test();    //A->1
	p2->test();    //B->1
	p3->test();    //A->1
	p4->test();    //B->1

	//func()
	p1->func();    //A->1
	p2->func();    //B->1
	p3->func();    //A->0
	p4->func();    //B->0
	return 0;
}
```

```C++
#include <iostream>
using namespace std;
class A
{
public:
	void func(int val = 1)
	{
		std::cout << "A->" << val << std::endl;
	}
	//���test()��virtual���п���
	virtual void test()
	{
		func();
	}
};
class B : public A
{
public:
	void func(int val = 0)
	{
		std::cout << "B->" << val << std::endl;
	}
};
int main(int argc, char* argv[])
{
	A*p1 = new A;
	A*p2 = new B;
	//B*p3 = new A;    //error
	//B*p3 = dynamic_cast<B*> (new A);   //dynamic_cast<B*>ת���� p3 = nullptr;
	B*p3 = reinterpret_cast<B*> (new A);
	B*p4 = new B;
	//test()
	p1->test();    //A->1
	p2->test();    //A->1
	p3->test();    //A->1
	p4->test();    //A->1

				   //func()
	p1->func();    //A->1
	p2->func();    //A->1
	p3->func();    //B->0
	p4->func();    //B->0
	return 0;
}
```

�����������жԱȣ���֪���ߵĲ�������ֵ����һ���ģ���ˣ�ȱʡ����ֵ���õľ�̬���ࡣ
��virtual��Ա��������ָ�����������ָ��Ķ��󣬾�������ʲô���ľ���ʵ�ֺ��������Ƕ�̬���ࡣ