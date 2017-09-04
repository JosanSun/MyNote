#include "01PriorityQueue.h"

//------------------ maxHeap ---------------------------
maxHeap::maxHeap(vector<Key>& a)
{
	for(auto x : a)
	{
		insert(x);
	}
}

void maxHeap::swim(int k)
{
	while(1 < k&&less(k / 2, k))
	{
		exch(k / 2, k);
		k = k / 2;
	}
}

void maxHeap::sink(int k)
{
	while(2 * k <= sz)
	{
		int j = 2 * k;
		if(j < sz&&less(j, j + 1))
		{
			++j;
		}
		if(false == less(k, j))
		{
			break;
		}
		exch(k, j);
		k = j;
	}
}

void maxHeap::insert(Key v)
{
	++sz;
	if(sz >= static_cast<int>(pq.size()))
	{
		pq.resize(static_cast<int>(sz*1.5));
	}
	pq[sz] = v;
	swim(sz);
}

Key maxHeap::delMax()
{
	Key max = pq[1];
	exch(1, sz--);
	pq[sz + 1] = Key();
	sink(1);
	return max;
}

//---------------- indexMaxHeap ---------------------
void indexMaxHeap::insert(int i, Key key)
{
	if(contains(i))
	{
		cerr << "A wrong insertion!" << endl;
		exit(0);
	}
	++sz;
	if(sz >= static_cast<int>(pq.size()))
	{
		pq.resize(static_cast<int>(sz*1.5));
		idx2Priority.resize(static_cast<int>(sz*1.5));
		element.resize(static_cast<int>(sz*1.5));
	}
	pq[sz] = i;
	idx2Priority[i] = sz;
	element[i] = key;
	swim(sz);
}

void indexMaxHeap::changeKey(int i, Key key)
{
	element[i] = key;
	//可能需要上浮
	swim(idx2Priority[i]);
	//也可能需要下沉
	sink(idx2Priority[i]);
}

void indexMaxHeap::increaseKey(int i, Key key)
{
	if(element[i] >= key)
	{
		cerr << "A wrong increase!" << endl;
		exit(0);
	}
	element[i] = key;
	//需要上浮
	swim(idx2Priority[i]);
}

void indexMaxHeap::decreaseKey(int i, Key key)
{
	if(element[i] <= key)
	{
		cerr << "A wrong decrease!" << endl;
		exit(0);
	}
	element[i] = key;
	//需要下沉
	sink(idx2Priority[i]);
}

int indexMaxHeap::delMax()
{
	assert(0 < sz);
	int maxIdx = pq[1];
	exch(1, sz--);
	sink(1);
	//删除元素
	idx2Priority[maxIdx] = -1;
	element[maxIdx] = Key();
	//删除索引
	pq[sz + 1] = -1;
	return maxIdx;
}

void indexMaxHeap::deleteElem(int i)
{
	if(!contains(i))
	{
		cerr << "A wrong delete!" << endl;
		exit(0);
	}
	int idx = idx2Priority[i];
	exch(idx, sz--);
	swim(idx);
	sink(idx);
}

void indexMaxHeap::swim(int k)
{
	while(1 < k&&less(k / 2, k))
	{
		exch(k / 2, k);
		k = k / 2;
	}
}

void indexMaxHeap::sink(int k)
{
	while(2 * k <= sz)
	{
		int j = 2 * k;
		if(j < sz&&less(j, j + 1))
		{
			++j;
		}
		if(false == less(k, j))
		{
			break;
		}
		exch(k, j);
		k = j;
	}
}
