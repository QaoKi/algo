#include <iostream>
#include <string>
#include <queue>
#include "../Edge.h"
#include "../demo2_DFS/WeightedGraphDFS.h"

using namespace std;

/*
	https://segmentfault.com/a/1190000021555887
	
	prim算法：采用切分定理，核心是贪心算法
	原理：
		设连通无向网为G(V,E)，将顶点集合V分成两个子集合T和T1（切分定理）。
			T：当前生成树顶点集合；
			T1：不属于当前生成树的顶点集合。
		很显然，T∪T1 = V。目标就是让T1集合中的顶点不断加入到T集合中。Prim的具体过程如下：

			1，从连通无向网G中选择一个起始顶点u0，首先将它加入到集合T中（用一个set来表示是否加入了）。
			2，遍历与u0相连接的边，按照权重排序放入优先级队列。
			3，从队列中取出一个权值最小的边e(u0, u1, weigh)
				（这条权重最小的边，意味着目前T1中的所有节点，距离T集合（最小生成树）最近的是 u1节点，距离是 weigh）
			4，检查u1是否已经进入集合T，如果有，跳过这条边，如果没有，将e放入结果集中
			5，将 u1加入到集合T中（set）
			6，遍历与 u1相连接的边，加入到优先级队列中（e再次加进队列也没有关系，从队列取出来的边会在第4步进行判断）
			7，此时的队列中包含了与u0相连接的边和与u1相连接的边，重复第3步操作

			按上面的步骤，直到所有顶点都加入到集合T中，也就意味着所有的顶点都进入了最小生成树。
	重点：
		从优先级队列中取出一条边e(u0, u1, weigh)，意味着目前T1中的所有节点，距离T集合最近的是 u1节点，距离是 weigh，
		将这条边作为最小生成树的一部分放入结果集，u1放入集合T
*/

/*
	prim算法能够计算任意加权无向图的最小生成树。
	复杂度：
		计算含有V个节点和E条边的连通加权无向图，额外空间复杂度为 O(E)
		时间复杂度 ElogE

		算法的瓶颈在于优先队列（堆）的insert()和delMin()，优先队列中最多可能有E条边，所以额外空间复杂度为 O(E)
		堆插入和删除的时间复杂度为O(logE)，因为最多插入E条边和删除E条边，所有时间复杂度为O(ElogE)
		visit()函数遍历节点的边也会消耗时间，但是最多也就遍历E条边，时间就不计了
*/

void visit(WeightedGraphDFS &weightedGraph, Node *node, priority_queue<Edge> &priorityQueue)
{
	//遍历与node节点相连通的所有边，加入到优先级队列中
	for (auto it = weightedGraph._mapWeightedGraph[node].begin(); it != weightedGraph._mapWeightedGraph[node].end(); it++)
	{
		Edge edge(node, it->first, it->second);
		//加入优先级队列
		priorityQueue.push(edge);
	}
}

/*	
前提：
	用 set<Edge> setEdgeResult 作为结果集。
		 不能用set<Node* > 作为结果集，因为最小生成树必然是包含所有的节点，
		 用set<Node *> 里面只含有所有的节点，但并不知道取了哪些边来组成树
	而set中不能直接保存 Edge，因为Edge类重写了 <，将edge对象加入set中时，如果两个edge的_weight相同，
	会被认为是同一个edge，用 multiset<Edge> 的方式
*/
void MST_Prim(WeightedGraphDFS &weightedGraph, int nodeCount, multiset<Edge> &setEdgeResult)
{
	//加入到setNode中的节点，是已经进入集合T的节点
	set<Node *> setNode;
	priority_queue<Edge> priorityQueue;

	//以 root 节点为开始节点，将root加入到集合T中，并将与root节点相连通的边加入优先级队列
	//root节点进入最小生成树
	setNode.insert(weightedGraph._nodeRoot);
	visit(weightedGraph, weightedGraph._nodeRoot, priorityQueue);

	while (!priorityQueue.empty() && setNode.size() < nodeCount)
	{
		//取出一条权重最小的边
		Edge edge = priorityQueue.top();
		priorityQueue.pop();
		/*
			如果这条边的from和to都已经进入了集合T，丢弃，不然会形成环
			算法第四版是判断了from和to两个节点，但其实只判断to节点就可以了
			因为这条边是从最小队列中取出的，而能进入最小队列中的边，边的from节点都是已经进入集合T中的，
			所以from节点肯定已经进入到最小生成树中了，也就是加入到了setNode中，所以不用写的这么繁琐

			不过这么写的话，代码更好理解
		*/
		/*
			算法第四版的写法：
			if (setNode.find(edge._from) != setNode.end() && setNode.find(edge._to) != setNode.end())
				continue;
			//放入结果集
			setEdgeResult.insert(edge);
		
			//这个可以不写的，因为_from肯定在setNode中
			if (setNode.find(edge._from) == setNode.end())
				visit(weightedGraph, edge._from, priorityQueue, setNode);
			
			if (setNode.find(edge._to) == setNode.end())
				visit(weightedGraph, edge._to, priorityQueue, setNode);
		*/

		//如果to节点已经进入了集合T，跳过，不然会形成环
		if (setNode.find(edge._to) != setNode.end())
			continue;
		//这条边放入结果集
		setEdgeResult.insert(edge);
		//to节点是集合T1中距离集合T最近的节点，进入集合T
		setNode.insert(edge._to);
		//把与to连接的边加入优先级队列
		visit(weightedGraph, edge._to, priorityQueue);
	}
}

int main()
{

	/*
		一共四个点1，2，3，4

			2		2
		 --------1-------
		|	   1 |		 |
		|	1	 |	 3	 |
		3------- 2-------4
		|				 |
		-----------------
				4
	*/
	int nodeCount = 4;
	WeightedGraphDFS weightedGraphDFS;
	weightedGraphDFS.addEdge(1, 2, 1);
	weightedGraphDFS.addEdge(1, 3, 2);
	weightedGraphDFS.addEdge(1, 4, 2);
	weightedGraphDFS.addEdge(2, 3, 1);
	weightedGraphDFS.addEdge(2, 4, 3);
	weightedGraphDFS.addEdge(3, 4, 4);

	weightedGraphDFS.printfAllNodes();
	//weightedGraphDFS.printfAllEdge();
	multiset<Edge> setResult;

	MST_Prim(weightedGraphDFS, nodeCount, setResult);
	for (auto it = setResult.begin(); it != setResult.end(); ++it)
		cout << (*it)._from->_data << " to " << (*it)._to->_data << endl;
	return 0;
}