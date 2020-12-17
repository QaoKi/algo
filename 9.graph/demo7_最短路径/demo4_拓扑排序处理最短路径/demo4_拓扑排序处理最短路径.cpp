#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include "../../Edge.h"
#include "../../OrientedWeightedGraph/OrientedWeightedGraph.h"

using namespace std;

/*
	���������ǰ�����޻�����ͼ���������ַ�ʽ�ʺ��޻�����ͼ�����������Ǵ��޻�����ͼ�����Ϊ0�Ķ��㿪ʼ�ģ�
	��Ȼ�����Ķ���s��һ�������Ϊ0�Ķ��㣬���ǲ��������ͼ�д�s�������ɵ���Ķ�������·����
	���Ҳ��ܸ�Ȩ�ߵ�Ӱ��

	ԭ��
		���˽�һ���������ķ��ɣ������˱ߵ��ɳڣ�����������ָ������бߣ������ɳڲ���
			void relax(Graph G, Node v) {
				for(Edge e : G.AllEdge(v)) {	//����vָ������б�
					if(distTo[e.to] < distTo[e.from] + e.weigh) {
						distTo[e.to] = distTo[e.from] + e.weigh;
						edgeTo[e.to] = e.from;
					}
				}	
			}
		�����˽�����������
			�����������ȼ��ߵĶ�������ǰ�棨���ȼ�����ָ��Ҫ�ȱ�ִ�еĶ��㣩�����������ǰ�����޻�����ͼ��
			��Ϊ�޻������Կ϶���һ�����Ϊ0�Ķ��㣬ֻ��ִ���������������ִ����һ������
			��ִ���ǳ����˵��������B�ļ�������A�ļ�����ôֻ���ȱ������ļ�A�������ٱ����ļ�B����ͼ�еĹ�ϵ����Aָ��B��
	ʵ�֣�
		��ͼ�����������򣬽�ͼ�ж��㰴��ִ�е����ȼ����򣬱���õ� s a v w t��s�����Ϊ0�Ķ��㣬a����s��v����a
		�������˳�򣬶Զ�����ж�����ɣ������㱻�����Ժ󣬶���ͽ�������С·�����������ж��㶼�������꣬������

	�ص㣺1�����㱻�����Ժ󣬱��� v�������Ժ�distTo[v]��ֵ�����ٸı䣬��Ϊ��v�������Ժ�֮����㷨�����ٴ����κ�ָ��v�ı�,
		 v�����ɵ�ǰ����ָ��v�Ľڵ㶼�Ѿ��������ˣ�Ҳ����˵v�������Ķ���a��s���Ѿ��������ˣ���ζ�Ŷ���a��sָ��v�ı��Ѿ����ɳ��ˣ���
		 ���Լ�Ȼv�ܱ����ɣ���˵��ָ��v�ı��Ѿ����������ˡ�v�������Ժ�֮�󲻻��ٱ�����ָ��v�ı��ˡ�
		 2�����������Ǵ��޻�����ͼ�����Ϊ0�Ķ��㿪ʼ�ģ�����㲻һ����ָ�������s������տ�ʼ��ʱ�򣬳�ʼ�� distTo[s] = 0;
		   �ڶԶ�����з��ɵ�ʱ�򣬼�� distTo[e.from]�Ƿ���ڣ���������ڣ�˵��s����ָ��������㣬Ҳ�Ͳ����ٴ�����
		   �������������Ժ󣬶���Ϊ a, b, c, s, d, e, f�����ȷ���a������û��distTo[a]��˵��s����ָ��a��aҲ�Ͳ����ٴ�����

	�ܽ᣺
		1���ʺ��޻�����ͼ
		2���ܹ�����Ȩ��
*/

/*
	ʱ�临�Ӷȣ���������ʱ�临�Ӷ�Ϊ O(E + V)���ٱ���һ�����еĶ��㣬ÿ���߶�ֻ�ᱻ�ɳ�һ��
		�����ܵ�ʱ�临�Ӷ�Ϊ O(E + V)
*/

void dfsHelp(OrientedWeightedGraph &weightedGraph, Node *node, set<Node *> &setNode, stack<Node *> &stackNode)
{
	//node�ڵ��Ϊ��ɫ
	setNode.insert(node);
	//�����ڵ�����б�
	for (auto it = weightedGraph._mapOrientedWeightedGraph[node].begin(); it != weightedGraph._mapOrientedWeightedGraph[node].end(); it++)
	{
		if (setNode.find(it->first) == setNode.end())
		{
			dfsHelp(weightedGraph, it->first, setNode, stackNode);
		}
	}

	//node�ڵ�ָ������нڵ㶼�������꣬node�ڵ��Ϊ��ɫ������ջ��
	stackNode.push(node);
}

queue<Node *> topologySort(OrientedWeightedGraph &weightedGraph)
{
	//��¼�ڵ�ķ���״̬
	set<Node *> setNode;
	//��ջ�������ĵ���
	stack<Node *> stackNode;

	//DFS�������нڵ�
	for (auto it = weightedGraph._mapAllNode.begin(); it != weightedGraph._mapAllNode.end(); it++)
	{
		//֮ǰû�б�����
		if (setNode.find(it->second) == setNode.end())
		{
			dfsHelp(weightedGraph, it->second, setNode, stackNode);
		}
	}

	//��ջ����ȡ���������
	queue<Node *> queueNode;
	while (!stackNode.empty())
	{
		Node *node = stackNode.top();
		stackNode.pop();
		queueNode.push(node);
	}

	return queueNode;
}

void relax(OrientedWeightedGraph &weightedGraph, Node *node, map<Node *, int> &distTo, map<Node *, Node *> &edgeTo)
{

	/*
		����Ƿ���distTo[node]�����û�У�˵��distTo[node]������󣬴Ӷ���s���ܴﵽnode����ônode�Ͳ���������
		��Ϊ����Ҫ��ģ��Ǵ�s�������ɴﵽ�Ķ�������·���������ڳ�ʼ����ʱ��ֻ��ʼ���� distTo[s] = 0;
		ֻ��nodeΪs��ʱ�򣬲ŻῪʼ�ɳڲ���
	*/
	if (distTo.find(node) == distTo.end())
		return;
	for (auto it = weightedGraph._mapOrientedWeightedGraph[node].begin(); it != weightedGraph._mapOrientedWeightedGraph[node].end(); it++)
	{
		//��ɱߣ�����Ҳ�У�ֻ��Ϊ�˴����������
		Edge edge(node, it->first, it->second);
		//�����ɳڲ���
		if (distTo.find(edge._to) == distTo.end() || distTo[edge._to] > distTo[edge._from] + edge._weight)
		{
			distTo[edge._to] = distTo[edge._from] + edge._weight;
			edgeTo[edge._to] = edge._from;
		}
	}
}

void ShortPath(OrientedWeightedGraph &weightedGraph, Node *s, map<Node *, int> &indistTo, map<Node *, Node *> &inedgeTo)
{

	//�������򣬽�ͼ�ж��㰴��ִ�е����ȼ�����
	queue<Node *> queueNode = topologySort(weightedGraph);
	map<Node *, int> distTo;
	map<Node *, Node *> edgeTo;

	//��ʼ������distToֵ
	distTo[s] = 0;

	//�Ӷ�����ȡ��������ж���ķ���
	while (!queueNode.empty())
	{
		Node *node = queueNode.front();
		queueNode.pop();
		cout << "get node[" << node->_data << "]" << endl;
		//������ɳ�
		relax(weightedGraph, node, distTo, edgeTo);
	}

	indistTo = distTo;
	inedgeTo = edgeTo;
}

int main()
{

	OrientedWeightedGraph weightedGraph;
	weightedGraph.addEdge(1, 2, 10);
	weightedGraph.addEdge(1, 4, 30);
	weightedGraph.addEdge(1, 5, 100);
	weightedGraph.addEdge(2, 3, 50);
	weightedGraph.addEdge(3, 5, 10);
	weightedGraph.addEdge(4, 3, 20);
	weightedGraph.addEdge(4, 5, 60);

	map<Node *, int> distTo;
	map<Node *, Node *> edgeTo;

	ShortPath(weightedGraph, weightedGraph._nodeRoot, distTo, edgeTo);

	//������
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

	return 0;
}