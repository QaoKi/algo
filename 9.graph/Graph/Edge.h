#pragma once
#include <iostream>
#include <string>
#include "Node.h"

class Edge
{
public:
	Edge();
	Edge(int weight,Node *from,Node *to);
	~Edge();

public:
	int weight;		//�����ߵ�Ȩ���Ƕ���
	Node *from;		//������
	Node *to;		//ָ��˭
};

