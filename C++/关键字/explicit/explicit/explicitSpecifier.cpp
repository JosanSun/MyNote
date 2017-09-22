/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               �����ߣ� Josan
 *             ����ʱ�䣺 2017/9/22 15:56:55
 */
// The explicit specifier specifies that a constructor or conversion function(since C++11) doesn't allow implicit conversions or copy-initialization. It may only appear within the decl-specifier-seq of the declaration of such a function within its class definition.

struct A
{
	A(int)
	{
	}      // converting constructor
	A(int, int)
	{
	} // converting constructor (C++11)
	operator bool() const
	{
		return true;
	}
};

struct B
{
	explicit B(int)
	{
	}
	explicit B(const B&)
	{

	}
	explicit B(B&&)
	{

	}
	//������ʹ��explicit
	/*explicit B& operator=(const B&)
	{

	}
	explicit fun(const B&)
	{

	}*/
	explicit B(int, int)
	{
	}
	explicit operator bool() const
	{
		return true;
	}
};

int main()
{
	A a1 = 1;      // OK: copy-initialization selects A::A(int)
	A a2(2);       // OK: direct-initialization selects A::A(int)
	A a3{4, 5};   // OK: direct-list-initialization selects A::A(int, int)
	A a4 = {4, 5}; // OK: copy-list-initialization selects A::A(int, int)
	A a5 = (A)1;   // OK: explicit cast performs static_cast
	if(a1);      // OK: A::operator bool()
	bool na1 = a1; // OK: copy-initialization selects A::operator bool()
	bool na2 = static_cast<bool>(a1); // OK: static_cast performs direct-initialization
	
									  
	//B b1 = 1;      // error: copy-initialization does not consider B::B(int)
	B b2(2);       // OK: direct-initialization selects B::B(int)
	B b3{4, 5};   // OK: direct-list-initialization selects B::B(int, int)
	//B b4 = {4, 5}; // error: copy-list-initialization does not consider B::B(int,int)
	//B b5 = (B)1;   // error: explicit B(const B&) or explicit B(B&&) ��֯���ÿ������캯��
	if(b2);      // OK: B::operator bool()
	//bool nb1 = b2; // error: copy-initialization does not consider B::operator bool()
	bool nb2 = static_cast<bool>(b2); // OK: static_cast performs direct-initialization

	return 0;
}