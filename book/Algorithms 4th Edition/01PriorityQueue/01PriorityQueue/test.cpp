/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/4 14:02:40
 */
#include <iostream>
#include <vector>
#include <string>
#include "01PriorityQueue.h"
using namespace std;
int main()
{
	//maxHeap mHeap(10);
	//mHeap.insert(12);
	//mHeap.insert(11);
	//mHeap.insert(123);
	//int res = mHeap.delMax();

	vector<int> ivec{41, 67, 34, 0, 69, 24, 78, 58, 62, 64};
	/*for(auto& x : ivec)
	{
		x = rand() % 100;
		cout << x << "   ";
	}*/
	indexMaxHeap idxHeap(10);
	
	for(int i = 0; i < 10; ++i)
	{
		idxHeap.insert(i, ivec[i]);
		if(7 == i)
		{
			idxHeap.changeKey(i, 120);
		}
		else if(i % 5 == 0)
		{
			idxHeap.increaseKey(i, ivec[i] + 10);
		}
		else if(i % 9 == 0)
		{
			idxHeap.decreaseKey(i, ivec[i] - 10);
		}
	}

	while(!idxHeap.isEmpty())
	{
		Key key = idxHeap.maxKey();
		int i = idxHeap.delMax();
		cout << i << ": " << key << endl;
	}

	return 0;
}