/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               �����ߣ� Josan
 *             ����ʱ�䣺 2017/9/22 11:02:50
 */
#include <iostream>
#include <type_traits>
using namespace std;

struct X
{
	X() = default;
};

struct Y
{
	Y()
	{
	};
};

//NOYE: ֻ�������������⺯����������Ϊ = default
/*
 * Special member functions
 * constructors and destructors are non-static member functions that use a special syntax for their declarations (see their pages for details).
 * Some member functions are special: under certain circumstances they are defined by the compiler even if not defined by the user. They are:

 * Default constructor
 * Copy constructor
 * Move constructor (since C++11)
 * Copy assignment operator
 * Move assignment operator (since C++11)
 * Destructor

 * Special member functions are the only functions that can be defaulted, that is, defined using = default instead of the function body (see their pages for details)
 */

class C
{
public:
	////����1�� ���Ͷ���Ĭ�Ϲ��캯����Ч
	//C(int x) = default;
	C(int x) :a(x)
	{

	}
	C() = default;
	//����2�� C(C&) = default;��C(const C&) = default; ֻ�ܴ���һ����������߶����֣��ͻᱨ��
	//C(C&) = default;
	C(const C&) = default;
	//����3�� C(const C&&) = default; ���ǿ�Ĭ��Ϊ�������Ա����
	//C(const C&&) = default;
	C(C&&) = default;
	C& operator=(const C&) & = default;
	C& operator=(C&&) & = default;
	virtual ~C()
	{
	}
private:
	int a;
};

void testDefaultFunction()
{
	static_assert(std::is_trivial<X>::value, "X should be trivial");  //X��ƽ����
	static_assert(std::is_pod<X>::value, "X should be POD");
	static_assert(!std::is_trivial<Y>::value, "Y should not be trivial");  //Y����ͨ��
	static_assert(!std::is_pod<Y>::value, "Y should not be POD");
	C c1;
	C c2(2);
}

int main()
{
	testDefaultFunction();
	return 0;
}

