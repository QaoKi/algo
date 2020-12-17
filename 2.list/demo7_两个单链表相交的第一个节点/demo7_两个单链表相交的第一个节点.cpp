#include "../List/List.h"
#include <set>
/*
	【题目】 在本题中，单链表可能有环，也可能无环。
			给定两个单链表，这两个链表可能相交，也可能不相交。
			请实现一个函数如果两个链表相交请返回相交的第一个节点；如果不相交，返回 nil 即可。

			要求：如果链表1的长度为N，链表2的长度为M，时间复杂度达到 O(N+M)，额外
			空间复杂度达到O(1)
*/

/*
	思路：
			首先要检查两个链表是否有环，如果一个链表有环，一个链表无环，那么不可能相交
			如果两个链表都无环，那么进行两个无环链表的相交处理
			如果两个链表都有环，那么进行两个有环链表的相交处理

			所以这是三道题的集合，
			1.怎么判断单链表有没有环
			2.怎么判断两个无环单链表相交的第一个节点
			3，怎么判断两个有环单链表相交的第一个节点

	解决：
		3，怎么判断两个有环单链表相交的第一个节点
			一个链表有环，一个链表无环，不可能相交

			两个有环链表的情况有三种：
				1，两个链表不相交
				2，两个链表不到环上时就相交，这种情况下，他们共享着环，是一样的环，
					例如：
							  F
							  |		   J ←I
							  ↓	  	   ↓  ↑
						A->B->C->D->E->G->H
				3，两个链表在环上相交

								 K->F->J ←I
								  	   ↓  ↑
						A->B->C->D->E->G->H
			先判断出来是哪种情况：找到链表A的入环口a，链表B的入环口b，
						如果a == b，说明链表A和B有同一个环，是第2种情况
						如果a != b, 让A从入环口a开始，一直朝下走，如果重新走回到a都没碰到b，
									说明两个链表不相交，如果碰到了b，此时返回a和b都可以，因为这两个都是
									环的入口
			判断出是哪种情况以后：
				第1种情况，没有相交的点
				第3种情况，返回a和b都可以
				第2种情况，只知道这两条链表有同一个环，但是不知道是在哪相交的
					可以将环的入环口当做尾节点，两条链表分别从头到尾，就是两条无环的链表
					将问题改为求两条无环链表相交的第一个节点

*/
//使用 set 检测单链表是否有环
Node *checkLoopUseSet(List *list)
{
	if (!list)
		return NULL;
	set<Node *> setNode;
	Node *curr = list->head;
	while (curr)
	{
		if (setNode.find(curr) != setNode.end())
		{
			printf("have loop,node: %d\n", curr->value);
			return curr;
		}
		setNode.insert(curr);
		curr = curr->next;
	}
	printf("not have loop\n");
	return NULL;
}

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

//检测两个单链表是否相交
Node *CheckTwoList(List *list1, List *list2)
{
	if (list1 == NULL || list2 == NULL)
		return NULL;
	//先判断两个链表是否有环，如果有环，找到入环口
	Node *loopNode1 = checkLoopUseSet(list1);
	Node *loopNode2 = checkLoopUseSet(list2);
	if ((loopNode1 == NULL && loopNode2 != NULL) || (loopNode2 == NULL && loopNode1 != NULL))
	{
		printf("not xiangjiao\n");
		//一个链表有环，一个无环，肯定不相交
		return NULL;
	}
	else if (loopNode1 == NULL && loopNode2 == NULL)
		//两个链表都无环，转为求两个无环链表的相交点
		return WuHuanUseSet(list1, list2);

	//两个有环链表的相交
	if (loopNode1 != loopNode2)
	{
		//入环口不一样
		Node *curr = loopNode1->next;
		while (curr != loopNode1)
		{
			if (curr == loopNode2)
			{
				//相交，返回 loopNode1 和 loopNode2 都可以
				printf("xiangjiao, vealue: %d\n", curr->value);
				return curr;
			}

			curr = curr->next;
		}
	}
	else
	{
		//入环口一样，两个链表共用同一个环
		//把入环口当做尾节点，把问题变成两条无环链表查找相交的第一个节点
		//先让尾节点指向 NULL，把线和环分隔开，最后再还原
		Node *temp = loopNode1->next;
		loopNode1->next = NULL;

		Node *ret = WuHuanUseSet(list1, list2);
		loopNode1->next = temp;

		return ret;
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
	//在成环前打印，不然成环后打印会死循环
	list1.Printf();

	//形成环，尾结点指向第4个节点
	list1.tail->next = list1.head->next->next->next;

	List list2;
	list2.AddNodeTail(9);
	list2.AddNodeTail(10);
	list2.AddNodeTail(11);
	list2.AddNodeTail(12);
	list2.AddNodeTail(13);
	list2.AddNodeTail(14);
	list2.AddNodeTail(15);
	list2.Printf();

	//两个链表不相交
	//list2.tail->next = list2.head->next->next;

	//形成环，但是两个链表的入环口不一样
	//list2.tail->next = list1.head->next->next->next->next->next->next;

	//形成环，两个链表共用同一个环
	//list2.tail->next = list1.head->next;

	CheckTwoList(&list1, &list2);
}
