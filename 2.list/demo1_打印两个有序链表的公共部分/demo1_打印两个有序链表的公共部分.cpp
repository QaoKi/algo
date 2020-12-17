#include "../List/List.h"

/*
	【题目】 给定两个有序链表的头指针head1和head2，打印两个链表的公共部分
*/

/*
	思路：用外排的方式，两个辅助指针指向头，谁小谁向下移动，打印相同值
*/

void PrintfEqual(List *list1, List *list2)
{
	if (list1 == NULL || list2 == NULL)
		return;
	Node *curr1 = list1->head;
	Node *curr2 = list2->head;

	while (curr1 != NULL && curr2 != NULL)
	{
		if (curr1->value == curr2->value)
		{
			printf("%d ", curr1->value);
			//两个都向后移动
			curr1 = curr1->next;
			curr2 = curr2->next;
		}
		else if (curr1->value > curr2->value)
			//较小的向后移
			curr2 = curr2->next;
		else
			curr1 = curr1->next;
	}

	printf("\n");
}

int main()
{
	List list1;
	list1.AddNodeTail(1);
	list1.AddNodeTail(2);
	list1.AddNodeTail(3);
	list1.AddNodeTail(4);
	list1.AddNodeTail(5);
	list1.Printf();

	List list2;
	list2.AddNodeTail(2);
	list2.AddNodeTail(4);
	list2.AddNodeTail(5);
	list2.AddNodeTail(7);
	list2.AddNodeTail(8);
	list2.Printf();

	PrintfEqual(&list1, &list2);
	return 0;
}
