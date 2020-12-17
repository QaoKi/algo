#include <iostream>
#include <string>
#include <set>
#include <queue>
#include "../UnionFind/UnionFind.h"
#include "../Edge.h"
#include "../demo2_DFS/WeightedGraphDFS.h"
using namespace std;

/*
	最小生成树：有权的无向连通图
		在保证图中节点都连通的情况下，权重最小的边的集合。
		最小生成树是一颗树，不包含环，所以包含全部v个节点，有v-1条边
		假设处理的图都是连通图，如果不是连通图，最小生成树不止一棵树
	比如：
		   2
		A----B
		|	 |
	  3	|	 |100
		|	 |
		C---->D
		   5
		因为是无向图，所以去掉权重为100那条边，图中的节点依然是连通的
		则权重为2，3，5的边，是最小生成树的集合
*/

/*
	kruskal算法：
		将每个节点都看做是只有一个节点的树，不断的取最小权重的边，将树不断的合并，最终只剩一棵树时，就是最小生成树

			2		2
		 --------A-------
		|	   1 |		 |
		|	1	 |	 3	 |
		E------- C-------F	
		|				|
		-----------------
				4

	思路：
		用一个并查集来判断是否形成了环，刚开始把图中每个节点都作为一个小集合加入到并查集中
		  比如ACEF，4个节点作为四个集合加入到并查集中。
		  再把每条边放入一个优先级队列中，按照边的权重，从小到大排序，每次取出队列头（权重最小的边）
		  判断这条边的from和to点是否属于同一个集合
		  如果不在同一个集合，这条边保存，并把from和to集合合并
		  如果在同一个集合，会构成回路，不要这条边
		  比如首先取出A到C的边，把AC集合合并，再取出C到E的边，把CE集合合并，此时ACE就处于同一个集合总了，
		  再取出A到E的边，检测发现A和E在同一个集合，不要这条边

		  不可以用集合set来判断是否形成了环，会出现错误判断
*/

/*
	kruskal算法能够计算任意加权无向图的最小生成树。
	复杂度：
		额外空间复杂度为 O(E + V)
		时间复杂度为 O(ElogE) （最坏情况下）

	优先级队列，最多保存E条边，并查集最多保存V个节点，所以额外空间复杂度为O(E + V)

	时间成本主要还是在优先级队列的插入和删除中，每次插入、删除时间复杂度为 logE，
	最多插入和删除E条边，所以时间复杂度为 ElogE
	并查集的构建和 unionSet 也需要时间，但是都是常数级别，忽略不计

*/

void MST_kruskal(WeightedGraphDFS &weightedGraph, multiset<Edge> &setResult)
{
	vector<Node *> vectorNode;
	for (auto it = weightedGraph._mapAllNode.begin(); it != weightedGraph._mapAllNode.end(); it++)
		vectorNode.push_back(it->second);

	//用图的所有节点，构建一个并查集，刚开始时，每个节点都是一个独立的集合
	UnionFind unionFind(vectorNode);

	multiset<Edge> setAllEdge;
	weightedGraph.printfAllEdge(setAllEdge);
	//构建一个以边的权重为排序大小的小根堆
	priority_queue<Edge> priorityQueue;
	for (auto it = setAllEdge.begin(); it != setAllEdge.end(); ++it)
		priorityQueue.push(*it);

	//最小生成树，有V个节点，有V-1条边
	while (!priorityQueue.empty() && setResult.size() < weightedGraph._mapAllNode.size() - 1)
	{
		//每次取一个权重最小的边
		Edge edge = priorityQueue.top();
		priorityQueue.pop();

		//判断这条边的from和to点是否属于同一个集合
		//如果在同一个集合，会构成回路，不要这条边
		if (unionFind.isSameSet(edge._from, edge._to))
			continue;
		//如果不在同一个集合，这条边保存，并把from和to集合合并
		setResult.insert(edge);
		unionFind.unionSet(edge._from, edge._to);
	}
}

int main()
{
	/*
		一共四个点1，2，3，4

			2		6
		 --------1-------
		|	   1 |		 |
		|	4	 |	 5	 |
		3------- 2-------4
		|				 |
		-----------------
				3
	*/
	WeightedGraphDFS weightedGraphDFS;
	weightedGraphDFS.addEdge(1, 2, 1);
	weightedGraphDFS.addEdge(1, 3, 2);
	weightedGraphDFS.addEdge(1, 4, 6);
	weightedGraphDFS.addEdge(2, 3, 4);
	weightedGraphDFS.addEdge(2, 4, 5);
	weightedGraphDFS.addEdge(3, 4, 3);

	weightedGraphDFS.printfAllNodes();
	multiset<Edge> setResult;

	MST_kruskal(weightedGraphDFS, setResult);
	for (auto it = setResult.begin(); it != setResult.end(); ++it)
		cout << (*it)._from->_data << " to " << (*it)._to->_data << endl;
	return 0;

	/*
	附上java代码

		public static Set<Edge> kruskalMST(Graph graph) {
		UnionFind unionFind = new UnionFind();
		unionFind.makeSets(graph.nodes.values());
		PriorityQueue<Edge> priorityQueue = new PriorityQueue<>(new EdgeComparator());
		for (Edge edge : graph.edges) {
			priorityQueue.add(edge);
		}
		Set<Edge> result = new HashSet<>();
		while (!priorityQueue.isEmpty()) {
			Edge edge = priorityQueue.poll();
			if (!unionFind.isSameSet(edge.from, edge.to)) {
				result.add(edge);
				unionFind.union(edge.from, edge.to);
			}
		}
		return result;
	}
	
	
	*/
	return 0;
}