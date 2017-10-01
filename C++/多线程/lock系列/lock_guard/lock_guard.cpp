/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/10/1 21:17:52
 */
#include <thread>
#include <mutex>
#include <iostream>

#define TEST_CASE(name) static void name()

int g_i = 0;
std::mutex g_i_mutex;  // protects g_i

void safe_increment()
{
	//lock_guard   不再需要显示的调用g_i_mutex.unlock()
	std::lock_guard<std::mutex> lock(g_i_mutex);
	++g_i;

	std::cout << std::this_thread::get_id() << ": " << g_i << '\n';

	// g_i_mutex is automatically released when lock
	// goes out of scope
}

std::mutex mtx;

void print_even(int x)
{
	if(x % 2 == 0) std::cout << x << " is even\n";
	else throw (std::logic_error("not even"));
}

void print_thread_id(int id)
{
	try
	{
		// using a local lock_guard to lock mtx guarantees unlocking on destruction / exception:
		std::lock_guard<std::mutex> lck(mtx);
		print_even(id);
	}
	catch(std::logic_error&)
	{
		std::cout << "[exception caught]\n";
	}
}

/*
explicit lock_guard(mutex_type& m);  (1)	(since C++11)
lock_guard(mutex_type& m, std::adopt_lock_t t);  (2)	(since C++11)
*/
TEST_CASE(test_ctor)
{
	//{
	//	std::cout << __func__ << ": " << g_i << '\n';

	//	std::thread t1(safe_increment);
	//	std::thread t2(safe_increment);

	//	t1.join();
	//	t2.join();

	//	std::cout << __func__ << ": " << g_i << '\n';
	//}
	/*
	Possible output:

	main: 0
	140641306900224: 1
	140641298507520: 2
	main: 2
	 */


	{
		std::thread threads[10];
		// spawn 10 threads:
		for(int i = 0; i < 10; ++i)
			threads[i] = std::thread(print_thread_id, i + 1);

		for(auto& th : threads) th.join();
	}
	/*
	Possible output (order of lines may vary, but they are never intermingled):
	[exception caught]
	2 is even
	[exception caught]
	4 is even
	[exception caught]
	6 is even
	[exception caught]
	8 is even
	[exception caught]
	10 is even
	*/
}


/*
~lock_guard() _NOEXCEPT
{	// unlock
_MyMutex.unlock();
}
*/
TEST_CASE(test_dtor)
{
	std::lock_guard<std::mutex> lck(mtx);
	//lck.~lock_guard();  //error  不能显示的调用, 否则会造成二次unlock;

	//std::lock_guard<std::mutex> lck1;  //不存在默认的构造函数
	std::lock_guard<> l;  //存在这样的特例，默认构造函数
	std::recursive_mutex mtx1;
	std::lock_guard<std::recursive_mutex> lck2(mtx1);
	//lck2.~lock_guard();  //error  不能显示的调用, 否则会造成二次unlock;
}

TEST_CASE(test)
{
	//test_ctor();
	test_dtor();
}


int main()
{
	test();

	return 0;
}