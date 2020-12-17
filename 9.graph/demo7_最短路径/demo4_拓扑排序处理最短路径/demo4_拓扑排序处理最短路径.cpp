#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include "../../Edge.h"
#include "../../OrientedWeightedGraph/OrientedWeightedGraph.h"

using namespace std;

/*
	拓扑排序的前提是无环有向图，所以这种方式适合无环有向图，拓扑排序是从无环有向图中入度为0的顶点开始的，
	虽然给定的顶点s不一定是入度为0的顶点，但是不妨碍求出图中从s出发，可到达的顶点的最短路径。
	并且不受负权边的影响

	原理：
		先了解一个概念：顶点的放松（采用了边的松弛），遍历顶点指向的所有边，进行松弛操作
			void relax(Graph G, Node v) {
				for(Edge e : G.AllEdge(v)) {	//遍历v指向的所有边
					if(distTo[e.to] < distTo[e.from] + e.weigh) {
						distTo[e.to] = distTo[e.from] + e.weigh;
						edgeTo[e.to] = e.from;
					}
				}	
			}
		再来了解下拓扑排序：
			拓扑排序，优先级高的顶点排在前面（优先级高是指需要先被执行的顶点），拓扑排序的前提是无环有向图，
			因为无环，所以肯定有一个入度为0的顶点，只有执行完这个顶点后才能执行下一个顶点
			（执行是抽象的说法，比如B文件依赖于A文件，那么只有先编译了文件A，才能再编译文件B，在图中的关系就是A指向B）
	实现：
		对图进行拓扑排序，将图中顶点按照执行的优先级排序，比如得到 s a v w t，s是入度为0的顶点，a依赖s，v依赖a
		按照这个顺序，对顶点进行顶点放松，当顶点被放松以后，顶点就进入了最小路径树，当所有顶点都被放松完，结束。

	重点：1，顶点被放松以后，比如 v被放松以后，distTo[v]的值不会再改变，因为在v被放松以后，之后的算法不会再处理任何指向v的边,
		 v被放松的前提是指向v的节点都已经被放松了，也就是说v所依赖的顶点a和s都已经被放松了（意味着顶点a和s指向v的边已经被松弛了）。
		 所以既然v能被放松，那说明指向v的边已经都被处理了。v被放松以后，之后不会再遍历到指向v的边了。
		 2，拓扑排序是从无环有向图中入度为0的顶点开始的，这个点不一定是指定的起点s，程序刚开始的时候，初始化 distTo[s] = 0;
		   在对顶点进行放松的时候，检查 distTo[e.from]是否存在，如果不存在，说明s不能指向这个顶点，也就不用再处理了
		   比如拓扑排序以后，顶点为 a, b, c, s, d, e, f，首先放松a，发现没有distTo[a]，说明s不能指向a，a也就不用再处理了

	总结：
		1，适合无环有向图
		2，能够处理负权边
*/

/*
	时间复杂度：拓扑排序时间复杂度为 O(E + V)，再遍历一遍所有的顶点，每条边都只会被松弛一次
		所以总的时间复杂度为 O(E + V)
*/

void dfsHelp(OrientedWeightedGraph &weightedGraph, Node *node, set<Node *> &setNode, stack<Node *> &stackNode)
{
	//node节点变为灰色
	setNode.insert(node);
	//遍历节点的所有边
	for (auto it = weightedGraph._mapOrientedWeightedGraph[node].begin(); it != weightedGraph._mapOrientedWeightedGraph[node].end(); it++)
	{
		if (setNode.find(it->first) == setNode.end())
		{
			dfsHelp(weightedGraph, it->first, setNode, stackNode);
		}
	}

	//node节点指向的所有节点都被遍历完，node节点变为黑色，加入栈中
	stackNode.push(node);
}

queue<Node *> topologySort(OrientedWeightedGraph &weightedGraph)
{
	//记录节点的访问状态
	set<Node *> setNode;
	//用栈保存结果的倒序
	stack<Node *> stackNode;

	//DFS遍历所有节点
	for (auto it = weightedGraph._mapAllNode.begin(); it != weightedGraph._mapAllNode.end(); it++)
	{
		//之前没有遍历过
		if (setNode.find(it->second) == setNode.end())
		{
			dfsHelp(weightedGraph, it->second, setNode, stackNode);
		}
	}

	//将栈倒序，取出结果返回
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
		检查是否有distTo[node]，如果没有，说明distTo[node]是无穷大，从顶点s不能达到node，那么node就不做处理了
		因为我们要求的，是从s出发，可达到的顶点的最短路径，所以在初始化的时候，只初始化了 distTo[s] = 0;
		只有node为s的时候，才会开始松弛操作
	*/
	if (distTo.find(node) == distTo.end())
		return;
	for (auto it = weightedGraph._mapOrientedWeightedGraph[node].begin(); it != weightedGraph._mapOrientedWeightedGraph[node].end(); it++)
	{
		//组成边（不组也行，只是为了代码更加形象）
		Edge edge(node, it->first, it->second);
		//进行松弛操作
		if (distTo.find(edge._to) == distTo.end() || distTo[edge._to] > distTo[edge._from] + edge._weight)
		{
			distTo[edge._to] = distTo[edge._from] + edge._weight;
			edgeTo[edge._to] = edge._from;
		}
	}
}

void ShortPath(OrientedWeightedGraph &weightedGraph, Node *s, map<Node *, int> &indistTo, map<Node *, Node *> &inedgeTo)
{

	//拓扑排序，将图中顶点按照执行的优先级排序
	queue<Node *> queueNode = topologySort(weightedGraph);
	map<Node *, int> distTo;
	map<Node *, Node *> edgeTo;

	//初始化起点的distTo值
	distTo[s] = 0;

	//从队列中取出顶点进行顶点的放松
	while (!queueNode.empty())
	{
		Node *node = queueNode.front();
		queueNode.pop();
		cout << "get node[" << node->_data << "]" << endl;
		//顶点的松弛
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

	//输出结果
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