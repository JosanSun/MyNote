//#include <iostream>
//#include <type_traits>
//#include <cstdint>
//
///*
// * If T and U name the same type **with the same const-volatile qualifications**, provides the member constant value equal to true. Otherwise value is false.
// */
//
//void print_separator()
//{
//	std::cout << "-----\n";
//}
//
//int main()
//{
//	std::cout << std::boolalpha;
//
//	std::cout << std::is_same<int, int32_t>::value << '\n';
//	std::cout << typeid(std::is_same<int, int32_t>::type).name() << '\n';
//	//std::cout << typeid(std::is_same<int, int32_t>::type).raw_name() << '\n';
//	std::cout << typeid(std::is_same<int, int32_t>::value_type).name() << '\n';
//	if(std::is_same<int, int32_t>())    //operator bool
//	{
//		std::cout << "This is a test.\n"; 
//	}
//	if(std::is_same<int, int32_t>()())   //operator()
//	{
//		std::cout << "This is a test.\n";
//	}
//	//error
//	//if(std::is_same<int, int32_t>()()())
//	//{
//	//	std::cout << "This is a test.\n";
//	//}
//	//std::cout << typeid(std::is_same<int, int32_t>::value_type).raw_name() << '\n';
//
//	std::cout << std::is_same<const int, int32_t>::value << '\n'; //false
//	std::cout << std::is_same<int, int32_t>::value << '\n';   // true
//	std::cout << std::is_same<int, int64_t>::value << '\n';   // false
//	std::cout << std::is_same<float, int32_t>::value << '\n'; // false
//
//	print_separator();
//
//	std::cout << std::is_same<int, int>::value << "\n";          // true
//	std::cout << std::is_same<int, unsigned int>::value << "\n"; // false
//	std::cout << std::is_same<int, signed int>::value << "\n";   // true
//
//	print_separator();
//
//	// unlike other types 'char' is not 'unsigned' and not 'signed'
//	std::cout << std::is_same<char, char>::value << "\n";          // true
//	std::cout << std::is_same<char, unsigned char>::value << "\n"; // false
//	std::cout << std::is_same<char, signed char>::value << "\n";   // false
//
//	return 0;
//}