#ifndef _WEIGHTED_GRAPH_H_
#define _WEIGHTED_GRAPH_H_

#include <string>
#include <unordered_map>
#include <set>
#include <map>
#include "../Node.h"
#include "../Edge.h"
using namespace std;

//权重图，不仅要保存 from指向to，也要保存 to 指向from
class WeightedGraph
{
public:
	WeightedGraph();
	~WeightedGraph();

	//增加节点与节点之间的指向
	void addEdge(int from, int to, int iWeight);

	//删除节点与节点之间的指向
	void delEdge(int from, int to);

public:
	//用 map（红黑树）代替 list，这样查找节点a是否和节点b相连时会很快
	//<nodeA,<nodeB,weighted>>，节点A指向节点B，权重为 weighted
	unordered_map<Node *, map<Node *, int>> _mapWeightedGraph;
	//保存所有节点,key 为 data
	unordered_map<int, Node *> _mapAllNode;

	//把第一个进图的节点作为根节点，方便遍历
	Node *_nodeRoot;
};

#endif