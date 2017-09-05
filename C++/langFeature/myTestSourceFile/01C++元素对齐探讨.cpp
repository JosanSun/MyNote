#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

struct A1
{
	char c;
};

struct A2
{
	char c1;
	char c2;
	int a;
};


struct A3
{
	char c1;
	int a;
	char c2;
};

struct A4
{

};

struct A5
{
	char c;
	double d;
	char c1[7];
};

//设定预设对齐大小为2
#pragma pack(2)
struct A6
{
	char a;
	int b;
	//short c;
};

struct A7
{
	char b;
};

#pragma pack(4)
struct A8
{
	A6 c1;
	A7 d1;
};

//恢复默认预设大小--8
#pragma pack()
struct A9
{
	char c;
	struct A9_inner
	{
		short ss;
	}a9in;
	double d;
};

struct A10
{
	char c;
	struct A10_inner
	{
		short ss;
		double dd;
	}a10in;
	double d;
};

//即使声明预设对齐大小为2，int位域还是进行32位扩展，而不是16位
#pragma pack(2)
struct A11
{
	short s;
	char c;
	int a1 : 1;
	int a2 : 4;
	int a3 : 7;
};
#pragma pack()

struct A12
{
	short s;
	char c;
	long long a1 : 1;
	long long a2 : 4;
	long long a3 : 7;
};

//位域超过一个整体时，首次超过的那个位域字段需要考虑对齐
struct A13
{
	unsigned a : 19;
	unsigned b : 11;
	//19+11+4 = 34 > 32  因此，c应该在下一个int里面
	unsigned c : 4;
	//同理，4 + 29 = 33 > 32 存在偏移
	unsigned d : 29;
	char index;
};



class Base
{

};

class C1
{
	char c;
	Base b;
};

class C2
{
	char c;
	Base b;
	int a;
};

class C3 :public Base
{
	char c;
};

class Base1
{
	
	char c;
	int a;
};

class C4 :public Base1
{
	char c1;
	double d;
};

class C41
{
	Base1 b;
	char c1;
	double d;
};

class C5 :public Base1
{
	char c1;
	int a;
	double d;
};

class C51
{
	
	char c1;
	Base1 b;
	int a;
	double d;
};

class Base2
{
public:
	virtual ~Base2(){ }
};

class C6
{
	char c;
	Base2 b;
};

class C7
{
	char c;
	Base2 b;
	int a;
};

class C8 :public Base2
{
	char c;
};

class Base3
{
	char c;
public:
	virtual ~Base3()
	{
	}
};

class C9 :public Base3
{
	char c1;
public:
	virtual void print(){ }
};

class Base4
{
public:
	virtual void print() = 0;
};

class C10 :public Base4
{
	char c;
public:
	virtual void print()
	{
	}
};

class Base5
{
	char c;
public:
	virtual void print() = 0;
};

class C11 :public Base5
{
	char c1;
public:
	virtual void print()
	{
	}
};

//测试开始标记
static void printStart()
{
	cout << "--------------------- test ---------------------\n";
}
//测试退出标记
static void printEndLine()
{
	cout << "--------------------- end  ---------------------\n";
}
//测试基本元素的字节数和对齐大小
static void testBaseElement()
{
	printStart();
	cout << "char: " << sizeof(char) << "---" << alignof(char) << endl;
	cout << "int: " << sizeof(int) << "---" << alignof(int) << endl;
	cout << "short: " << sizeof(short) << "---" << alignof(short) << endl;
	cout << "long: " << sizeof(long) << "---" << alignof(long) << endl;
#pragma pack(2)
	//基本类型为一个整体时，不受预设对齐大小的约束
	cout << "long long: " << sizeof(long long) << "---" << alignof(long long) << endl;
#pragma pack()
	cout << "float: " << sizeof(float) << "---" << alignof(float) << endl;
	cout << "double: " << sizeof(double) << "---" << alignof(double) << endl;
	cout << "long double: " << sizeof(long double) << "---" << alignof(long double) << endl;
	void* p = NULL;
	cout << "pointer: " << sizeof(p) << "---" << alignof(char*) << endl;
	printEndLine();
}
//测试struct相关的字节数和对齐大小
static void testOnlyWithStruct()
{
	printStart();
	cout << "struct A1: " << sizeof(A1) << "---" << alignof(A1) << endl;
	cout << "struct A2: " << sizeof(A2) << "---" << alignof(A2) << endl;
	cout << "struct A3: " << sizeof(A3) << "---" << alignof(A3) << endl;
	cout << "struct A4: " << sizeof(A4) << "---" << alignof(A4) << endl;
	cout << "struct A5: " << sizeof(A5) << "---" << alignof(A5) << endl;
	cout << "struct A6: " << sizeof(A6) << "---" << alignof(A6) << endl;
	cout << "struct A6.b: " << sizeof(A6::b) << "---" << offsetof(A6, b) << endl;
	cout << "struct A7: " << sizeof(A7) << "---" << alignof(A7) << endl;
	cout << "struct A8: " << sizeof(A8) << "---" << alignof(A8) << endl;
	cout << "struct A9: " << sizeof(A9) << "---" << alignof(A9) << endl;
	cout << "struct A10: " << sizeof(A10) << "---" << alignof(A10) << endl;
	cout << "struct A11: " << sizeof(A11) << "---" << alignof(A11) << endl;
	cout << "struct A12: " << sizeof(A12) << "---" << alignof(A12) << endl;
	cout << "struct A13: " << sizeof(A13) << "---" << alignof(A13) << endl;
	printEndLine();
}
//测试不存在虚函数的类的字节数和对齐大小
static void testWithClassNonVirtual()
{
	cout << "class Base: " << sizeof(Base) << "---" << alignof(Base) << endl;
	cout << "class C1: " << sizeof(C1) << "---" << alignof(C1) << endl;
	cout << "class C2: " << sizeof(C2) << "---" << alignof(C2) << endl;
	cout << "class C3: " << sizeof(C3) << "---" << alignof(C3) << endl;
	cout << "class Base1: " << sizeof(Base1) << "---" << alignof(Base1) << endl;
	cout << "class C4: " << sizeof(C4) << "---" << alignof(C4) << endl;
	cout << "class C41: " << sizeof(C41) << "---" << alignof(C41) << endl;
	cout << "class C5: " << sizeof(C5) << "---" << alignof(C5) << endl;
	cout << "class C51: " << sizeof(C51) << "---" << alignof(C51) << endl;
}
//测试不存在虚函数的类的字节数和对齐大小
static void testWithClassVirtual()
{
	cout << "class Base2: " << sizeof(Base2) << "---" << alignof(Base2) << endl;
	cout << "class C6: " << sizeof(C6) << "---" << alignof(C6) << endl;
	cout << "class C7: " << sizeof(C7) << "---" << alignof(C7) << endl;
	cout << "class C8: " << sizeof(C8) << "---" << alignof(C8) << endl;
	cout << "class Base3: " << sizeof(Base3) << "---" << alignof(Base3) << endl;
	cout << "class C9: " << sizeof(C9) << "---" << alignof(C9) << endl;
	//alignof(Base4),alignof(Base5)  会报错， 不能实例化抽象类
	cout << "class Base4: " << sizeof(Base4) << "---"  << endl;
	cout << "class C10: " << sizeof(C10) << "---" << alignof(C10) << endl;
	cout << "class Base5: " << sizeof(Base5) << "---"  << endl;
	cout << "class C11: " << sizeof(C11) << "---" << alignof(C11) << endl;

}
//测试类相关的字节数和对齐大小，主要涉及继承和虚函数
static void testWithClass()
{
	printStart();
	testWithClassNonVirtual();
	cout << "\n------------------------------------------------\n" << endl;
	testWithClassVirtual();
	printEndLine();
}

struct D1
{
	int size;
	//使用了非标准扩展；结构/联合中的零大小数组
	//这是C99的柔性数组Flexible Array，也就是变长数组
	char data[0];    //或者char data[];  
};

struct D2
{
	//使用了非标准扩展；结构/联合中的零大小数组
	char data[0];
};

//不能直接定义一个数组大小为0的数组
//char data[0];
//测试柔性数组
static void testOther()
{
	printStart();
	cout << "class D1: " << sizeof(D1) << "---" << alignof(D1) << endl;
	cout << "class D2: " << sizeof(D2) << "---" << alignof(D2) << endl;
	printEndLine();
}

int main()
{
	freopen("out32.txt", "w", stdout);
	testBaseElement();
	cout << endl;
	testOnlyWithStruct();
	cout << endl;
	testWithClass();
	cout << endl;
	testOther();
	return 0;
}