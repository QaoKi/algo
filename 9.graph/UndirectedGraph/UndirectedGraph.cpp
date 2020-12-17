#include "UndirectedGraph.h"
#include <queue>
#include <stack>

UndirectedGraph::UndirectedGraph() { _nodeRoot = NULL; }
UndirectedGraph::~UndirectedGraph()
{
	auto it = _mapAllNode.begin();
	for (; it != _mapAllNode.end(); it++)
	{
		Node *node = it->second;
		delete node;
		node = NULL;
	}
}

UndirectedGraph::UndirectedGraph(const UndirectedGraph &graph)
{
	_mapUndirectedGraph = graph._mapUndirectedGraph;
	_mapAllNode = graph._mapAllNode;
	_nodeRoot = graph._nodeRoot;
}

void UndirectedGraph::addEdge(int from, int to)
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
	_mapUndirectedGraph[nodeFrom].insert(nodeTo);

	//to ָ�� from
	_mapUndirectedGraph[nodeTo].insert(nodeFrom);
}

void UndirectedGraph::delEdge(int from, int to)
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
	if (_mapUndirectedGraph.find(nodeFrom) != _mapUndirectedGraph.end())
	{
		if (_mapUndirectedGraph[nodeFrom].find(nodeTo) != _mapUndirectedGraph[nodeFrom].end())
			_mapUndirectedGraph[nodeFrom].erase(nodeTo);
	}

	//ɾ�� to ָ�� from
	if (_mapUndirectedGraph.find(nodeTo) != _mapUndirectedGraph.end())
	{
		if (_mapUndirectedGraph[nodeTo].find(nodeFrom) != _mapUndirectedGraph[nodeTo].end())
			_mapUndirectedGraph[nodeTo].erase(nodeFrom);
	}
}
