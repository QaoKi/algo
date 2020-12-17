#include "../List/List.h"
#include <set>

/*
	【题目】 
			给定一个单链表，判断该链表是否有环。
			如果链表有环，返回入环的第一个节点，无环返回Null

			进阶：空间复杂度 O(1)
*/

/*
	解决：
		1.怎么判断单链表有没有环			
			因为链表中只含有next这一条指针，所以每个节点只指向一个节点，
			有环的情况，是最后一个节点不指向null，而指向了链表中的某一个节点导致的
			(1),使用哈希set,哈希set和哈希map的区别是哈希set不含有value，只含有key，set是集合，map是映射
				遍历链表，将每个结点放到set中，遍历的时候，查找ste中是否已经有该结点，
				如果有，说明这个节点就是环的入口，如果没有，说明没有环
			(2),不使用额外的空间，使用快慢指针，快指针一次走两步，慢指针一次走一步，
				快指针或慢指针为空，说明无环，如果有环，那么快指针和慢指针一定会在环上相遇，
				相遇以后让快指针回到第一个节点，一次走一步，下一次和慢指针相交的地方就是入环口
				需要注意的是，这种方法是从链表的第一个节点（有数据的节点）开始遍历的。如果链表有头节点（没有数据），需要
				省略头节点，从第一个节点开始进行快慢指针的遍历
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

//使用快慢指针
Node *checkLoopQuickSlowPointer(List *list)
{
	if (!list)
		return NULL;

	Node *quick = list->head;
	Node *slow = list->head;
	//如果有环，指向环入口的结点
	Node *ret = NULL;

	//快指针走两步，慢指针走一步
	while (quick != NULL && quick->next != NULL)
	{
		//先让指针移动，不然在第一个节点处两个指针就相等了
		quick = quick->next->next;
		slow = slow->next;
		//快指针和慢指针相遇，说明有环
		if (quick == slow)
		{
			ret = quick;
			break;
		}
	}

	if (ret != NULL)
	{
		//说明有环让快指针回到第一个节点，一次一步的走，下次再和慢指针相遇时就是入环口
		quick = list->head;

		while (quick != NULL && slow != NULL)
		{
			if (quick == slow)
			{
				printf("have loop,node: %d\n", quick->value);
				return quick;
			}
			quick = quick->next;
			slow = slow->next;
		}
	}

	printf("not have loop\n");
	return NULL;
}

int main()
{
	List list;

	list.AddNodeTail(1);
	list.AddNodeTail(2);
	list.AddNodeTail(3);
	list.AddNodeTail(4);
	list.AddNodeTail(5);
	list.AddNodeTail(6);
	list.AddNodeTail(7);
	list.AddNodeTail(8);
	list.Printf();

	//给链表加上环
	//最后一个节点指向第3个节点，第3个节点是环的入口
	list.tail->next = list.head->next->next;

	checkLoopUseSet(&list);
	checkLoopQuickSlowPointer(&list);
	return 0;
}
