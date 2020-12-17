#include <iostream>
#include <string>
#include <queue>
#include <map>
#include "../../Edge.h"
#include "../../OrientedWeightedGraph/OrientedWeightedGraph.h"

using namespace std;

/*
	Floyd算法：多源最短路径算法
	

*/

/*
	时间复杂度：O(V^3)，效率比执行V次Dijkstra算法要高（Dijkstra一次只能求出一个顶点到其他顶点的最短路径），V是顶点数量
*/

void findNegativeClcle(OrientedWeightedGraph &weightedGraph, Node *s, map<Node *, Node *> &edgeTo, bool &hasNegativeClcle)
{
	cout << "start find clcle" << endl;

	for (auto it = weightedGraph._mapAllNode.begin(); it != weightedGraph._mapAllNode.end(); it++)
	{
		/*
			参见demo_4检测环的 OrientedGraphCycle
			将访问到的节点依次压入栈中，如果顶点在环上，或者顶点的 edgeTo[]在环上，那么一定会重新遍历到已入栈的顶点
			注意：不能用下面的写法：
				  Node* self = it->second;
				  Node *curr = it->second;
				  while (edgeTo.find(curr) != edgeTo.end())
				  {
					curr = edgeTo[curr];
					//如果转了一圈又回到自己了，说明在环上
					if (curr == self){}
				  }
				这种写法，如果 self 顶点在环上，是可以检测出来，但是如果self不在环上，
				但是 edgeTo[self]在环上，或者edgeTo[edgeTo[self]] 在环上，那么就在while循环里出不来了
		*/

		Node *curr = it->second;
		//用set来代替栈，也可以用map<Node, bool>
		set<Node *> setNodeInStack;
		setNodeInStack.insert(curr);
		while (edgeTo.find(curr) != edgeTo.end())
		{
			setNodeInStack.insert(curr);
			curr = edgeTo[curr];
			if (setNodeInStack.find(curr) != setNodeInStack.end())
			{
				//有环
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
	//松弛 node 指向的所有边
	for (auto it = weightedGraph._mapOrientedWeightedGraph[node].begin(); it != weightedGraph._mapOrientedWeightedGraph[node].end(); it++)
	{
		//组成边（不组也行，只是为了代码更加形象）
		Edge edge(node, it->first, it->second);
		//进行松弛操作，只有松弛成功才能进入队列
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
			判断有环1。
			每次遍历了V条边以后，检测是否有环，不知道为什么在这判断，
			在这判断的话，能更快速的发现是否有环，但是会多走几遍 findNegativeClcle()
		*/
		if (count++ % weightedGraph._mapAllNode.size() == 0)
		{
			findNegativeClcle(weightedGraph, s, edgeTo, hasNegativeClcle);
		}
	}
}

//查找图中，以s为起点，到其他可达节点的最短路径
bool ShortPath(OrientedWeightedGraph &weightedGraph, Node *s, map<Node *, int> &indistTo, map<Node *, Node *> &inedgeTo)
{

	map<Node *, int> distTo;
	map<Node *, Node *> edgeTo;
	//在这一轮被放松的节点
	queue<Node *> queueNode;
	//检查顶点是否已经进入队列，防止重复加入队列中
	map<Node *, bool> mapNodeJoinQueue;

	//初始化
	distTo[s] = 0;
	queueNode.push(s);
	mapNodeJoinQueue[s] = true;

	//当遍历了
	int count = 0;
	bool hasNegativeClcle = false;
	while (!queueNode.empty() && !hasNegativeClcle)
	{
		Node *node = queueNode.front();
		queueNode.pop();
		mapNodeJoinQueue[node] = false;
		//放松顶点
		relax(weightedGraph, node, s, mapNodeJoinQueue, queueNode, distTo, edgeTo, count, hasNegativeClcle);

		/*
			判断有环2。
			或者在这判断是否有环，在这判断话，findNegativeClcle()会少走几遍，但是relax()会多走几遍
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
		//没有负权重环时输出结果
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