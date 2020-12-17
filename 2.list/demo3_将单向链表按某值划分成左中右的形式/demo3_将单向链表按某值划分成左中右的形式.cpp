#include "../List/List.h"
#include <queue>

/*
	将单向链表按某值划分成左边小、中间相等、右边大的形式
	【题目】 给定一个单向链表的头节点head，节点的值类型是整型，再给定一个
			整数num。实现一个调整链表的函数，将链表调整为左部分都是值小于num
			的节点，中间部分都是值等于num的节点，右部分都是值大于 num的节点。
			并且要求数据的稳定性：要求每部分里的节点从左 到右的顺序与原链表中节点的先后次序一致。
			例如：链表 9->0->4->5->1，num=3。调整后的链表是 0->1->9->4->5。
			左部分节点从左到右为0、1。在原链表中也 是先出现0，后出现1；
			中间部分在本例中为空，不再讨论；
			右部分节点从左到右为9、4、5。在原链表中也是先出现9，然后出现4，最后出现5。

		进阶： 额外空间复杂度为O(1),，时间复杂度O(N)
*/

/*
	思路：
		不考虑空间复杂度的情况：
			使用三个队列，遍历一遍链表，大于、小于、等于num的放进不同的队列中，最后再组合起来
		考虑空间复杂度：
			声明三个辅助指针变量small,equal,big，遍历链表，把小于num的节点，拆分出来放到small下面，
			等于num的节点，拆分出来放到equal下面，大于num的节点，拆分出来放到big下面
			类似于桶排序，把相应的节点放到相应的桶中，每个桶声明一个end指针，遍历完链表以后
			三个新链表直接首尾相连就完成了
			可以遍历两次，第一次找到第一个小于等于和大于的节点，让small,equal,big等于他们，然后
			small,equal,big就不动了，就指向小于等于大于的第一个节点，再遇到小于等于大于的，就让
			end节点去操作，也可以遍历一遍，比如遇到小于的值，每次要判断一下small是否为空，如果为空
			说明遇到的是链表中第一个小于的节点，要让small指向它

			注意，要记得断开每个结点原来的next指向，不然可能出现环结构
*/

void useQueue(List *list, int num)
{
	if (!list)
		return;

	queue<Node *> queueSmall;
	queue<Node *> queueEqual;
	queue<Node *> queueBig;

	Node *curr = list->head;
	//让链表头节点断开和之前第一个节点的连接
	list->head = NULL;
	while (curr)
	{
		Node *next = curr->next;
		//断开节点之间的连接，使节点独立出来
		curr->next = NULL;

		if (curr->value == num)
			queueEqual.push(curr);
		else if (curr->value > num)
			queueBig.push(curr);
		else
			queueSmall.push(curr);

		curr = next;
	}

	Node *end = NULL; //指向新链表的尾节点
	while (!queueSmall.empty())
	{
		Node *temp = queueSmall.front();
		if (list->head == NULL)
		{
			//更新一下头节点
			list->head = temp;
			end = temp;
		}
		else
		{
			end->next = temp;
			end = temp;
		}
		queueSmall.pop();
	}

	while (!queueEqual.empty())
	{
		Node *temp = queueEqual.front();

		if (list->head == NULL)
		{
			list->head = temp;
			end = temp;
		}
		else
		{
			end->next = temp;
			end = temp;
		}

		queueEqual.pop();
	}

	while (!queueBig.empty())
	{
		Node *temp = queueBig.front();

		if (list->head == NULL)
		{
			list->head = temp;
			end = temp;
		}
		else
		{
			end->next = temp;
			end = temp;
		}

		queueBig.pop();
	}
}

void useHelpPointer(List *list, int num)
{
	if (!list)
		return;
	Node *smallHead = NULL;
	Node *equalHead = NULL;
	Node *bigHead = NULL;

	Node *smallEnd = NULL;
	Node *equalEnd = NULL;
	Node *bigEnd = NULL;

	Node *curr = list->head;
	//让链表头节点断开和之前第一个节点的连接
	list->head = NULL;
	while (curr)
	{
		Node *next = curr->next;
		//断开节点之间的连接，使节点独立出来
		curr->next = NULL;

		if (curr->value < num)
		{
			if (smallHead == NULL)
			{
				smallHead = curr;
				smallEnd = curr;
			}
			else
			{
				smallEnd->next = curr;
				smallEnd = curr;
			}
		}
		else if (curr->value == num)
		{
			if (equalHead == NULL)
			{
				equalHead = curr;
				equalEnd = curr;
			}
			else
			{
				equalEnd->next = curr;
				equalEnd = curr;
			}
		}
		else if (curr->value > num)
		{
			if (bigHead == NULL)
			{
				bigHead = curr;
				bigEnd = curr;
			}
			else
			{
				bigEnd->next = curr;
				bigEnd = curr;
			}
		}

		curr = next;
	}

	//三条链表拆分完毕
	//找出新链表的头结点
	if (smallHead != NULL)
		list->head = smallHead;
	else if (equalHead != NULL)
		list->head = equalHead;
	else
		list->head = bigHead;

	//首尾相连。不用去判断哪个链表有值哪个没有，直接连接到一起就行
	if (smallEnd != NULL)
		smallEnd->next = equalHead;
	if (equalEnd != NULL)
		equalEnd->next = bigHead;
}

int main()
{
	List list;
	list.AddNodeTail(7);
	list.AddNodeTail(3);
	list.AddNodeTail(7);
	list.AddNodeTail(3);
	list.AddNodeTail(6);
	list.AddNodeTail(9);
	list.AddNodeTail(0);
	list.AddNodeTail(4);
	list.AddNodeTail(8);
	list.AddNodeTail(6);
	list.Printf();

	//useQueue(&list, 6);
	useHelpPointer(&list, 6);
	list.Printf();
	return 0;
}
