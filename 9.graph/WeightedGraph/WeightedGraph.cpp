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
	_mapWeightedGraph[nodeFrom].insert(make_pair(nodeTo, iWeight));

	//to ָ�� from
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

	//ɾ�� from ָ�� to
	if (_mapWeightedGraph.find(nodeFrom) != _mapWeightedGraph.end())
	{
		if (_mapWeightedGraph[nodeFrom].find(nodeTo) != _mapWeightedGraph[nodeFrom].end())
			_mapWeightedGraph[nodeFrom].erase(nodeTo);
	}

	//ɾ�� to ָ�� from
	if (_mapWeightedGraph.find(nodeTo) != _mapWeightedGraph.end())
	{
		if (_mapWeightedGraph[nodeTo].find(nodeFrom) != _mapWeightedGraph[nodeTo].end())
			_mapWeightedGraph[nodeTo].erase(nodeFrom);
	}
}