#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include "../../Edge.h"
#include "../../OrientedWeightedGraph/OrientedWeightedGraph.h"

using namespace std;

/*
	无环有向图中的单点最长路径：给定一个无环加权有向图（边的权重可能为负），和一个起点s，找到从s到其他可达顶点的
	最长路径。

	实现：
		将demo4中最短路径问题，改为最长问题，将relax()函数中 的 < 改为 >
	总结：
		在一般的加权有向图（边的权重可能为负）中寻找最长路径的已知最好算法在最坏情况下所需的时间是指数级别的
*/

/*
	还能解决平行任务调度问题，算法第四版（p430）
*/

/*
	时间复杂度：拓扑排序时间复杂度为 O(E + V)，再遍历一遍所有的顶点，每条边都只会被松弛一次
		所以总的时间复杂度为 O(E + V)
*/

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
		if (distTo.find(edge._to) == distTo.end() || distTo[edge._to] < distTo[edge._from] + edge._weight)
		{
			distTo[edge._to] = distTo[edge._from] + edge._weight;
			edgeTo[edge._to] = edge._from;
		}
	}
}