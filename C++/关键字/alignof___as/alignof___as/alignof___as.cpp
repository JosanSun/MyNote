#include <iostream>   // #include <cstdalign>  //alginas alginof
#define TEST_CASE(name) static void name()

struct Foo
{
	int   i;
	float f;
	char  c;
};

struct Empty
{
};

struct alignas(64) Empty64
{

};


//²âÊÔalginof²Ù×÷·û
//alignof operator (since C++11)
//alignof( type-id )		  Returns a value of type std::size_t.
TEST_CASE(test_alignof)
{
	std::cout << "Alignment of"  "\n"
		"- char             : " << alignof(char) << "\n"      //1
		"- pointer          : " << alignof(int*) << "\n"      //4  32bit
		"- class Foo        : " << alignof(Foo) << "\n"       //4
		"- empty class      : " << alignof(Empty) << "\n"     //1
		"- alignas(64) Empty: " << alignof(Empty64) << "\n";  //64
}

//²âÊÔalginasÏÞ¶¨·û
//alignas specifier (since C++11)

/* alignas( expression )
 * alignas( type-id )
 * alignas( pack ... )
 */
TEST_CASE(test_alignas)
{
	// every object of type sse_t will be aligned to 16-byte boundary
	struct alignas(16) sse_t
	{
		float sse_data[4];
	};
	struct sse_t1
	{
		float sse_data[4];
	};

	std::cout << "Alignment of"  "\n"
		"- sse_t             : " << alignof(sse_t) << "\n"    //16
		"- sse_t             : " << alignof(sse_t1) << "\n";  //4
	
															  
	// the array "cacheline" will be aligned to 128-byte boundary
	struct tmp
	{
		alignas(128) char cacheline[128];
	};
	struct tmp1
	{
		char cacheline[128];
	};
	std::cout << "Alignment of"  "\n"
		"- cachline_t             : " << alignof(tmp) << "\n"  //128
		"- cachline_t1             : " << alignof(tmp1) << "\n";  //1
}

TEST_CASE(test)
{
	test_alignof();
	test_alignas();
}

int main()
{
	test();
	return 0;
}