/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               �����ߣ� Josan
 *             ����ʱ�䣺 2017/9/30 20:44:42
 */
#include <iostream> // std::cout
#include <thread>   // std::thread

void thread_hello()
{
	std::cout << "hello thread" << std::endl;
}

int main(int argc, const char *argv[])
{
	std::thread t(thread_hello);
	//t.join();

	return EXIT_SUCCESS;
}  /* ----------  end of function main  ---------- */