#define _CRT_SECURE_NO_WARNINGS
// exception constructor
#include <iostream>       // std::cout
#include <exception>      // std::exception
#include <cstring>
using namespace std;

struct ooops : std::exception
{
	const char* what() const noexcept
	{
		return "Ooops!\n";
	}
};

static void testCtor()
{
	ooops e;
	std::exception* p = &e;
	try
	{
		throw e;       // throwing copy-constructs: ooops(e)
	}
	catch(std::exception& ex)
	{
		std::cout << ex.what();
	}
	try
	{
		throw *p;      // throwing copy-constructs: std::exception(*p)
	}
	catch(std::exception& ex)
	{
		std::cout << ex.what();   //默认是 "Unknown exception"
	}
}


// text_exception uses a dynamically-allocated internal c-string for what():
class text_exception : public std::exception
{
	char* text_;
public:
	text_exception(const char* text)
	{
		text_ = new char[std::strlen(text)]; 
		std::strcpy(text_, text);
	}
	text_exception(const text_exception& e)
	{
		text_ = new char[std::strlen(e.text_)]; 
		std::strcpy(text_, e.text_);
	}
	~text_exception()
	{
		cout << "Hello" << endl;
		delete[] text_;    //为什么这边会发生断点？好奇怪！
	}
	const char* what() const noexcept
	{
		return text_;
	}
};

static void testDtor()
{
	try
	{
		throw text_exception("custom text");
	}
	catch(std::exception& ex)
	{
		std::cout << ex.what();
	}
}

static void test()
{
	//testCtor();
	testDtor();
	//testWhat()就在前面两个测试中
}

int main()
{
	test();
	return 0;
}