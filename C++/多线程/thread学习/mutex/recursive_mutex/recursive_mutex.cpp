/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               �����ߣ� Josan
 *             ����ʱ�䣺 2017/10/1 2:14:36
 */
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>

#define IN 0
#define OUT 0
#define TEST_CASE(name) static void name()



TEST_CASE(test_ctor)
{

}

int g_num = 0;  // protected by g_num_mutex
std::recursive_mutex g_num_mutex;

void slow_increment(int id)
{
	for(int i = 0; i < 3; ++i)
	{
		g_num_mutex.lock();  //1.���������ܶ�Σ������и����ֵ���ơ� 2.��������������ڽ������������������ж��쳣
		g_num_mutex.lock();
		++g_num;
		std::cout << id << " => " << g_num << '\n';
		g_num_mutex.unlock();
		g_num_mutex.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

//����lock() unlock()
//void lock();    //Locks the mutex.
//void unlock();  //Unlocks the mutex.
TEST_CASE(test_lock_and_unlock)
{
	std::thread t1(slow_increment, 0);
	std::thread t2(slow_increment, 1);
	t1.join();
	t2.join();
}
//Output:
/*
0 => 1
1 => 2
0 => 3
1 => 4
0 => 5
1 => 6
*/




//bool try_lock();
//try_lock  �������true�Ļ�����ô�൱������̻߳������һ���߳��ͷŵ�����ע��ִ����lock
//�������̣߳��Ѿ�ӵ���������ߣ������߳�ӵ�������򷵻�false
TEST_CASE(test_try_lock)
{
	//std::mutex test;  //ok
	std::recursive_mutex test;  //note:������Ҫ��������
	if(test.try_lock() == true)
	{
		std::cout << "lock acquired" << std::endl;
		test.unlock();	//now unlock the mutex    
	}
	else
	{
		std::cout << "lock not acquired" << std::endl;
	}

	test.lock();	//to lock it again
	if(test.try_lock())  //���֣� test.try_lock()  �����mutex����false������UB.  �����recursive_mutex�Ļ������Լ���������
	{  //true can be left out
		std::cout << "lock acquired" << std::endl;  //recursive_mutex
	}
	else
	{
		std::cout << "lock not acquired" << std::endl;  //mutex
	}
	test.unlock();
	test.unlock();
}

TEST_CASE(test_member_function)
{
	test_ctor();
	test_lock_and_unlock();
	test_try_lock();
}

TEST_CASE(test)
{
	test_member_function();
}


int main()
{
#if IN
	FILE* inFile;
	freopen_s(&inFile, "in.txt", "r", stdin);
#endif
#if OUT
	FILE* outFile;
	freopen_s(&outFile, "out1.txt", "w", stdout);
#endif
	//-------------start of program----------------

	test();

	//------------- end  of program----------------
#if IN
	fclose(inFile);
#endif
#if OUT
	fclose(outFile);
#endif
	return 0;
}