#include <iostream>
#include <string>
#include <queue>
#include <map>
#include "../../Edge.h"
#include "../../OrientedWeightedGraph/OrientedWeightedGraph.h"

using namespace std;

/*
	Bellman-Ford算法：单点最短路径算法，图中不能有负权环，可以有负权边。有向无向都可以

	实现：将distTo[s]初始化为0，其他distTo[]初始化为无穷大，以任意顺序放松图中的所有边，
		重复 V - 1 轮，每一轮都将图中所有的边进行松弛操作。V是图中顶点个数

	原理：这个方法和我在demo2_dijkstra算法中想到的另一种思路相似，当时也想的是遍历所有的边，进行松弛操作，不采用优先级队列，
		但是遍历的顺序会导致出错，现在有了解决方案，就是放松 V - 1 次所有的边
	
	伪代码：
		//执行V - 1轮
		for(int i = 0; i < graph._mapAllNode.size() - 1; i++) {
			//每一轮都放松所有的边
			for(auto it = graph._mapAllNode.begin(); it != graph._mapAllNode.end(); it++) {
				//第二层for循环是每次取一个顶点，第三层循环是遍历这个顶点指向的所有边
				Node* node = it->second;
				for(auto it = graph._mapGrapg[node].begin(); it != graph._mapGrapg[node].end(); it++) {
					Edge e(node, *it);
					relax(e);
				}
			}
		}
	算法证明：数学归纳法，算法第四版 p436
			起点s到其他顶点的最短路径最多包括V ? 1条边.因此最多经过V ? 1 V-1V?1轮松弛, 
			顶点s到其余顶点的最短路径便可搜索得到
	
	继续优化：SPFA算法
		根据经验我们知道，在任意一轮中许多边的放松不会都成功：只有上一轮中的distTo[]值发生变化的顶点指出的边才能够改变其他
		顶点distTo[]的值，采用一个queue，记录在这一轮distTo[]值改变了的节点，每一轮不再放松图中所有的边，而是从队列中取
		出上一轮distTo[]值改变了的顶点，放松这些顶点所指向的边，初始化时让顶点s进入队列。直到队列为空，或者检测到图中有负权环时，结束。
		也就是说，每轮只放松上一轮distTo[]值改变了的顶点所指向的边，而不是图中所有的边。
		比如，初始时队列中只有顶点s，取出s，放松s所指向的所有边，比如 e(s, a, weigh), e1(s, b, weigh)，
		并把松弛成功的边的to节点加入到队列中（松弛成功，意味着distTo[]值改变了），初始时distTo[a]和distTo[b]都为无穷大，
		肯定松弛成功，a和b进入队列。这一轮结束，下一轮取出队列中的a和b，放松a和b指出的所有边，并将松弛成功的边的to节点加入到
		队列中...
		
		重点：改变了edgeTo[]和distTo[]的值的所有顶点都会在下一轮中处理
			使用了队列优化的Bellamn_ford算法叫做SPFA算法
	
	检测图中是否有负权环
		当进行了V轮后（调用了V次realx()），如果发现队列不为空，那说明图中存在从起点可达的负权环（从起点可达这点也挺重要），
		如果是这样，那么edgeTo[]数组所表达的子图中必然含有这个负权重环，可以根据 edgeTo[]数组来构建一幅图检测是否有环。
		或者遍历从s可达的顶点在edgeTo[]中的路径，如果不能回到起点s，那说明这个顶点就在负权重上
*/

/*
	空间复杂度：O(V)
	时间复杂度：最坏情况下，在每一轮都放会放松E条边，共V轮，所以时间复杂度 O(EV)
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