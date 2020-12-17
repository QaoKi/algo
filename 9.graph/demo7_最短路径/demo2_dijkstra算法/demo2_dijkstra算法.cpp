#include <iostream>
#include <string>
#include <queue>
#include <map>
#include "../../Edge.h"
#include "../../OrientedWeightedGraph/OrientedWeightedGraph.h"

using namespace std;

/*
	dijkstra算法，适合非负权重图（权重不能为负，因为核心是松弛操作，有负权值会出错），能解决单源最短路径问题

	题目：给定一个有权图（有向无向都可以，这里使用了有向图），给定一个起点s，求出节点s到其他可到达节点的最短路径

	思路：以s为起点，到其他可达节点的最短路径，是可以组成一颗最短路径树的。
			和 prim算法实现类似，将顶点集合V分成两个子集合T和T1，
			T：已经求出最短路径的顶点集合（节点进入了最短路径树）
			T1：还未求出最短路径的顶点集合（节点还没有进入最短路径树）。

		    不断的将T1中的顶点放入到T中，Prim算法每次添加的都是离树最近的非树顶点，使用优先级队列的Dijkstra算法每次添加到
			最小路径树上的节点也是当前离树最近的非树顶点

	实现：
		1，借助两个数组:
			distTo[w] = 100，w 距离 s的长度是 100（从s到w，整个路径的权重是100），初始化时，让distTo数组的值都为无穷大
			edgeTo[w] = v，从s到w的最短路径，最后一条边是 v——w，初始化时，让edgeTo数组的值都为NULL
		1，让distTo[s] = 0, edgeTo[s] = NULL，让s节点进入集合T中（用一个set来表示是否加入了）
		2，遍历与s相连接的边，按照权重排序放入优先级队列。
		3，从队列中取出一个权值最小的边e(s, v, weigh)
			（这条权重最小的边，意味着目前T1中的所有节点，距离最短路径树最近的是 v节点，距离是 weigh）
		4，检查v 是否已经进入集合T，如果有，跳过这条边，如果没有，更新distTo和edgeTo
			如何更新 distTo和edgeTo？
				松弛操作：（尝试找出更短的最短路径）
					遍历边 e 时
					if(distTo[e.to] > distTo[e.from] + e.weigh) {
						distTo[e.to] = distTo[e.from] + e.weigh;
						edgeTo[e.to] = e.from;
					}

			第一次从队列中取出来边时，distTo[v]为无穷大，那么这条边肯定满足松弛操纵，更新两个数组
		5，（从优先级队列中取出来，意味着s到v的最短路径已经找到了），v直接进入集合T
		6，遍历与 v相连接的边，加入到优先级队列中（e再次加进队列也没有关系，从队列取出来的边会在第4步进行判断）
		7，此时的队列中包含了与s相连接的边和与v相连接的边，重复第3步操作

		按上面的步骤，知道所有顶点都加入到集合T中，也就意味着所有的顶点都进入了最小路径树。

	重点：
		Dijkstra算法和Prim实现类似，Prim算法每次添加的都是离树最近的非树顶点，使用优先级队列的Dijkstra算法每次添加到
		最小路径树上的节点也是当前离树最近的非树顶点

*/

/*
	总结：
		还有一种思路，不采用优先级队列，而是遍历所有的边，进行松弛操作。但是先遍历哪个节点和后遍历哪个节点是
		不能控制的，这样就导致 distTo 数组数据不对，从而影响结果，如果想先遍历s，第二次遍历和s直接相连的节点w，第三次遍历
		和v直接相连的节点v，但是如果v没有出度，那么就不能在遍历完其他节点前遍历v节点，就要回溯到w节点，带来更多的麻烦
*/

/*
	时间复杂度：和prim算法一样（实现原理都一样），时间复杂度为 O(ElogE)
*/

void visit(OrientedWeightedGraph &weightedGraph, Node *node, priority_queue<Edge> &pq)
{
	//遍历和node连通的所有边
	for (auto it = weightedGraph._mapOrientedWeightedGraph[node].begin(); it != weightedGraph._mapOrientedWeightedGraph[node].end(); it++)
	{
		//组成边，加入优先级队列
		Edge edge(node, it->first, it->second);
		pq.push(edge);
	}
}

//查找图中，以s为起点，到其他可达节点的最短路径
void ShortPath(OrientedWeightedGraph &weightedGraph, Node *s, map<Node *, int> &indistTo, map<Node *, Node *> &inedgeTo)
{
	//已经找到最短路径的节点
	set<Node *> setNode;

	// <w, 100>	从 s节点到w节点的最短路径，总权重为100
	map<Node *, int> distTo;
	/*
		<w, v> 从 s节点到w节点的最短路径，最后一条边是 v——w
		同时 edgeTo 也是结果集，最短路径为 edgeTo[w] 倒序
		也可以用 map<Node *, Edge>，一样的
	*/
	map<Node *, Node *> edgeTo;

	//初始化时，应该让 distTo 值为无穷大，edgeTo值为null，这里采用了map，if(find() == end())，说明不存在
	//让distTo[s] = 0, edgeTo[s]就不设为NULL了，if(edgeTo.find(s) == edgeTo.end())，类似于 edgeTo[s] = NULL
	distTo[s] = 0;
	//s节点的最短路径已经找到
	setNode.insert(s);

	priority_queue<Edge> pq;
	visit(weightedGraph, s, pq);

	while (!pq.empty() && setNode.size() < weightedGraph._mapAllNode.size())
	{
		Edge edge = pq.top();
		pq.pop();

		//这个to节点的最短路径已经找到了，跳过
		if (setNode.find(edge._to) != setNode.end())
			continue;

		//进行松弛操作
		if (distTo.find(edge._to) == distTo.end() || distTo[edge._to] > distTo[edge._from] + edge._weight)
		{
			/*
				if (distTo.find(edge._to) == distTo.end())
					distTo中没找到edge._to，类似于 distTo[to] 等于无穷大，那么肯定大于 distTo[edge._from] + edge._weight
			*/
			distTo[edge._to] = distTo[edge._from] + edge._weight;
			//沿着 edge._from——edge._to 这条边过来的
			edgeTo[edge._to] = edge._from;
		}

		//边从优先队列中取出，意味着边的to节点的最短路径已经找到
		setNode.insert(edge._to);
		//再遍历to节点
		visit(weightedGraph, edge._to, pq);
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
	weightedGraph.addEdge(3, 4, 100);
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