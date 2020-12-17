#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

/*
	链表和数组对比
		数组支持随机访问，复杂度为O(1)，链表为O(n)，在插入和删除方面，数组为O(n)，
		对于链表，如果给定了结点，插入和删除复杂度为O(1)

		数组简单易用，在实现上使用的是连续的内存空间，可以借助 CPU 的缓存机制，预读数组中的数据，
		在加载某个下标的时候可以把以后的几个下标元素也加载到CPU缓存。所以访问效率更高。
		而链表在内存中并不是连续存储，所以对 CPU 缓存不友好，没办法有效预读
*/

/*
	双向链表和单向链表对比
		双向链表效率比单向链表更高，采用空间换时间的思想。
		比如删除操作，通常有两种情况
			1，删除结点中 “值等于某个给定值”的结点；
			2，给定一个指针，删除指针指向的结点。
		对于第一种情况，双向链表和单向链表都需要遍历找到该结点，时间复杂度都为O(n)，但对于第二种情况
		因为删除结点，需要知道前驱结点，而双向链表保存了前驱结点，所以复杂度为O(1)，但是单链表仍然需要遍历找到前驱结点
		插入同理
		对于一个有序链表，双向链表的按值查询的效率也要比单链表高一些。
		因为，我们可以记录上次查找的位置 p，每次查询时，根据要查找的值与 p 的大小关系，
		决定是往前还是往后查找，所以平均只需要查找一半的数据
*/

struct Node
{
	Node *prev;
	Node *next;
	Node *rand; //某些题目会用到，随机指向链表中的某个结点，或者null
	int value;

	Node()
	{
		prev = NULL;
		next = NULL;
		rand = NULL;
		value = 0;
	}
};

class List
{
public:
	List();
	~List();

	void AddNodeHead(int value);
	void AddNodeTail(int value);
	void DelNode(Node *node);
	Node *SearchKey(int key);
	void Printf();
	void Clear();

public:
	Node *head;
	Node *tail;
	int len;
};

#endif