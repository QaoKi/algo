#include "List.h"

List::List()
{
    head = NULL;
    tail = NULL;
    len = 0;
}

List::~List()
{
    Clear();
}

void List::AddNodeHead(int value)
{
    Node *newNode = new Node;
    if (newNode == NULL)
        return;
    newNode->value = value;

    if (len == 0)
        tail = newNode;
    else
        //如果链表不为空，要处理一下头节点的前置指针
        head->prev = newNode;

    //新结点前驱结点为null
    newNode->prev = NULL;
    newNode->next = head;
    //头节点指向新插入的节点
    head = newNode;

    len++;
}

void List::AddNodeTail(int value)
{
    Node *newNode = new Node;
    if (newNode == NULL)
        return;
    newNode->value = value;

    if (len == 0)
        head = newNode;
    else
        //如果链表不为空，要处理一下尾节点的后继指针
        tail->next = newNode;

    //新结点前驱结点为tail
    newNode->prev = tail;
    newNode->next = NULL;
    //尾节点指向新插入的节点
    tail = newNode;

    len++;
}

void List::DelNode(Node *node)
{
    if (node->prev != NULL)
        node->prev->next = node->next;
    else
        //没有前置节点，说明node是头节点
        head = node->next;

    if (node->next != NULL)
        node->next->prev = node->prev;
    else
        //没有后置节点，说明是尾结点
        tail = tail->prev;

    if (node)
    {
        delete node;
        node = NULL;
    }

    len--;
}

Node *List::SearchKey(int key)
{
    Node *curr = head;
    while (curr)
    {
        if (curr->value == key)
            return curr;
        curr = curr->next;
    }

    return NULL;
}

void List::Printf()
{
    Node *curr = head;
    while (curr)
    {
        printf("%d ", curr->value);
        curr = curr->next;
    }

    printf("\n");
}

void List::Clear()
{
    Node *curr = head;
    while (curr)
    {
        Node *next = curr->next;
        delete curr;
        curr = next;
    }

    len = 0;
    head = NULL;
    tail = NULL;
}