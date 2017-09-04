#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <vector>
#include <cassert>
#include <iostream>
using std::cerr;
using std::endl;
using std::vector;
typedef int Key;

//NOTE:�ѵ����Ԫ����pq[1]���棬���ڶԱ�ʾ�ķ��㿼��  ����������������ȶ���
class maxHeap
{
public:
	maxHeap():sz(0){ }
	maxHeap(int maxN) :sz(0)
	{
		assert(0 <= maxN);
		pq.resize(maxN + 1);
	}
	maxHeap(vector<Key>& a);
	void insert(Key v);
	Key max()const
	{
		return pq[1];
	}
	Key delMax();
	bool isEmpty()const
	{
		return 0 == sz;
	}
	int size()const
	{
		return sz;
	}
	
private:
	//����pq[i]��pq[j]
	void exch(int i, int j)
	{
		Key t = pq[i];
		pq[i] = pq[j];
		pq[j] = t;
	}
	bool less(int i, int j)
	{
		return pq[i] < pq[j];
	}
	void swim(int k);
	void sink(int k);
	//pq[] : binary heap using 1-based indexing
	vector<Key> pq;
	int sz;
};

typedef int Index;
//NOTE:�ѵ����Ԫ����pq[1]���棬���ڶԱ�ʾ�ķ��㿼��  ����������������ȶ���
class indexMaxHeap
{
public:
	indexMaxHeap():sz(0)
	{
	}
	indexMaxHeap(int maxN):sz(0)
	{
		assert(0 <= maxN);
		pq.resize(maxN + 1);
		idx2Priority.resize(maxN + 1, -1);
		element.resize(maxN + 1);
	}
	int maxIndex()const
	{
		return pq[1];
	}
	Key maxKey()const
	{
		return element[pq[1]];
	}
	bool isEmpty()const
	{
		return 0 == sz;
	}
	Key keyOf(int i)const
	{
		return element[i];
	}
	//���ص������ȶ��еĴ�С
	int size()const
	{
		return sz;
	}
	bool contains(int i)
	{
		return -1 != idx2Priority[i];
	}
	//�������i������λelement[i]
	void insert(int i, Key key);
	void changeKey(int i, Key key);
	void increaseKey(int i, Key key);
	void decreaseKey(int i, Key key);
	int delMax();
	void deleteElem(int i);
private:
	/***************************************************************************
	* General helper functions.
	***************************************************************************/
	//����pq[i]��pq[j]
	void exch(int i, int j)
	{
		int tmp = pq[i];
		pq[i] = pq[j];
		pq[j] = tmp;
		idx2Priority[pq[i]] = i;
		idx2Priority[pq[j]] = j;
	}
	bool less(int i, int j)
	{
		return element[pq[i]] < element[pq[j]];
	}
	void swim(int k);
	void sink(int k);
	vector<Index> pq;
	// inverse of pq - idx2Priority[pq[i]] = pq[idx2Priority[i]] = i
	vector<Index> idx2Priority;
	vector<Key> element;
	int sz;
};

#endif