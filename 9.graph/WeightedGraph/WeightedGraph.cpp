#include "WeightedGraph.h"

WeightedGraph::WeightedGraph() { _nodeRoot = NULL; }
WeightedGraph::~WeightedGraph()
{
	auto it = _mapAllNode.begin();
	for (; it != _mapAllNode.end(); it++)
	{
		Node *node = it->second;
		delete node;
		node = NULL;
	}
}

void WeightedGraph::addEdge(int from, int to, int iWeight)
{
	//节点是否已经建立，没有的话新建节点
	if (_mapAllNode.find(from) == _mapAllNode.end())
		_mapAllNode[from] = new Node(from);

	if (_mapAllNode.find(to) == _mapAllNode.end())
		_mapAllNode[to] = new Node(to);

	Node *nodeFrom = _mapAllNode[from];
	Node *nodeTo = _mapAllNode[to];

	if (nodeFrom == NULL || nodeTo == NULL)
		return;

	if (_nodeRoot == NULL)
		_nodeRoot = nodeFrom;
	//from 指向 to
	_mapWeightedGraph[nodeFrom].insert(make_pair(nodeTo, iWeight));

	//to 指向 from
	_mapWeightedGraph[nodeTo].insert(make_pair(nodeFrom, iWeight));
}

void WeightedGraph::delEdge(int from, int to)
{
	Node *nodeFrom = NULL;
	Node *nodeTo = NULL;
	if (_mapAllNode.find(from) != _mapAllNode.end())
		nodeFrom = _mapAllNode[from];

	if (_mapAllNode.find(to) != _mapAllNode.end())
		nodeTo = _mapAllNode[to];

	if (nodeFrom == NULL || nodeTo == NULL)
		return;

	//删除 from 指向 to
	if (_mapWeightedGraph.find(nodeFrom) != _mapWeightedGraph.end())
	{
		if (_mapWeightedGraph[nodeFrom].find(nodeTo) != _mapWeightedGraph[nodeFrom].end())
			_mapWeightedGraph[nodeFrom].erase(nodeTo);
	}

	//删除 to 指向 from
	if (_mapWeightedGraph.find(nodeTo) != _mapWeightedGraph.end())
	{
		if (_mapWeightedGraph[nodeTo].find(nodeFrom) != _mapWeightedGraph[nodeTo].end())
			_mapWeightedGraph[nodeTo].erase(nodeFrom);
	}
}