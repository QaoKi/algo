#ifndef _ORIENTED_GRAPH_H_
#define _ORIENTED_GRAPH_H_

#include <string>
#include <unordered_map>
#include <iostream>
#include <set>
#include "../Node.h"
using namespace std;

//有向图只需要保存 from 指向to 就可以了
class OrientedGraph
{
public:
	OrientedGraph();
	~OrientedGraph();

	//增加节点与节点之间的指向
	void addEdge(int from, int to);

	//删除节点与节点之间的指向
	void delEdge(int from, int to);

public:
	//用 set（红黑树）代替 list，这样查找节点a是否和节点b相连时会很快
	unordered_map<Node *, set<Node *>> _mapOrientedGraph;
	//保存所有节点,key 为 data
	unordered_map<int, Node *> _mapAllNode;

	//记录哪些节点指向了节点 a。可以用来对有向图取反
	unordered_map<Node *, set<Node *>> _mapNegativeOriented;
	//把第一个进图的节点作为根节点，方便遍历
	Node *_nodeRoot;
};

#endif