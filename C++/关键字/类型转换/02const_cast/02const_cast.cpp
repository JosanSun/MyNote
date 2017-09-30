#include <iostream>

struct type
{
	type() :i(3)
	{
	}
	void m1(int v) const
	{
		// this->i = v;                 
		// compile error: this is a pointer to const
		const_cast<type*>(this)->i = v; // OK as long as the type object isn't const
	}
	int i;
};

//const_cast < new_type > ( expression )		
//Converts between types with different cv-qualification.
int main()
{
	int i = 3;                    // i is not declared const
	const int& cref_i = i;
	const_cast<int&>(cref_i) = 4; // OK: modifies i
	std::cout << "i = " << i << '\n';  //4

	type t; 
	// note, if this is const type t;, then t.m1(4); is UB
	t.m1(4);
	std::cout << "type::i = " << t.i << '\n';

	const int j = 3; // j is declared const
	int* pj = const_cast<int*>(&j);
	*pj = 4;         // undefined behavior!
	std::cout << "*pj = " << *pj << std::endl;  //4
	std::cout << "j = " << j << std::endl;  //3   其实j已经改为4,但是编译在编译的时候，进行优化，直接将j替换为3，因此，输出为3.


	void (type::*mfp)(int) const = &type::m1; // pointer to member function
	////compiler error: const_cast does not work on function pointers
	//const_cast<void(type::*)(int)>(mfp);


	return 0;
}
