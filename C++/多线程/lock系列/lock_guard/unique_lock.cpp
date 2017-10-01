/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/10/1 22:10:35
 */
#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>

#define TEST_CASE(name) static void name()

TEST_CASE(test_ctor)
{

}

/*	~unique_lock() _NOEXCEPT
		{	// clean up
		if (_Owns)
			_Pmtx->unlock();
		}
*/
TEST_CASE(test_dtor)
{
	std::mutex counter_mutex;
	std::unique_lock<std::mutex> lock(counter_mutex);
	////不可以多次析构，因为多次析构不会改变_Owns的值，因此会调用多次unlock()
	//lock.~unique_lock();
	//lock.~unique_lock();
}

/* 	void unlock()
		{	// try to unlock the mutex
		if (!_Pmtx || !_Owns)
			_THROW_NCEE(system_error,
				_STD make_error_code(errc::operation_not_permitted));

		_Pmtx->unlock();
		_Owns = false;
		}
 */
TEST_CASE(test_lock_and_unlock)
{
	int counter = 0;
	std::mutex counter_mutex;
	std::vector<std::thread> threads;

	auto worker_task = [&](int id) {
		std::unique_lock<std::mutex> lock(counter_mutex);
		++counter;
		std::cout << id << ", initial counter: " << counter << '\n';
		//可以解锁  //但是不可以二次解锁
		lock.unlock();
		//lock.unlock();
		
		// don't hold the lock while we simulate an expensive operation
		std::this_thread::sleep_for(std::chrono::seconds(2));  //休息2秒
		////可以不加锁，不影响锁的正常释放
		//但是, 不能二次加锁
		lock.lock();  
		//lock.lock();

		++counter;
		std::cout << id << ", final counter: " << counter << '\n';
	};

	for(int i = 0; i < 10; ++i) threads.emplace_back(worker_task, i);

	for(auto &thread : threads) thread.join();
}

TEST_CASE(test_observers)
{
	std::mutex counter_mutex;
	std::unique_lock<std::mutex> lock(counter_mutex);  
	std::cout << std::boolalpha;
	std::cout << "lock owns lock? " << lock.owns_lock() << std::endl;  //true
	if(lock)  //转换函数，转为true
	{
		std::cout << "lock can be translated to boolean: true\n";
	}
	else
	{
		std::cout << "lock can be translated to boolean: false\n";
	}
	std::mutex* m_ptr = lock.release();  

	std::cout << "lock owns lock? " << lock.owns_lock() << std::endl;  //false

	if(lock)  //转换函数，转为false
	{
		std::cout << "lock can be translated to boolean: true\n";
	}
	else
	{
		std::cout << "lock can be translated to boolean: false\n";
	}

	m_ptr->unlock(); 
	//如果没有m_ptr->unlock();这个程序会报错
	//注意不是lock析构函数引发的异常
}

TEST_CASE(test)
{
	test_ctor();
	test_dtor();
	//test_lock_and_unlock();
	test_observers();
}

int main()
{
	test();
	return 0;
}