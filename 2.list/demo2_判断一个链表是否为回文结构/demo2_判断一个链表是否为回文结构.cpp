#include "../List/List.h"
#include <stack>

/*
	【题目】 给定一个链表的头节点head，请判断该链表是否为回文结构。
			 例如： 1->2->1，返回true。 1->2->2->1，返回true,
			 15->6->15，返回true。 1->2->3，返回false,1->2->3->1，返回false

			 进阶： 如果链表长度为N，时间复杂度达到O(N)，额外空间复杂度达到O(1)。
*/

/*
	思路：
		不考虑额外空间复杂度的办法：笔试中使用，能快速的解决
			1.先遍历一遍链表，把所有的值压入栈中，再遍历一遍，用栈顶数据与之比较，这样就可以判断是否回文
			2.还可以用两个辅助指针，一个快指针，每次走两步，一个慢指针，每次走一步，
			  当快指针走到头时，慢指针走到一半的位置。继续遍历慢指针到尾部，并开始记录慢指针对应的值，压入栈中。
			  再遍历链表的前半部分，是不是和栈中的数据相对应
		考虑时间复杂度
			使用快慢指针，同样是慢指针走到中间位置时，让后半部分的链表倒置，然后从两头开始遍历对比，有不一样的
			就返回false，一直对比到中间位置，比较完以后，把链表再还原回去
*/

//只使用栈，时间复杂度为O(n)，空间复杂度为O(n)
void useStack(List *list)
{
	if (list == NULL)
		return;
	stack<int> stackInt;
	//先遍历一边链表，将节点值放入栈中
	Node *curr = list->head;
	while (curr)
	{
		stackInt.push(curr->value);
		curr = curr->next;
	}

	//再遍历一遍，对比数据
	curr = list->head;
	while (curr)
	{
		int n = stackInt.top();
		if (n != curr->value)
		{
			printf("no huiwen\n");
			return;
		}
		curr = curr->next;
		stackInt.pop();
	}
	printf("is huiwen\n");
}

//使用快慢指针和反转链表，时间复杂度为O(n)，空间复杂度为O(1)
void useQuickSlowPointer(List *list)
{
	Node *quick = list->head;
	Node *slow = list->head;

	while (quick != NULL && quick->next != NULL)
	{
		quick = quick->next->next;
		slow = slow->next;
	}
	/*
		如果节点个数为奇数个，如 1 2 3 2 1，此时慢指针指向中间的位置
		如果节点个数为偶数个，如 1 2 2 1，此时慢指针指向中间的位置两个中的第二个
	*/
	printf("slow value: %d\n", slow->value);

	//翻转链表
	Node *pre = NULL;
	Node *curr = slow;
	while (curr)
	{
		Node *next = curr->next;
		curr->next = pre;
		pre = curr;
		curr = next;
	}
	//此时pre指向最后一个节点
	Node *rear = pre;
	Node *front = list->head;

	bool ret = true;
	while (rear != NULL && front != NULL)
	{
		if (rear->value != front->value)
		{
			printf("no huiwen\n");
			ret = false;
			break;
		}
		rear = rear->next;
		front = front->next;
	}

	if (ret)
		printf("is huiwen\n");
	//将链表翻转回来，只要别把原来链表的最后一个结点丢了，就可以原样倒置
	//pre指向最后一个节点
	curr = pre;
	pre = NULL;
	while (curr)
	{
		Node *next = curr->next;
		curr->next = pre;
		pre = curr;
		curr = next;
	}
}

int main()
{
	List list;
	list.AddNodeTail(1);
	list.AddNodeTail(2);
	list.AddNodeTail(3);
	list.AddNodeTail(4);
	list.AddNodeTail(3);
	list.AddNodeTail(2);
	list.AddNodeTail(1);
	list.Printf();

	useStack(&list);
	list.Printf();
	useQuickSlowPointer(&list);
	list.Printf();
}