///*
// * ---------------------------------------------------
// *  Copyright (c) 2017 josan All rights reserved.
// * ---------------------------------------------------
// *
// *               创建者： Josan
// *             创建时间： 2017/9/22 15:26:19
// */
// // NVC_Function_Try.cpp
// // Compile by using /EHsc
//#include <iostream>
//#include <ostream>
//#include <stdexcept>
//#include <string>
//using namespace std;
//
//class Name
//{
//public:
//	Name(const string& strFirstName, const string& strLastName)
//	{
//		if(strFirstName == "")
//		{
//			throw runtime_error("Error in Name::Name(): first name parameter must not be blank.");
//		}
//
//		if(strLastName == "")
//		{
//			throw runtime_error("Error in Name::Name(): last name parameter must not be blank.");
//		}
//
//		m_firstName = strFirstName;
//		m_lastName = strLastName;
//
//		cout << "Inside Name::Name(): My name is " << GetName() << "." << endl;
//	}
//
//	~Name()
//	{
//		cout << "Inside Name::~Name(): Destroying " << GetName() << "." << endl;
//	}
//
//	string GetName()
//	{
//		return m_firstName + " " + m_lastName;
//	}
//
//private:
//	string m_firstName;
//	string m_lastName;
//};
//
//class Person
//{
//public:
//	Person(const string& strFirstName, const string& strLastName)
//		// begin function-try block
//		try : m_name(strFirstName, strLastName)
//	{
//	}
//	catch(const runtime_error& err)
//	{
//		cout << "Caught exception inside Person::Person()." << endl;
//		cout << err.what() << endl;
//		// The exception will be automatically rethrown.
//	}
//
//	~Person()
//	{
//		cout << "Inside Person::~Person(): Destroying " << m_name.GetName() << "." << endl;
//	}
//
//private:
//	Name m_name;
//};
//
//int main()
//{
//	try
//	{
//		// Test 1 - Valid Parameters 
//		{
//			cout << "Attempting to construct an object of class Person." << endl;
//			cout << "Passing parameters: \"John\", \"Smith\"" << endl;
//			Person person1("John", "Smith");
//		}
//
//		cout << "Test 1 completed." << endl;
//
//		// Test 2 - Invalid first name parameter
//		{
//			// Note that an exception will be thrown in Name's constructor,
//			//  as the first name parameter must not be blank.
//			//  Because this exception is thrown, person2's destructor
//			//  is never called.
//			cout << "Attempting to construct an object of class Person." << endl;
//			cout << "Passing parameters: \"\", \"Jones\"" << endl;
//			Person person2("", "Jones");
//		}
//	}
//	catch(const runtime_error&)
//	{
//		cout << "Exception caught within main()." << endl;
//	}
//	return 0;
//}
//
//// Output:
//// --------------------------
//// Attempting to construct an object of class Person.
//// Passing parameters: "John", "Smith"
//// Inside Name::Name(): My name is John Smith.
//// Inside Person::~Person(): Destroying John Smith.
//// Inside Name::~Name(): Destroying John Smith.
//// Test 1 completed.
//// Attempting to construct an object of class Person.
//// Passing parameters: "", "Jones"
//// Caught exception inside Person::Person().
//// Error in Name::Name(): first name parameter must not be blank.
//// Exception caught within main().