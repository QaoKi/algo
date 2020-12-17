#ifndef _UNDIRECTED_GRAPH_H_
#define _UNDIRECTED_GRAPH_H_

#include <string>
#include <unordered_map>
#include <set>
#include <iostream>
#include "../Node.h"
using namespace std;
//无向图，不仅要保存 from指向to，也要保存 to 指向from
class UndirectedGraph
{
public:
	UndirectedGraph();
	~UndirectedGraph();

	UndirectedGraph(const UndirectedGraph &graph);
	//增加节点与节点之间的指向
	void addEdge(int from, int to);

	//删除节点与节点之间的指向
	void delEdge(int from, int to);

public:
	//用 set（红黑树）代替 list，这样查找节点a是否和节点b相连时会很快
	unordered_map<Node *, set<Node *>> _mapUndirectedGraph;
	//保存所有节点,key 为 data
	unordered_map<int, Node *> _mapAllNode;

	//把第一个进图的节点作为根节点，方便遍历
	Node *_nodeRoot;
};

#endif