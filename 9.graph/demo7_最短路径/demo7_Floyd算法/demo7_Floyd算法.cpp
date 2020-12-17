#include <iostream>
#include <string>
#include <queue>
#include <map>
#include "../../Edge.h"
#include "../../OrientedWeightedGraph/OrientedWeightedGraph.h"

using namespace std;

/*
	Floyd�㷨����Դ���·���㷨
	

*/

/*
	ʱ�临�Ӷȣ�O(V^3)��Ч�ʱ�ִ��V��Dijkstra�㷨Ҫ�ߣ�Dijkstraһ��ֻ�����һ�����㵽������������·������V�Ƕ�������
*/

void findNegativeClcle(OrientedWeightedGraph &weightedGraph, Node *s, map<Node *, Node *> &edgeTo, bool &hasNegativeClcle)
{
	cout << "start find clcle" << endl;

	for (auto it = weightedGraph._mapAllNode.begin(); it != weightedGraph._mapAllNode.end(); it++)
	{
		/*
			�μ�demo_4��⻷�� OrientedGraphCycle
			�����ʵ��Ľڵ�����ѹ��ջ�У���������ڻ��ϣ����߶���� edgeTo[]�ڻ��ϣ���ôһ�������±���������ջ�Ķ���
			ע�⣺�����������д����
				  Node* self = it->second;
				  Node *curr = it->second;
				  while (edgeTo.find(curr) != edgeTo.end())
				  {
					curr = edgeTo[curr];
					//���ת��һȦ�ֻص��Լ��ˣ�˵���ڻ���
					if (curr == self){}
				  }
				����д������� self �����ڻ��ϣ��ǿ��Լ��������������self���ڻ��ϣ�
				���� edgeTo[self]�ڻ��ϣ�����edgeTo[edgeTo[self]] �ڻ��ϣ���ô����whileѭ�����������
		*/

		Node *curr = it->second;
		//��set������ջ��Ҳ������map<Node, bool>
		set<Node *> setNodeInStack;
		setNodeInStack.insert(curr);
		while (edgeTo.find(curr) != edgeTo.end())
		{
			setNodeInStack.insert(curr);
			curr = edgeTo[curr];
			if (setNodeInStack.find(curr) != setNodeInStack.end())
			{
				//�л�
				cout << "find clcle:  ";
				cout << curr->_data << "  ";
				Node *parent = edgeTo[curr];
				while (parent != curr)
				{
					cout << parent->_data << "  ";
					parent = edgeTo[parent];
				}
				cout << endl;
				hasNegativeClcle = true;
				return;
			}
		}
	}
}
void relax(OrientedWeightedGraph &weightedGraph, Node *node, Node *s, map<Node *, bool> &mapNodeJoinQueue, queue<Node *> &queueNode, map<Node *, int> &distTo, map<Node *, Node *> &edgeTo, int &count, bool &hasNegativeClcle)
{
	//�ɳ� node ָ������б�
	for (auto it = weightedGraph._mapOrientedWeightedGraph[node].begin(); it != weightedGraph._mapOrientedWeightedGraph[node].end(); it++)
	{
		//��ɱߣ�����Ҳ�У�ֻ��Ϊ�˴����������
		Edge edge(node, it->first, it->second);
		//�����ɳڲ�����ֻ���ɳڳɹ����ܽ������
		if (distTo.find(edge._to) == distTo.end() || distTo[edge._to] > distTo[edge._from] + edge._weight)
		{
			distTo[edge._to] = distTo[edge._from] + edge._weight;
			edgeTo[edge._to] = edge._from;

			if (mapNodeJoinQueue.find(edge._to) == mapNodeJoinQueue.end() || !mapNodeJoinQueue[edge._to])
			{
				queueNode.push(edge._to);
				mapNodeJoinQueue[edge._to] = true;
			}
		}

		/*
			�ж��л�1��
			ÿ�α�����V�����Ժ󣬼���Ƿ��л�����֪��Ϊʲô�����жϣ�
			�����жϵĻ����ܸ����ٵķ����Ƿ��л������ǻ���߼��� findNegativeClcle()
		*/
		if (count++ % weightedGraph._mapAllNode.size() == 0)
		{
			findNegativeClcle(weightedGraph, s, edgeTo, hasNegativeClcle);
		}
	}
}

//����ͼ�У���sΪ��㣬�������ɴ�ڵ�����·��
bool ShortPath(OrientedWeightedGraph &weightedGraph, Node *s, map<Node *, int> &indistTo, map<Node *, Node *> &inedgeTo)
{

	map<Node *, int> distTo;
	map<Node *, Node *> edgeTo;
	//����һ�ֱ����ɵĽڵ�
	queue<Node *> queueNode;
	//��鶥���Ƿ��Ѿ�������У���ֹ�ظ����������
	map<Node *, bool> mapNodeJoinQueue;

	//��ʼ��
	distTo[s] = 0;
	queueNode.push(s);
	mapNodeJoinQueue[s] = true;

	//��������
	int count = 0;
	bool hasNegativeClcle = false;
	while (!queueNode.empty() && !hasNegativeClcle)
	{
		Node *node = queueNode.front();
		queueNode.pop();
		mapNodeJoinQueue[node] = false;
		//���ɶ���
		relax(weightedGraph, node, s, mapNodeJoinQueue, queueNode, distTo, edgeTo, count, hasNegativeClcle);

		/*
			�ж��л�2��
			���������ж��Ƿ��л��������жϻ���findNegativeClcle()�����߼��飬����relax()����߼���
			if (count++ == weightedGraph._mapAllNode.size())
			{
				findNegativeClcle(weightedGraph, s, edgeTo, hasNegativeClcle);
			}
		*/
	}

	indistTo = distTo;
	inedgeTo = edgeTo;
	return hasNegativeClcle;
}

int main()
{

	OrientedWeightedGraph weightedGraph;
	// weightedGraph.addEdge(1, 2, 10);
	// weightedGraph.addEdge(1, 4, 30);
	// weightedGraph.addEdge(1, 5, 100);
	// weightedGraph.addEdge(2, 3, 50);
	// weightedGraph.addEdge(3, 5, 10);
	// weightedGraph.addEdge(4, 3, 20);
	// weightedGraph.addEdge(4, 5, 60);

	//weightedGraph.addEdge(5, 1, 20);
	//weightedGraph.addEdge(2, 5, -50);

	//weightedGraph.addEdge(5, 4, -40);

	weightedGraph.addEdge(2, 1, -40);

	weightedGraph.addEdge(0, 4, 38);
	weightedGraph.addEdge(0, 2, 26);
	weightedGraph.addEdge(4, 5, 35);
	weightedGraph.addEdge(5, 4, -66);
	weightedGraph.addEdge(4, 7, 37);
	weightedGraph.addEdge(5, 7, 28);
	weightedGraph.addEdge(7, 5, 28);
	weightedGraph.addEdge(5, 1, 32);
	weightedGraph.addEdge(7, 3, 39);
	weightedGraph.addEdge(1, 3, 29);
	weightedGraph.addEdge(2, 7, 34);
	weightedGraph.addEdge(6, 2, 40);
	weightedGraph.addEdge(3, 6, 52);
	weightedGraph.addEdge(6, 0, 58);
	weightedGraph.addEdge(6, 4, 93);

	map<Node *, int> distTo;
	map<Node *, Node *> edgeTo;

	bool hasNegativeClcle = ShortPath(weightedGraph, weightedGraph._nodeRoot, distTo, edgeTo);

	if (!hasNegativeClcle)
	{
		//û�и�Ȩ�ػ�ʱ������
		for (auto it = distTo.begin(); it != distTo.end(); it++)
		{
			cout << "node: " << it->first->_data << " weighted: " << it->second << endl;
		}

		for (auto it = weightedGraph._mapAllNode.begin(); it != weightedGraph._mapAllNode.end(); it++)
		{
			cout << "node: " << weightedGraph._nodeRoot->_data << " to " << it->first << "  path: ";

			Node *curr = it->second;
			while (edgeTo.find(curr) != edgeTo.end())
			{
				cout << curr->_data << "  ";
				curr = edgeTo[curr];
			}
			cout << weightedGraph._nodeRoot->_data << endl;
		}
	}

	return 0;
}