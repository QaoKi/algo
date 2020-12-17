#include "Graph.h"

Graph::Graph()
{
}

Graph::~Graph()
{
}

/*
	传一个数组，[[1,2,3],[2,3,4],[4,5,6]]
	1	2	3	
	2	3	4
	4	5	6
	构建一个图
	第一列表示权重
	第二列表示form
	第三列表示to
*/
Node *Graph::GetGraph(int arr[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		int weight = arr[i][0];
		int from = arr[i][1];
		int to = arr[i][2];
		//from这个结点在图中有没有，没有的话就新建一个点
		if (this->nodes.find(from) == this->nodes.end())
		{
			this->nodes[from] = new Node(from);
		}

		//to这个结点在图中有没有，没有的话新建一个节点
		if (this->nodes.find(to) == this->nodes.end())
		{
			this->nodes[to] = new Node(to);
		}

		//这样from和to在图中都有了，搭建他们的关系
		//取出来from和to节点
		Node *fromNode = this->nodes[from];
		Node *toNode = this->nodes[to];
		//新建一条边
		Edge *newEdge = new Edge(weight, fromNode, toNode);

		//from指向to
		fromNode->nexts.push_back(toNode);
		fromNode->out++; //节点指向的节点的数量+1
		toNode->in++;	 //节点被指向的数量+1
		//节点作为from的边
		fromNode->edges.push_back(newEdge);
		this->edges.insert(newEdge);
	}

	return this->nodes[1];
}
