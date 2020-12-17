#include "Edge.h"



Edge::Edge(int weight, Node *from, Node *to)
{
	this->weight = weight;
	this->from = from;
	this->to = to;
}


Edge::Edge()
{

}

Edge::~Edge()
{
}
