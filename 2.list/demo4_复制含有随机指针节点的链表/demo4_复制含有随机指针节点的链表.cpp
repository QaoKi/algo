#include "../List/List.h"
#include <map>

/*
	【题目】 一种特殊的链表节点类,比平常的Node结构，多了一个rand指针，
			next指针和正常单链表中next指针的意义一样，都指向下一个节点，
			rand指针是Node类中新增的指针，这个指针可能指向链表中的任意一个节点，也可能指向null。

			给定一个由Node节点类型组成的无环单链表的头节点head，请实现一个函数完成
			这个链表中所有结构的复制，并返回复制的新链表的头节点。

			进阶：空间复杂度O(1)，时间复杂度为 O(N)
*/

/*
	思路：
		如果像对待普通链表一样，用next遍历原来的链表，对于每一个结点，创建一个值相同的新节点，然后组合成一条新的链表
		接下来有两种处理方式：
		1.再遍历rand的指向，创建节点加到头节点上，就会出现重复的节点。也不行。
		2.再次用next遍历原链表，并且同时遍历新链表，让 newNode.rand = oldNode.rand
		  这样新结点的rand，指向的是老链表上的结点，并没有指向新链表上的结点，所以这种方法不行
		  这种方法的问题在于，如何通过原来的结点，找到它的拷贝结点

	解决：
	不考虑空间复杂度
		首先用next指向遍历链表，
		创建一个map，比如遍历到1号位置，map中key放1号节点，再拷贝一份1号节点，放到value中
		这样就形成节点和它的拷贝节点的对应关系，遍历完一遍之后，所有的节点，在map中都有一个拷贝节点

		这样做的目的，是为了复制所有的节点，并且在连接这些节点的时候，能随时找到
		比如，next是这样的：1->2->3，找1的rand指向，通过原来的链表知道指向3，但是如果
		不将3的拷贝节点和3号节点放到map中，不容易通过3找到3的拷贝节点，

		总的来说，因为每个节点都是没有序号的，他们的不同只是value不同，所以需要将
		节点和拷贝的节点放到map中，方便查找

	考虑空间复杂度
		因为要记录节点和它的拷贝节点的对应关系，所以用到了map,现在不使用map
		假设链表中节点为ABCDEF，它们的拷贝节点分别为abcdef
		遍历链表，链表的next指针的结构为A->B->C->D->E->F->NULL
		遍历到A，创建一个A的拷贝节点a，连接成 A->a->B->C->D->E->F->NULL
		同理，遍历到BCDEF时，把结构变成	A->a->B->b->C->c->D->d->E->e->F->f->NULL
		这样的话，就能通过A找到a，通过B找到b。。

		再遍历链表，比如A的rand指向C，那么遍历的时候，让a->rand = A->rand->next，这样就让a
		的rand指向了c

		最后把两个链表分离出来
*/

//使用辅助空间
List *useMap(List *list)
{
	if (!list->len)
		return NULL;

	List *copyList = new List;
	map<Node *, Node *> mapNode;
	Node *curr = list->head;
	while (curr)
	{
		//将原链表中所有的结点，拷贝一份，并用map将两者建立联系
		Node *copyNode = new Node;
		copyNode->value = curr->value;

		mapNode[curr] = copyNode;
		curr = curr->next;
	}

	//重新遍历一下，为新链表确定结点之间的指向
	curr = list->head;
	while (curr)
	{
		mapNode[curr]->next = mapNode[curr->next];
		mapNode[curr]->rand = mapNode[curr->rand];
		curr = curr->next;
	}
	//为新链表确定头结点和尾结点
	copyList->head = mapNode[list->head];
	copyList->tail = mapNode[list->tail];

	return copyList;
}

List *notUseMap(List *list)
{
	if (!list->len)
		return NULL;
	List *copyList = new List;
	//遍历一遍链表，每次都创建一个copy节点放到curr节点的后面
	Node *curr = list->head;
	while (curr)
	{
		Node *copyNode = new Node;
		copyNode->value = curr->value;
		//将copy节点放到curr节点的后面
		copyNode->next = curr->next;
		curr->next = copyNode;

		//curr要跳两次
		curr = curr->next->next;
	}
	//此时链表变成了 A->a->B->b->C->c->D->d->E->e->F->f->NULL
	//再遍历一遍，处理rand指向
	curr = list->head;
	while (curr != NULL && curr->next != NULL)
	{
		if (curr->rand != NULL)
			curr->next->rand = curr->rand->next;
		else
			//当前结点的rand指向NULL，那么拷贝结点的rand也指向NULL
			curr->next->rand = NULL;
		curr = curr->next->next;
	}

	//将两条链表拆分出来，这块如果想不出来，可以简单画个图
	curr = list->head;
	//设置头节点
	copyList->head = curr->next;
	while (curr != NULL && curr->next != NULL)
	{
		Node *nextNode = curr->next;
		curr->next = nextNode->next;
		curr = nextNode;
	}

	/*
		//另一种写法。这种一次处理两个节点，上面的是一次处理一个节点
		while (curr != NULL && curr->next != NULL)
		{
			Node *nextNode = curr->next;
			curr->next = nextNode->next;
			if (nextNode->next == NULL)
				//nextNode指向了最后一个节点，不用再处理了
				break;
			nextNode->next = nextNode->next->next;
			curr = curr->next;
		}
	*/
	return copyList;
}

int main()
{
	List list;

	list.AddNodeTail(1);
	list.AddNodeTail(3);
	list.AddNodeTail(5);
	list.AddNodeTail(7);
	list.AddNodeTail(9);
	list.AddNodeTail(11);
	list.AddNodeTail(13);
	list.AddNodeTail(15);
	list.Printf();

	//给每个节点加上rand节点
	Node *current = list.head;
	current->rand = NULL; //1 指向 NULL

	current = current->next;
	current->rand = current->next->next; //3指向7

	current = current->next;
	current->rand = list.head; //5指向1

	current = current->next;
	current->rand = NULL; //7 指向 NULL

	current = current->next;
	current->rand = current->next; //9 指向 11

	current = current->next;
	current->rand = list.head->next; //11 指向 3

	current = current->next;
	current->rand = list.head->next->next->next; //13 指向 7

	current = current->next;
	current->rand = NULL; //15 指向 NULL

	Node *curr = list.head;
	while (curr)
	{

		if (curr->rand != NULL)
			printf("%d --> %d\n", curr->value, curr->rand->value);
		else
			printf("%d --> NULL\n", curr->value);

		curr = curr->next;
	}

	//List *copylist = useMap(&list);
	List *copylist = notUseMap(&list);
	//验证一下
	copylist->Printf();

	curr = copylist->head;
	while (curr)
	{

		if (curr->rand != NULL)
			printf("%d --> %d\n", curr->value, curr->rand->value);
		else
			printf("%d --> NULL\n", curr->value);

		curr = curr->next;
	}

	return 0;
}
