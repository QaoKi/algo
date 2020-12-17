#include "OrientedGraph.h"
#include <queue>

OrientedGraph::OrientedGraph() { _nodeRoot = NULL; }
OrientedGraph::~OrientedGraph()
{
	auto it = _mapAllNode.begin();
	for (; it != _mapAllNode.end(); it++)
	{
		Node *node = it->second;
		delete node;
		node = NULL;
	}
}

void OrientedGraph::addEdge(int from, int to)
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
	_mapOrientedGraph[nodeFrom].insert(nodeTo);

	//指向节点 to 的节点多了一个
	_mapNegativeOriented[nodeTo].insert(nodeFrom);
}

void OrientedGraph::delEdge(int from, int to)
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
	if (_mapOrientedGraph.find(nodeFrom) != _mapOrientedGraph.end())
	{
		if (_mapOrientedGraph[nodeFrom].find(nodeTo) != _mapOrientedGraph[nodeFrom].end())
			_mapOrientedGraph[nodeFrom].erase(nodeTo);
	}

	//指向 to 的节点少了一个
	if (_mapNegativeOriented.find(nodeTo) != _mapNegativeOriented.end())
	{
		if (_mapNegativeOriented[nodeTo].find(nodeFrom) != _mapNegativeOriented[nodeTo].end())
			_mapNegativeOriented[nodeTo].erase(nodeFrom);
	}
}
