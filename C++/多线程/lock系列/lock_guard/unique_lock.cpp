/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               �����ߣ� Josan
 *             ����ʱ�䣺 2017/10/1 22:10:35
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
	////�����Զ����������Ϊ�����������ı�_Owns��ֵ����˻���ö��unlock()
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
		//���Խ���  //���ǲ����Զ��ν���
		lock.unlock();
		//lock.unlock();
		
		// don't hold the lock while we simulate an expensive operation
		std::this_thread::sleep_for(std::chrono::seconds(2));  //��Ϣ2��
		////���Բ���������Ӱ�����������ͷ�
		//����, ���ܶ��μ���
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
	if(lock)  //ת��������תΪtrue
	{
		std::cout << "lock can be translated to boolean: true\n";
	}
	else
	{
		std::cout << "lock can be translated to boolean: false\n";
	}
	std::mutex* m_ptr = lock.release();  

	std::cout << "lock owns lock? " << lock.owns_lock() << std::endl;  //false

	if(lock)  //ת��������תΪfalse
	{
		std::cout << "lock can be translated to boolean: true\n";
	}
	else
	{
		std::cout << "lock can be translated to boolean: false\n";
	}

	m_ptr->unlock(); 
	//���û��m_ptr->unlock();�������ᱨ��
	//ע�ⲻ��lock���������������쳣
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