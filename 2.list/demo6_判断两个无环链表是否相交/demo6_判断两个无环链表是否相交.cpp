#include "../List/List.h"
#include <set>

/*
	【题目】 
			给定两个无环的单链表，这两个链表可能相交，也可能不相交。
			请实现一个函数如果两个链表相交请返回相交的第一个节点；如果不相交，返回 NULL。

			要求：如果链表1的长度为N，链表2的长度为M，时间复杂度达到 O(N+M)，额外
			空间复杂度达到O(1)
*/

/*

	解决：
		2,怎么判断两个无环单链表相交的第一个节点
			两个链表相交以后，因为只有一个next指针，所以从相交的第一个节点开始，后面都是相同的
			如果两条链表是有序的，用 demo1_打印两个有序链表的公共部分 中的方法就可以找到，但是现在链表不一样有序
			(1),使用set，先遍历a链表，把a的节点都放到set中，再遍历b链表，依次查找set中是否已经存在
				第一个已存在的就是第一个相交的节点
			(2),不使用额外的空间，遍历两条链表，分别记录两条链表的尾节点和链表的长度
				如果两个尾节点不相等，说明两条链表肯定不相交，如果尾节点相等，判断两条链表哪个更长
				长的那条链表的长度减去短的那条链表的长度，差值为len,让长的那条链表，从头开始先走len个
				节点，然后长的链表和短的链表一起走，这两条链表肯定会走到交点

*/

//使用 set 检测两个无环链表的相交
Node *WuHuanUseSet(List *list1, List *list2)
{
	if (list1 == NULL || list2 == NULL)
		return NULL;
	set<Node *> setNode;

	//先遍历list1，将list1的节点都放到set中
	Node *curr = list1->head;
	while (curr)
	{
		setNode.insert(curr);
		curr = curr->next;
	}

	//再遍历list2
	curr = list2->head;
	while (curr)
	{
		//查找set中是否已经存在该节点，如果已经存在，该节点就是入环口
		if (setNode.find(curr) != setNode.end())
		{
			printf("xiangjiao, vealue: %d\n", curr->value);
			return curr;
		}
		curr = curr->next;
	}
	printf("not xiangjiao\n");
	return NULL;
}

//空间复杂度O(1)检测两个无环链表是否相交
Node *WuHuanNotUseSet(List *list1, List *list2)
{
	if (list1 == NULL || list2 == NULL)
		return NULL;

	//遍历两条链表，保存链表的长度和最后一个节点
	Node *endNode1 = NULL;
	Node *endNode2 = NULL;
	int len1 = 0;
	int len2 = 0;

	Node *curr = list1->head;
	while (curr)
	{
		len1++;
		endNode1 = curr;
		curr = curr->next;
	}

	curr = list2->head;
	while (curr)
	{
		len2++;
		endNode2 = curr;
		curr = curr->next;
	}

	//如果尾节点不一样，说明一定不相交
	if (endNode1 != endNode2)
	{
		printf("not xiangjiao\n");
		return NULL;
	}

	//用两个节点分别指向较长的链表和较短的链表
	Node *longNode = len1 >= len2 ? list1->head : list2->head;
	Node *shortNode = len1 < len2 ? list1->head : list2->head;
	//找到两条链表长度的差值
	int lenCha = len1 >= len2 ? len1 - len2 : len2 - len1;

	//让较长的链表先走 lenCha 步
	while (lenCha--)
		longNode = longNode->next;

	//两个链表一起走，当相等时，进入入环口
	while (longNode != NULL && shortNode != NULL)
	{
		if (longNode == shortNode)
		{
			printf("xiangjiao, vealue: %d\n", longNode->value);
			return longNode;
		}
		longNode = longNode->next;
		shortNode = shortNode->next;
	}

	printf("not xiangjiao\n");
	return NULL;
}

int main()
{
	List list1;

	list1.AddNodeTail(1);
	list1.AddNodeTail(2);
	list1.AddNodeTail(3);
	list1.AddNodeTail(4);
	list1.AddNodeTail(5);
	list1.AddNodeTail(6);
	list1.AddNodeTail(7);
	list1.AddNodeTail(8);
	list1.Printf();

	List list2;
	list2.AddNodeTail(9);
	list2.AddNodeTail(10);
	list2.AddNodeTail(11);

	//让两个链表，在链表1的第3个节点相交
	list2.tail->next = list1.head->next->next;

	list2.Printf();

	WuHuanUseSet(&list1, &list2);
	WuHuanNotUseSet(&list1, &list2);
}
