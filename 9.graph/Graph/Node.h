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
	int value;	//值
	int in;		//有多少个节点指向这个节点
	int out;	//这个节点指向多少个节点
	list<Node*> nexts;	//作为from指向的to节点
	list<Edge*> edges;	//作为from节点的边
};

