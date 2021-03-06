/*
* ---------------------------------------------------
*  Copyright (c) 2017 josan All rights reserved.
* ---------------------------------------------------
*
*               创建者： Josan
*             创建时间： 2017/10/1 0:12:36
*/
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>

#define IN 0
#define OUT 1
#define TEST_CASE(name) static void name()

int g_num = 0;  // protected by g_num_mutex
std::mutex g_num_mutex;  //初始化时，是unlock()状态

void slow_increment(int id)
{
	for(int i = 0; i < 3; ++i)
	{
		//不能二次上锁
		//g_num_mutex.lock();  //死锁的话，会触发中断。  lock之前，必须确保锁是unlock()
		g_num_mutex.lock();
		g_num = g_num + 1;
		std::cout << id << " => " << g_num << '\n';
		g_num_mutex.unlock();
		//g_num_mutex.unlock();  //不能两次解锁
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

//constexpr mutex() noexcept;   (1)	(since C++11)
TEST_CASE(test_ctor)
{
	//只有这一种构造函数
	std::mutex num_mutex;  //初始状态是unlock
	num_mutex.lock();
	//num_mutex.lock();  //UB   无法连续两次lock().  但是正常的做法应该是进入死锁（死循环）
}

//测试lock() unlock()
//void lock();    //Locks the mutex.
//void unlock();  //Unlocks the mutex.
TEST_CASE(test_lock_and_unlock)
{
	std::thread t1(slow_increment, 0);
	std::thread t2(slow_increment, 1);
	t1.join();
	t2.join();
}

std::chrono::milliseconds interval(100);

std::mutex mutex;
int job_shared = 0; // both threads can modify 'job_shared',
					// mutex will protect this variable

int job_exclusive = 0; // only one thread can modify 'job_exclusive'
					   // no protection needed

// this thread can modify both 'job_shared' and 'job_exclusive'
void job_1()
{
	//mutex.lock();
	std::this_thread::sleep_for(interval); // let 'job_2' take a lock

	while(true)
	{
		// try to lock mutex to modify 'job_shared'
		if(mutex.try_lock())
		{
			std::cout << "job shared (" << job_shared << ")\n";
			mutex.unlock();
			return;
		}
		else
		{
			// can't get lock to modify 'job_shared'
			// but there is some other work to do
			++job_exclusive;
			std::cout << "job exclusive (" << job_exclusive << ")\n";
			std::this_thread::sleep_for(interval);
		}
	}
}

// this thread can modify only 'job_shared'
void job_2()
{
	//std::this_thread::sleep_for(interval); // let 'job_1' run first
	mutex.lock();
	std::this_thread::sleep_for(5 * interval);
	++job_shared;
	mutex.unlock();
}

volatile long long int  counter(0); // non-atomic counter
std::mutex mtx;           // locks access to counter

void attempt_10k_increases(int n)
{
	for(int i = 0; i < n; ++i)
	{
		if(mtx.try_lock())
		{   // only increase if currently not locked:
			++counter;
			mtx.unlock();
		}
	}
}

//bool try_lock();
//try_lock  如果返回true的话，那么相当于这个线程获得了另一个线程释放的锁。注意执行了lock
//如果这个线程，已经拥有锁，或者，其他线程拥有锁，则返回false
TEST_CASE(test_try_lock)
{
	//{
	//	std::thread thread_1(job_1);
	//	std::thread thread_2(job_2);

	//	thread_1.join();
	//	thread_2.join();
	//}
	std::vector<long long int> ivec{10, 100, 500, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
	auto it = ivec.begin();
	for(int j = 1; j <= 10; ++j)
	{
		clock_t t_st, t_ed;
		t_st = clock();
		std::thread threads[10];
		for(int i = 0; i < 10; ++i)
			threads[i] = std::thread(attempt_10k_increases, *it);	
		for(auto& th : threads) th.join();
		std::cout << counter << " successful increases of the counter.\n";
		std::cout << "Total possible add times is " << *it * 10 << std::endl;
		std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
		std::cout << "Valid sum percentage is " << 1.0*counter / (*it * 10) << std::endl;
		t_ed = clock();
		std::cout << "The time of calculation is " << t_ed - t_st << " ms." << std::endl;
		std::cout << "-------------------\n";
		counter = 0;
		++it;
	}
}

TEST_CASE(test_member_function)
{
	//test_ctor();
	/*for(int i = 0; i < 10; ++i)
	{
		test_lock_and_unlock();
		std::cout << "---------------------\n\n";
		g_num = 0;
	}*/
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
	freopen_s(&outFile, "out2.txt", "w", stdout);
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