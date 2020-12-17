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
	_mapOrientedWeightedGraph[nodeFrom].insert(make_pair(nodeTo, iWeight));

	//ָ��ڵ� to �Ľڵ����һ��
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

	//ɾ�� from ָ�� to
	if (_mapOrientedWeightedGraph.find(nodeFrom) != _mapOrientedWeightedGraph.end())
	{
		if (_mapOrientedWeightedGraph[nodeFrom].find(nodeTo) != _mapOrientedWeightedGraph[nodeFrom].end())
			_mapOrientedWeightedGraph[nodeFrom].erase(nodeTo);
	}

	//ָ�� to �Ľڵ�����һ��
	if (_mapNegativeOriented.find(nodeTo) != _mapNegativeOriented.end())
	{
		if (_mapNegativeOriented[nodeTo].find(nodeFrom) != _mapNegativeOriented[nodeTo].end())
			_mapNegativeOriented[nodeTo].erase(nodeFrom);
	}
}