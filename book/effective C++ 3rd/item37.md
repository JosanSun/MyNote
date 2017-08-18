# 条款37：绝不重新定义继承而来的缺省参数值

![](https://github.com/JosanSun/MyNote/blob/master/book/effective%20C++%203rd/pic/item37-02.png?raw=true)

## 问题由来
做了牛客网上面的一道题目，觉得这题是理解条款37的最佳好题，于是顺便进行一下延伸讨论。题目如下：

![](https://github.com/JosanSun/MyNote/blob/master/book/effective%20C++%203rd/pic/item37-01.png?raw=true)

PS: 正确答案B

## 程序代码

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
	//B*p3 = dynamic_cast<B*> (new A);   //dynamic_cast<B*>转化后， p3 = nullptr;
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
	//这个test()的virtual可有可无
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
	//B*p3 = dynamic_cast<B*> (new A);   //dynamic_cast<B*>转化后， p3 = nullptr;
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

从这两个进行对比，可知二者的参数传递值都是一样的，因此，缺省参数值采用的静态联编。
而virtual成员函数可以指针或者引用所指向的对象，决定采用什么样的具体实现函数，这是动态联编。