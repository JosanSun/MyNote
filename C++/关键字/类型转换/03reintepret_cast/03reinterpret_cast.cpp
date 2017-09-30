#include <cstdint>
#include <cassert>
#include <iostream>
int f()
{
	return 42;
}

//reinterpret_cast < new_type > ( expression )		
//Converts between types by reinterpreting the underlying bit pattern.
int main()
{
	int i = 7;

	// pointer to integer and back
	uintptr_t v1 = reinterpret_cast<uintptr_t>(&i); // static_cast is an error
	std::cout << "The value of &i is 0x" << std::hex << v1 << '\n';
	int* p1 = reinterpret_cast<int*>(v1);
	assert(p1 == &i);

	// pointer to function to another and back
	void(*fp1)() = reinterpret_cast<void(*)()>(f);
	// fp1(); undefined behavior
	int(*fp2)() = reinterpret_cast<int(*)()>(fp1);
	std::cout << std::dec << fp2() << '\n'; // safe

	// type aliasing through pointer
	char* p2 = reinterpret_cast<char*>(&i);
	if(p2[0] == '\x7')
		std::cout << "This system is little-endian\n";
	else
		std::cout << "This system is big-endian\n";

	// type aliasing through reference
	reinterpret_cast<unsigned int&>(i) = 42;
	std::cout << i << '\n';

	const int &const_iref = i;
	//int &iref = reinterpret_cast<int&>(const_iref); //compiler error - can't get rid of const
	//Must use const_cast instead:  int &iref = const_cast<int&>(const_iref);

	return 0;
}