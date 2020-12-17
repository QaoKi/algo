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
	int weight;		//这条边的权重是多少
	Node *from;		//从哪来
	Node *to;		//指向谁
};

