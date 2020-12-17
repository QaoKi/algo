#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <stack>
#include "../demo4_��⻷/OrientedGraphCycle.h"

using namespace std;

/*
	���������㷨 
		������1������ͼ��
			 2��û�л�

	���������ʹ�ó�����
		1.����������ȼ���
		��������ļ���A�ļ�������B,C,D�ļ���D�ļ�������E�ļ���B�ļ�������E�ļ���C�ļ�
		Ҫ������A�ļ�����Ҫ������BCD��Ҫ����B����Ҫ������EC��Ҫ����D����Ҫ������E
		���Ե�һ��Ӧ��������E��C��Ȼ������BD���������A

		���ܳ���ѭ������������A����B��B����C��C������A�����ԣ�ͼ�����л�

		��ͼ��ʾ���ǣ�
			Eָ��B��D
			Cָ��B��A
			Bָ��A
			Dָ��A
*/

/*
	BFS:
		��ͼ�У����Ϊ0�Ľڵ㣬�����������ڵ㣬�����ȱ����ɣ�E��C
		Ȼ��ɾ����Щ�ڵ㣬ɾ��EC�Ժ��ͼ����ȱ�Ϊ0�Ľڵ㣬������һ�α����ɵģ�B��D
		������
		ʱ�临�Ӷȣ�O(E + V)
	DFS:
		�����޻�ͼ������������������
		��dfs�����ڵ��ʱ��ʹ��һ��ջ����ĳ�ڵ�ָ������нڵ㶼�����꣬
		Ҳ���� demo4������ͼ��⻷�У��ڵ��Ϊ��ɫ�Ժ󣬽��ڵ����ջ�У����ȼ���͵�������ջ�����ȼ���ߵ������ջ
		���Ӷ�ΪO(E + V)
*/

queue<Node *> topologySortBFS(OrientedGraphCycle &orientedGraphCycle)
{
	queue<Node *> queueResult;

	//����ÿ���ڵ�����Ϊ���٣���һ�ݼ�¼
	map<Node *, int> mapNodeInDegree;
	//�������Ϊ0�Ľڵ�
	queue<Node *> queueZeroInDegree;

	//����ͼ�����нڵ�
	auto it = orientedGraphCycle._mapAllNode.begin();
	for (; it != orientedGraphCycle._mapAllNode.end(); ++it)
	{
		mapNodeInDegree[it->second] = orientedGraphCycle._mapNegativeOriented[it->second].size();
		if (mapNodeInDegree[it->second] == 0)
			queueZeroInDegree.push(it->second);
	}

	//����ʱ�����нڵ����ȶ���¼��map�У����Ϊ0�Ľڵ㶼��¼��queue��
	//�����޻�ͼ���϶������Ϊ0�Ľڵ㣬���û�У�˵���л�
	while (!queueZeroInDegree.empty())
	{
		//�Ӷ����е���һ���ڵ�
		Node *curr = queueZeroInDegree.front();
		queueZeroInDegree.pop();
		queueResult.push(curr);
		//��������ڵ���ָ��Ľڵ㣬����Щ�ڵ����ȼ�1�������1֮���Ϊ0������������
		for (set<Node *>::iterator it = orientedGraphCycle._mapOrientedGraph[curr].begin(); it != orientedGraphCycle._mapOrientedGraph[curr].end(); ++it)
		{
			mapNodeInDegree[*it]--;
			if (mapNodeInDegree[*it] == 0)
				queueZeroInDegree.push(*it);
		}
	}

	//������еĽڵ㣬�������˽������˵���޻�������˵���л�
	if (orientedGraphCycle._mapAllNode.size() == queueZeroInDegree.size())
		cout << "�޻�" << endl;

	return queueResult;
}

void dfsHelp(OrientedGraphCycle &orientedGraphCycle, Node *node, set<Node *> &setNode, stack<Node *> &stackNode)
{
	//node�ڵ��Ϊ��ɫ
	setNode.insert(node);
	//���� node�ڵ�ָ������нڵ�
	for (auto it = orientedGraphCycle._mapOrientedGraph[node].begin(); it != orientedGraphCycle._mapOrientedGraph[node].end(); ++it)
	{
		if (setNode.find(*it) == setNode.end())
			dfsHelp(orientedGraphCycle, *it, setNode, stackNode);
	}

	//node�ڵ�ָ������нڵ㶼�������꣬node�ڵ��Ϊ��ɫ������ջ��
	stackNode.push(node);
}

queue<Node *> topologySortDFS(OrientedGraphCycle &orientedGraphCycle)
{
	set<Node *> setNode;
	//ʹ��һ��ջ����Ž��
	stack<Node *> stackNode;
	for (auto it = orientedGraphCycle._mapAllNode.begin(); it != orientedGraphCycle._mapAllNode.end(); ++it)
	{
		if (setNode.find(it->second) == setNode.end())
			dfsHelp(orientedGraphCycle, it->second, setNode, stackNode);
	}

	//��ջ�е�����ȡ��������������
	queue<Node *> queueResult;
	while (!stackNode.empty())
	{
		Node *curr = stackNode.top();
		stackNode.pop();
		queueResult.push(curr);
	}
	return queueResult;
}

int main()
{
	//����һ������ͼ
	OrientedGraphCycle orientedGraphCycle;
	orientedGraphCycle.addEdge(5, 2);
	orientedGraphCycle.addEdge(5, 4);
	orientedGraphCycle.addEdge(3, 2);
	orientedGraphCycle.addEdge(3, 1);
	orientedGraphCycle.addEdge(2, 1);
	orientedGraphCycle.addEdge(4, 1);

	cout << "all node: ";
	for (auto it = orientedGraphCycle._mapAllNode.begin(); it != orientedGraphCycle._mapAllNode.end(); ++it)
		cout << it->second->_data << "  ";
	cout << endl;

	queue<Node *> queueNode = topologySortBFS(orientedGraphCycle);
	cout << "topologySort BFS: ";
	while (!queueNode.empty())
	{
		Node *curr = queueNode.front();
		queueNode.pop();
		cout << curr->_data << "  ";
	}
	cout << endl;

	queue<Node *> queueNodeDFS = topologySortDFS(orientedGraphCycle);
	cout << "topologySort DFS: ";
	while (!queueNodeDFS.empty())
	{
		Node *curr = queueNodeDFS.front();
		queueNodeDFS.pop();
		cout << curr->_data << "  ";
	}
	cout << endl;

	return 0;
}