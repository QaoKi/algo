#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <stack>
#include "../demo4_检测环/OrientedGraphCycle.h"

using namespace std;

/*
	拓扑排序算法 
		条件：1，有向图，
			 2，没有环

	拓扑排序的使用场景：
		1.任务调度优先级：
		比如编译文件，A文件依赖于B,C,D文件，D文件依赖于E文件，B文件依赖于E文件和C文件
		要想生存A文件，需要先生成BCD，要生成B，需要先生成EC，要生成D，需要先生成E
		所以第一步应该先生成E和C，然后生成BD，最后生成A

		不能出现循环依赖，比如A依赖B，B依赖C，C又依赖A，所以，图不能有环

		用图表示就是：
			E指向B，D
			C指向B，A
			B指向A
			D指向A
*/

/*
	BFS:
		在图中，入度为0的节点，不依赖其他节点，可以先被生成：E和C
		然后删掉这些节点，删掉EC以后的图，入度变为0的节点，就是下一次被生成的：B和D
		。。。
		时间复杂度：O(E + V)
	DFS:
		有向无环图的逆后序就是拓扑排序
		在dfs遍历节点的时候，使用一个栈，当某节点指向的所有节点都遍历完，
		也就是 demo4中无向图检测环中，节点变为黑色以后，将节点加入栈中，优先级最低的最先入栈，优先级最高的最后入栈
		复杂度为O(E + V)
*/

queue<Node *> topologySortBFS(OrientedGraphCycle &orientedGraphCycle)
{
	queue<Node *> queueResult;

	//保存每个节点的入度为多少，做一份记录
	map<Node *, int> mapNodeInDegree;
	//保存入度为0的节点
	queue<Node *> queueZeroInDegree;

	//遍历图中所有节点
	auto it = orientedGraphCycle._mapAllNode.begin();
	for (; it != orientedGraphCycle._mapAllNode.end(); ++it)
	{
		mapNodeInDegree[it->second] = orientedGraphCycle._mapNegativeOriented[it->second].size();
		if (mapNodeInDegree[it->second] == 0)
			queueZeroInDegree.push(it->second);
	}

	//到此时，所有节点的入度都记录在map中，入度为0的节点都记录在queue中
	//有向无环图，肯定有入度为0的节点，如果没有，说明有环
	while (!queueZeroInDegree.empty())
	{
		//从队列中弹出一个节点
		Node *curr = queueZeroInDegree.front();
		queueZeroInDegree.pop();
		queueResult.push(curr);
		//遍历这个节点所指向的节点，将这些节点的入度减1，如果减1之后变为0，则加入队列中
		for (set<Node *>::iterator it = orientedGraphCycle._mapOrientedGraph[curr].begin(); it != orientedGraphCycle._mapOrientedGraph[curr].end(); ++it)
		{
			mapNodeInDegree[*it]--;
			if (mapNodeInDegree[*it] == 0)
				queueZeroInDegree.push(*it);
		}
	}

	//如果所有的节点，都进入了结果集，说明无环，否则，说明有环
	if (orientedGraphCycle._mapAllNode.size() == queueZeroInDegree.size())
		cout << "无环" << endl;

	return queueResult;
}

void dfsHelp(OrientedGraphCycle &orientedGraphCycle, Node *node, set<Node *> &setNode, stack<Node *> &stackNode)
{
	//node节点变为灰色
	setNode.insert(node);
	//遍历 node节点指向的所有节点
	for (auto it = orientedGraphCycle._mapOrientedGraph[node].begin(); it != orientedGraphCycle._mapOrientedGraph[node].end(); ++it)
	{
		if (setNode.find(*it) == setNode.end())
			dfsHelp(orientedGraphCycle, *it, setNode, stackNode);
	}

	//node节点指向的所有节点都被遍历完，node节点变为黑色，加入栈中
	stackNode.push(node);
}

queue<Node *> topologySortDFS(OrientedGraphCycle &orientedGraphCycle)
{
	set<Node *> setNode;
	//使用一个栈，存放结果
	stack<Node *> stackNode;
	for (auto it = orientedGraphCycle._mapAllNode.begin(); it != orientedGraphCycle._mapAllNode.end(); ++it)
	{
		if (setNode.find(it->second) == setNode.end())
			dfsHelp(orientedGraphCycle, it->second, setNode, stackNode);
	}

	//将栈中的数据取出放入结果队列中
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
	//建立一个有向图
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