#include "OrientedWeightedGraph.h"

OrientedWeightedGraph::OrientedWeightedGraph() { _nodeRoot = NULL; }
OrientedWeightedGraph::~OrientedWeightedGraph()
{
	auto it = _mapAllNode.begin();
	for (; it != _mapAllNode.end(); it++)
	{
		Node *node = it->second;
		delete node;
		node = NULL;
	}
}

void OrientedWeightedGraph::addEdge(int from, int to, int iWeight)
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
	_mapOrientedWeightedGraph[nodeFrom].insert(make_pair(nodeTo, iWeight));

	//指向节点 to 的节点多了一个
	_mapNegativeOriented[nodeTo].insert(make_pair(nodeFrom, iWeight));
}

void OrientedWeightedGraph::delEdge(int from, int to)
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
	if (_mapOrientedWeightedGraph.find(nodeFrom) != _mapOrientedWeightedGraph.end())
	{
		if (_mapOrientedWeightedGraph[nodeFrom].find(nodeTo) != _mapOrientedWeightedGraph[nodeFrom].end())
			_mapOrientedWeightedGraph[nodeFrom].erase(nodeTo);
	}

	//指向 to 的节点少了一个
	if (_mapNegativeOriented.find(nodeTo) != _mapNegativeOriented.end())
	{
		if (_mapNegativeOriented[nodeTo].find(nodeFrom) != _mapNegativeOriented[nodeTo].end())
			_mapNegativeOriented[nodeTo].erase(nodeFrom);
	}
}