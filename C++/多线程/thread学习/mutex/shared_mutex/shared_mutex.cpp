/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/10/1 20:32:05
 */
#include <iostream>
#include <chrono>
#include <thread>
#include <shared_mutex>
#include <vector>

#define IN 0
#define OUT 0
#define TEST_CASE(name) static void name()

int g_num = 0;  // protected by g_num_mutex
std::shared_mutex g_num_mutex;  //初始化时，是unlock()状态

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

//constexpr shared_mutex() noexcept;   (1)	(since C++11)
TEST_CASE(test_ctor)
{
	//只有这一种构造函数
	std::shared_mutex num_mutex;  //初始状态是unlock
	num_mutex.lock();
	//num_mutex.lock();
}

//测试lock() unlock()
//void lock();    //Locks the shared_mutex.
//void unlock();  //Unlocks the shared_mutex.
TEST_CASE(test_lock_and_unlock)
{
	std::thread t1(slow_increment, 0);
	std::thread t2(slow_increment, 1);
	t1.join();
	t2.join();
}


TEST_CASE(test_try_lock)
{
	
}

TEST_CASE(test_member_function)
{
	test_ctor();
	for(int i = 0; i < 10; ++i)
	{
		test_lock_and_unlock();
		std::cout << "---------------------\n\n";
		g_num = 0;
	}
	//test_try_lock();
}

class ThreadSafeCounter
{
public:
	ThreadSafeCounter() = default;

	// Multiple threads/readers can read the counter's value at the same time.
	unsigned int get() const
	{
		std::shared_lock<std::shared_mutex> lock(mutex_);
		return value_;
	}

	// Only one thread/writer can increment/write the counter's value.
	void increment()
	{
		std::unique_lock<std::shared_mutex> lock(mutex_);
		value_++;
	}

	// Only one thread/writer can reset/write the counter's value.
	void reset()
	{
		std::unique_lock<std::shared_mutex> lock(mutex_);
		value_ = 0;
	}

private:
	mutable std::shared_mutex mutex_;
	unsigned int value_ = 0;
};



//一些综合测试
TEST_CASE(test_other)
{
	ThreadSafeCounter counter;

	auto increment_and_print = [&counter]() {
		for(int i = 0; i < 3; i++)
		{
			counter.increment();
			std::cout << std::this_thread::get_id() << ' ' << counter.get() << '\n';

			// Note: Writing to std::cout actually needs to be synchronized as well
			// by another std::mutex. This has been omitted to keep the example small.
		}
	};

	std::thread thread1(increment_and_print);
	std::thread thread2(increment_and_print);

	thread1.join();  //join()之后，线程就消失
	thread2.join();
}
// Explanation: The output below was generated on a single-core machine. When
// thread1 starts, it enters the loop for the first time and calls increment()
// followed by get(). However, before it can print the returned value to
// std::cout, the scheduler puts thread1 to sleep and wakes up thread2, which
// obviously has time enough to run all three loop iterations at once. Back to
// thread1, still in the first loop iteration, it finally prints its local copy
// of the counter's value, which is 1, to std::cout and then runs the remaining
// two loop iterations. On a multi-core maschine, none of the threads is put to
// sleep and the output is more likely to be in ascending order.


TEST_CASE(test)
{
	//test_member_function();
	test_other();
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