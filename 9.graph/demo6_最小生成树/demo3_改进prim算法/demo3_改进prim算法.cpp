#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>
#include <unordered_set>
#include "../Edge.h"
#include "../demo2_DFS/WeightedGraphDFS.h"
#include "../IndexMinHeap/IndexMinHeap.h"

using namespace std;

/*
	prim算法改进：
	segmentfault.com/a/1190000021555887
	上面讲了两个数组 edgeTo 和 distTo 的具体用法	

思路：
	V集合表示图中所有节点，U集合表示最小生成树的集合，当V中节点都转移到U中，最小生成树完成
	数组 edgeTo[i] = j 表示集合 V 中的节点 i 到集合 U 中的所有节点的距离，最近的是 j节点
	数组 distTo[i] = 100 表示 i 到 j 的权值为100
	只需要在集合 V 中找 distTo[]值最小的顶点即可

先看一个复杂度高的
	V集合表示图中所有节点，U集合表示最小生成树的集合，当V中节点都转移到U中，最小生成树完成
	一个 bool数组s[]，s[i] = true，说明节点i已加入集合U，
	数组 closest[i] = j 表示集合 V 中的节点 i 到集合 U 中的所有节点的距离，最近的是 j节点
	数组 lowcost[i] = 100 表示 i 到 j 的权值为100
	只需要在集合 V 中找lowcost[]值最小的顶点即可
	步骤1，初始化，指定一个节点u，令 U = {u}，并按照u来初始化closest[].lowcost[]和s[]
	步骤2，在V集合中找lowcost最小的节点t,将节点t加入集合U
	步骤3，对集合V-U中的所有顶点j,更新其lowcost[]和closest[]。
		  由于此时t已经是U中的节点，但它和U-V中的一些节点有连接，
		  因此需要更新当它加入U时而引起的连接两个集合的权值最小的边的变化情况，
		  更新公式为：if(c[t][j] < lowcost[j]) {lowcost[j] = c[t][j] ; closest[j] = t;},转步骤2。
	注：lowcost可用优先级队列代替，pair<i, 100>

为什么要使用索引优先队列：之前使用优先级队列，队列中存储的是边，现在用索引优先队列，存储的是节点
*/

/*
	prim算法能够计算任意加权无向图的最小生成树。
	复杂度：
		计算含有V个节点和E条边的连通加权无向图，额外空间复杂度为 O(V)
		时间复杂度 ElogV

		优先队列中，最多会加入V次，所以额外空间复杂度为 O(V)
		会进行V次插入操作，V次删除最小元素的操作和（在最坏情况下）E次改变优先级的操作
		所以时间复杂度为ElogV
*/

/*
	prim算法和kruskal算法
	kruskal算法时间复杂度为 ElogE，改进版的prim算法时间复杂度为 ElogV，边稠密的图，可以用 prim，边稀疏的图可以用 Kruskal算法
*/

void visit(WeightedGraphDFS &weightedGraph, Node *v, IndexMinHeap &indexPQ, set<Node *> &setNode, map<Node *, Node *> &edgeTo, map<Node *, int> &distTo)
{
	//遍历v节点的所有边
	for (auto it = weightedGraph._mapWeightedGraph[v].begin(); it != weightedGraph._mapWeightedGraph[v].end(); it++)
	{
		Node *w = it->first;
		int weight = it->second;
		//已经进入集合U中的节点就不用管了
		if (setNode.find(w) != setNode.end())
			continue;

		if (distTo.find(w) == distTo.end())
		{
			edgeTo[w] = v;
			distTo[w] = weight;
			//记录w节点进入集合U的权重
			indexPQ.insert(w->_data, weight);
		}
		else if (weight < distTo[w])
		{
			//w节点到集合U的最佳边变成  w —— v
			edgeTo[w] = v;
			distTo[w] = weight;
			//改变w节点进入集合U的权重
			indexPQ.change(w->_data, weight);
		}
	}
}

map<Node *, Node *> MST_QuickPrim(WeightedGraphDFS &weightedGraph)
{
	/*
	节点是否已经加入到最小生成树中，这个set是需要的，不然会出错
		比如 e(u0, u1, 10), e1(u1, u2, 5)
		刚开始distTo[u0] = 0,遍历完e后，distTo[u1] = 10，此时u0和u1已经加入到了集合T中，
		接着遍历完e1后，distTo[u2] = 5，u2进入集合T，因为是无向图，当下次遍历到边 e2(u2, u1, 5)的
		时候，此时distTo[u1] = 10，如果不去判断 u1是否已经进入了集合T，
		直接判断 weight < distTo[u1] 的话，会出错，会将distTo[u1]的值改为5，u1会再次加入索引优先队列中
	*/

	set<Node *> setNode;
	//两个数组，最小生成树的结果就放在edgeTo中
	map<Node *, Node *> edgeTo;
	map<Node *, int> distTo;
	/*
		采用索引优先队列，要注意一点，在初始化索引队列的时候，要传入最大的索引值，索引队列用这个值分配内存，
		我们使用图中节点的值作为索引（key），所以要找到图中所有节点的最大值传入
		因为在 insert(key, data)的时候，会让 _value[key] = data，如果初始化的时候传入的值比key小，那么很明显_value数组就越界了
		不用管data的大小，因为另外两个数组，_pq和_qp，都没有接触到data
	*/
	//这个图最大的节点值应该不会超过节点的数量，就懒得计算了
	IndexMinHeap indexPQ(weightedGraph._mapAllNode.size());
	/*
		让 root 节点作为第一个进入集合U的节点
		用节点的值作为key，这样key是唯一的，权重作为数据
	*/
	//因为root节点是第一个进入集合U的，所以它距离集合U的权重为0
	indexPQ.insert(weightedGraph._nodeRoot->_data, 0);

	//因为indexPQ 中最多会放入V个节点，所以不需要使用 while(!indexPQ.isEmpty() && setNode.size() < nodeCount) 来判断结束
	while (!indexPQ.isEmpty())
	{
		//从队列中取一个节点 node，node 存在于集合V中，并且比起集合V中的其他节点，node 到集合U的权重最小
		//朝索引队列中存数据时，节点的值作为key，权重作为value，所以节点的值是 topIndex()的返回值
		//第一个取出来的是root
		int valueData = indexPQ.topIndex();
		indexPQ.pop();
		//根据节点值找到节点指针，这里就不判断_mapAllNode中是否有valueData这个key了
		Node *node = weightedGraph._mapAllNode[valueData];

		//这个节点已经加入到了集合U，就不管了
		if (setNode.find(node) != setNode.end())
			continue;

		//让node进入集合U
		setNode.insert(node);
		visit(weightedGraph, node, indexPQ, setNode, edgeTo, distTo);
	}

	//最小生成树的结果就放在edgeTo中
	return edgeTo;
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
	map<Node *, Node *> edgeTo = MST_QuickPrim(weightedGraphDFS);
	for (auto it = edgeTo.begin(); it != edgeTo.end(); ++it)
		cout << it->first->_data << " to " << it->second->_data << endl;

	return 0;
}