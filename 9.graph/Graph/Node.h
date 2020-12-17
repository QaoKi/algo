#pragma once
#include <string>
//#include "Edge.h"
#include <list>
using namespace std;

extern class Edge;

class Node
{
public:
	Node(int value);
	~Node();

public:
	int value;	//ֵ
	int in;		//�ж��ٸ��ڵ�ָ������ڵ�
	int out;	//����ڵ�ָ����ٸ��ڵ�
	list<Node*> nexts;	//��Ϊfromָ���to�ڵ�
	list<Edge*> edges;	//��Ϊfrom�ڵ�ı�
};

