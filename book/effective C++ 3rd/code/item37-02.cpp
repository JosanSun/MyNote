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