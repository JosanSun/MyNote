#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>


#define TEST_CASE(name)  static void name()

std::condition_variable cv;
std::mutex cv_m;
int i = 0;
bool done = false;

void waits()
{
	std::unique_lock<std::mutex> lk(cv_m);
	std::cout << "Waiting... \n";
	//cv执行wait()之后，其他线程就可以获得mutex
	cv.wait(lk, [] {return i == 1; });
	std::cout << "...finished waiting. i == 1\n";
	done = true;
	////进程等待10秒  测试用
	//std::this_thread::sleep_for(std::chrono::seconds(10));
}

void signals()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Notifying falsely...\n";
	cv.notify_one(); // waiting thread is notified with i == 0.
					 // cv.wait wakes up, checks i, and goes back to waiting

	//虽然cv.wait()里面拥有锁，但是执行wait之后，其状态已经变为等待状态，不影响锁的使用。
	std::unique_lock<std::mutex> lk(cv_m);
	i = 1;
	while(!done)
	{
		std::cout << "Notifying true change...\n";
		//注意这里必须先解锁
		lk.unlock();
		cv.notify_one(); // waiting thread is notified with i == 1, cv.wait returns
		std::this_thread::sleep_for(std::chrono::seconds(1));
		lk.lock();
	}
}

void signals1()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	{
		std::lock_guard<std::mutex> lk(cv_m);
		std::cerr << "Notifying...\n";
	}
	cv.notify_all();

	std::this_thread::sleep_for(std::chrono::seconds(1));

	{
		std::lock_guard<std::mutex> lk(cv_m);
		i = 1;
		std::cerr << "Notifying again...\n";
	}
	cv.notify_one();
}

TEST_CASE(test_notify_one)
{
	std::thread t1(waits), t2(signals);
	t1.join();
	t2.join();
}

TEST_CASE(test_notify_all)
{
	std::thread t1(waits), t2(waits), t3(waits), t4(signals1);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}

TEST_CASE(test_member_function)
{
	//test_notify_one();
	test_notify_all();
}


TEST_CASE(test)
{
	test_member_function();
}

int main()
{
	test();

	return 0;
}