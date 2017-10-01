/* thread() noexcept;     (1)	(since C++11)
 * thread(thread&& other) noexcept;   (2)	 (since C++11)
 * template< class Function, class... Args >
   explicit thread(Function&& f, Args&&... args);    (3)	(since C++11)
 * thread(const thread&) = delete;  (4)	(since C++11)
 * 
 */

#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#include <mutex>
#include <algorithm>

#define TEST_CASE(name) static void name()

void f1(int n)
{
	for(int i = 0; i < 5; ++i)
	{
		std::cout << "Thread 1 executing\n";
		++n;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void f2(int& n)
{
	for(int i = 0; i < 5; ++i)
	{
		n = 6;
		std::cout << "Thread 2 executing\n";
		++n;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

//测试thread的构造函数
//Constructs new thread object.
TEST_CASE(test_ctor)
{
	{
		int n = 0;
		std::thread t1; // t1 is not a thread    pid == 0
		std::thread t2(f1, n + 1); // pass by value
		std::thread t3(f2, std::ref(n)); // pass by reference
		//std::thread t3_err(f2, n);  //error
		std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
		

		//test max threads
		std::thread t5(f1, n + 1);
		std::thread t6(f1, n + 1);
		std::thread t7(f1, n + 1);
		std::thread t8(f1, n + 1);

		//t3_err.join();
		t5.join();
		t6.join();
		t7.join();
		t8.join();
		t2.join();
		t4.join();
		std::cout << "Final value of n is " << n << '\n';   //这个最终的n必然是5
	}

	//int cnt7 = 0;
	//int cnt8 = 0;
	//while(1)
	//{
	//	int n = 0;
	//	std::thread t1; // t1 is not a thread
	//	std::thread t2(f2, std::ref(n)); // pass by value
	//	std::thread t3(f2, std::ref(n)); // pass by reference
	//	std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
	//	t2.join();
	//	t4.join();
	//
	//	if(cnt7 > 100 || cnt8 > 100)
	//	{
	//		break;
	//	}
	//	if(7 == n)
	//	{
	//		++cnt7;
	//	}
	//	else if(8 == n)
	//	{
	//		++cnt8;
	//	}
	//	else
	//	{
	//		break;
	//	}
	//	//std::cout << "Final value of n is " << n << '\n';   //这个最终的n必然是5
	//}
	//std::cout << "n!=7,8    " << cnt7 << "    " << cnt8 << std::endl;  
	////cnt7  1001   cnt8  826
	////cnt7  101    cnt8  5

	//改测试详细解析，见MostVexingParse.cpp  //http://en.wikipedia.org/wiki/Most_vexing_parse
	{
		class background_task
		{
		public:
			void operator()() const
			{
				//do_something();
			}
		};

		background_task f;
		std::thread my_thread1(f);  //ok

		////这是一个函数声明，没有创建一个线程
		//std::thread my_thread(background_task());  //歧义


		//以下1, 2是正确做法
		std::thread my_thread((background_task()));  // 1  OK
		//std::thread my_thread{background_task()};    // 2  OK

		my_thread.join();
		my_thread1.join();
	}
}

void foo()
{
	// simulate expensive operation
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void bar()
{
	// simulate expensive operation
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

//直到确定调用者完成它的执行，才阻塞调用join()者的线程。
//waits for a thread to finish its execution  前提条件是joinable() == true; 否则触发异常
// Blocks the current thread until the thread identified by *this finishes its execution.
TEST_CASE(test_join)
{
	std::cout << "starting first helper...\n";
	std::thread helper1(foo);

	std::cout << "starting second helper...\n";
	std::thread helper2(bar);

	std::cout << "waiting for helpers to finish..." << std::endl;
	helper1.join();  //多join会出错，少了join也会出错。
	//helper1.join();  //error
	helper2.join();

	std::cout << "done!\n";
}

//Checks if the thread object identifies an active thread of execution.
TEST_CASE(test_joinable)
{
	//默认构造的线程是不可结合的 not joinable
	std::thread t;
	std::cout << "before starting, joinable: " << t.joinable() << '\n';  //false

	t = std::thread(foo);
	std::cout << "after starting, joinable: " << t.joinable() << '\n';  //true
	t = std::thread(foo);
	t.join();
	std::cout << "after joining, joinable: " << t.joinable() << '\n';  //false
}

/* Destroys the thread object.
 * If *this has an associated thread (joinable() == true), std::terminate() is called.
 */
TEST_CASE(test_dtor)
{
	//默认构造的线程是不可结合的 not joinable
	
	std::thread t;
	std::cout.setf(std::ios_base::boolalpha);
	std::cout << "before starting, joinable: " << t.joinable() << '\n';  //false

	t.~thread();  //ok

	t = std::thread(foo);
	std::cout << "after starting, joinable: " << t.joinable() << '\n';  //true

	//t.~thread();  //error  发生中断

	t.join();
	std::cout << "after joining, joinable: " << t.joinable() << '\n';  //false
	t.~thread();  //ok
}

//测试移动赋值成员函数     thread& operator=( thread&& other ) noexcept;  moves the thread object 
//赋值之前，必须保证调用者的状态是 joinable() == false;
/* If *this still has an associated running thread (i.e. joinable() == true), call std::terminate(). Otherwise, assigns the state of other to *this and sets other to a default constructed state.

 * After this call, this->get_id() is equal to the value of other.get_id() prior to the call, and other no longer represents a thread of execution.
 */
TEST_CASE(test_oper)
{
	//默认构造的线程是不可结合的 not joinable
	std::thread t;
	std::cout << "before starting, joinable: " << t.joinable() << '\n';  //false
	//这里调用了赋值表达式，只能移动赋值。
	//thread& operator=( thread&& other ) noexcept;
	t = std::thread(foo);  //ok
	//t = std::thread(bar);  //error
	t.join();
}

//std::thread::id get_id() const noexcept;
//Returns a value of std::thread::id identifying the thread associated with *this.
TEST_CASE(test_get_id)
{
	std::thread t1(foo);
	std::thread::id t1_id = t1.get_id();

	std::thread t2(foo);
	std::thread::id t2_id = t2.get_id();

	std::cout << "t1's id: " << t1_id << '\n';  //19896
	std::cout << "t2's id: " << t2_id << '\n';  //18696

	t1.join();
	t2.join();
}

void independentThread()
{
	std::cout << "Starting concurrent thread.\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "Exiting concurrent thread.\n";
}

void threadCaller()
{
	std::cout << "Starting thread caller.\n";
	std::thread t(independentThread);
	t.detach();  //分离
	
	std::cout << "after detaching, joinable: " << t.joinable() << '\n';  //false

	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Exiting thread caller.\n";
}

//permits the thread to execute independently from the thread handle 
TEST_CASE(test_detach)
{
	threadCaller();
	//如果没有这个等待，可能看不见“Exiting concurrent thread.”
	std::this_thread::sleep_for(std::chrono::seconds(5));

}



TEST_CASE(test_native_handler)
{
	//none  还不懂这个成员函数
}

//static unsigned hardware_concurrency() noexcept;
//Returns the number of concurrent threads supported by the implementation. The value should be considered only a hint.
TEST_CASE(test_hardware_concurrency)
{
	//NOTE: 这不是代表最多只能创建4个线程
	unsigned int n = std::thread::hardware_concurrency();  //4
	std::cout << n << " concurrent threads are supported.\n";
}

TEST_CASE(test_swap)
{
	//正常测试
	{
		std::thread t1(foo);
		std::thread t2(bar);

		std::cout << "thread 1 id: " << t1.get_id() << std::endl;
		std::cout << "thread 2 id: " << t2.get_id() << std::endl;

		t1.swap(t2);

		std::cout << "after t1.swap(t2):" << std::endl;
		std::cout << "thread 1 id: " << t1.get_id() << std::endl;
		std::cout << "thread 2 id: " << t2.get_id() << std::endl;

		t1.join();
		t2.join();
	}
	{
		std::thread t1;
		std::thread t2(bar);

		std::cout << "thread 1 id: " << t1.get_id() << std::endl;
		std::cout << "thread 2 id: " << t2.get_id() << std::endl;

		//t1.swap(t2);
		t2.swap(t1);  //swap的调用与是否joinable无关

		std::cout << "after t1.swap(t2):" << std::endl;
		std::cout << "thread 1 id: " << t1.get_id() << std::endl;
		std::cout << "thread 2 id: " << t2.get_id() << std::endl;

		t1.join();  
		//t2.join();  //error   发生system_error异常
	}
}

//测试成员函数
TEST_CASE(test_member_function)
{
	test_ctor();
	//test_join();
	//test_joinable();
	//test_dtor();
	//test_oper();
	//test_get_id();
	//test_detach();
	//test_hardware_concurrency();
	test_swap();
}

//测试非成员函数swap
//void swap( thread& other ) noexcept;
TEST_CASE(test_non_member_function)
{
	//正常测试
	{
		std::thread t1(foo);
		std::thread t2(bar);

		std::cout << "thread 1 id: " << t1.get_id() << std::endl;
		std::cout << "thread 2 id: " << t2.get_id() << std::endl;

		swap(t1, t2);

		std::cout << "after t1.swap(t2):" << std::endl;
		std::cout << "thread 1 id: " << t1.get_id() << std::endl;
		std::cout << "thread 2 id: " << t2.get_id() << std::endl;

		t1.join();
		t2.join();
	}
	{
		std::thread t1;  
		std::thread t2(bar);

		std::cout << "thread 1 id: " << t1.get_id() << std::endl;
		std::cout << "thread 2 id: " << t2.get_id() << std::endl;

		//swap(t1, t2);
		swap(t2, t1);  //swap的调用与是否joinable无关

		std::cout << "after t1.swap(t2):" << std::endl;
		std::cout << "thread 1 id: " << t1.get_id() << std::endl;
		std::cout << "thread 2 id: " << t2.get_id() << std::endl;

		t1.join();
		//t2.join();  //error   发生system_error异常
	}
}


//thread的其他测试，作为扩展
struct func
{
	int& i;
	func(int& i_) : i(i_)
	{
	}
	void operator() ()
	{
		for(unsigned j = 0; j < 1000000; ++j)
		{
			++i;
			//do_something(i);           // 1. 潜在访问隐患：悬空引用
		}
	}
};

class thread_guard
{
	std::thread& t;
public:
	explicit thread_guard(std::thread& t_) :
		t(t_)
	{
	}
	~thread_guard()
	{
		if(t.joinable()) // 1
		{
			t.join();      // 2
		}
	}
	thread_guard(thread_guard const&) = delete;   // 3
	thread_guard& operator=(thread_guard const&) = delete;
};

TEST_CASE(test_other_func_throw)
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	try
	{
		new int[1000];
		//do_something_in_current_thread();
	}
	catch(...)
	{
		t.join();  // 1
		throw;
	}
	t.join();  // 2
}

class scoped_thread
{
	std::thread t;
public:
	explicit scoped_thread(std::thread t_) :                 // 1
		t(std::move(t_))
	{
		if(!t.joinable())                                     // 2
			throw std::logic_error("No thread");
	}
	~scoped_thread()
	{
		t.join();                                            // 3
	}
	scoped_thread(scoped_thread const&) = delete;
	scoped_thread& operator=(scoped_thread const&) = delete;
};

TEST_CASE(test_other_func_RAII)
{
	//注意区分thread_guard和scoped_thread的初始化方式

	{
		int some_local_state = 0;
		func my_func(some_local_state);
		std::thread t(my_func);
		thread_guard g(t);  //不需要手动的join()
		//thread_guard g1((std::thread{my_func}));   //error  临时无法正确赋值
							//do_something_in_current_thread();
	}

	{
		int some_local_state;
		scoped_thread t(std::thread(func(some_local_state)));    // 4
		//do_something_in_current_thread();
	}
}

TEST_CASE(test_other)
{
	test_other_func_throw();
	test_other_func_RAII();
}

TEST_CASE(test)
{
	//test_member_function();
	//test_non_member_function();
	test_other();
}

int main()
{
	test();
	return 0;
}


