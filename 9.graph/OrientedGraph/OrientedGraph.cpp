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
	//�ڵ��Ƿ��Ѿ�������û�еĻ��½��ڵ�
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

	//from ָ�� to
	_mapOrientedGraph[nodeFrom].insert(nodeTo);

	//ָ��ڵ� to �Ľڵ����һ��
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

	//ɾ�� from ָ�� to
	if (_mapOrientedGraph.find(nodeFrom) != _mapOrientedGraph.end())
	{
		if (_mapOrientedGraph[nodeFrom].find(nodeTo) != _mapOrientedGraph[nodeFrom].end())
			_mapOrientedGraph[nodeFrom].erase(nodeTo);
	}

	//ָ�� to �Ľڵ�����һ��
	if (_mapNegativeOriented.find(nodeTo) != _mapNegativeOriented.end())
	{
		if (_mapNegativeOriented[nodeTo].find(nodeFrom) != _mapNegativeOriented[nodeTo].end())
			_mapNegativeOriented[nodeTo].erase(nodeFrom);
	}
}
