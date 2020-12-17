#include <iostream>
#include <string>
#include <queue>
#include <map>
#include "../../Edge.h"
#include "../../OrientedWeightedGraph/OrientedWeightedGraph.h"
#include "../../IndexMinHeap/IndexMinHeap.h"

using namespace std;

/*
	使用索引优先队列，将时间复杂度降为 ElogV
	使用优先级队列的Dijkstra算法，每次添加到最小路径树上的顶点是当前离树最近的非树顶点，而使用索引优先队列的Dijkstra算法，
	每次添加到树上的顶点，是当前距离起点s最近的顶点。
	使用索引优先队列，顶点的值做key，顶点的distTo值做 value，每次从队列中取出的顶点，它的distTo值是最小的，也就是说这个顶点
	是离起点s最近的
*/

/*
	时间复杂度：和改进的prim算法一样（实现原理都一样），时间复杂度为 O(ElogV)
*/

//查找图中，以s为起点，到其他可达节点的最短路径
void ShortPath(OrientedWeightedGraph &weightedGraph, Node *s, map<Node *, int> &indistTo, map<Node *, Node *> &inedgeTo)
{
	/*
		这个方法不再需要setNode来判断顶点是否已经加入最短路径树，之前判断是怕重复放入数据造成错误，
		但是松弛操作不会，比如遍历到边e(v, w, weigh)，更新distTo[w] = distTo[v] + weigh，将w插入到索引优先队列，
		下次取出顶点w的时候，遍历到边e1(w, v, weigh)，此时 distTo[v]的值肯定是小于distTo[w] + weigh，（除非weigh是负数），
		因为distTo[w]的值，就是distTo[v] + weigh，所以不可能满足松弛操作，所以不需要担心遍历完了一遍e，下次遍历到e1时会出错。
		但是在改进版prim算法中，setNode还是需要的
	*/

	map<Node *, int> distTo;
	map<Node *, Node *> edgeTo;
	IndexMinHeap indexPQ(weightedGraph._mapAllNode.size());

	distTo[s] = 0;
	//顶点的值作为key，顶点的distTo值作为value
	indexPQ.insert(s->_data, distTo[s]);

	while (!indexPQ.isEmpty())
	{
		//朝索引队列中存数据时，节点的值作为key，所以节点的值是 topIndex()的返回值（key）
		int nodeData = indexPQ.topIndex();
		indexPQ.pop();
		//根据节点值找到节点指针，这里就不判断_mapAllNode中是否有nodeData这个key了
		Node *node = weightedGraph._mapAllNode[nodeData];

		/*
			从队列中取出来的顶点 v，是当前队列的所有顶点中 distTo值最小的，也就是离起点s最近的顶点，distTo[v]这个值，不会再
			改变了，在之后遍历其他有效边的时候也不会再改变
			取出来后默认是加到了集合T中，如果有setNode的话，这里就将node节点放进去
		*/
		//遍历和node连通的所有边，进行松弛操作，更新两个数组
		for (auto it = weightedGraph._mapOrientedWeightedGraph[node].begin(); it != weightedGraph._mapOrientedWeightedGraph[node].end(); it++)
		{
			//组成边（不组也行，只是为了代码更加形象）
			Edge edge(node, it->first, it->second);
			//进行松弛操作
			if (distTo.find(edge._to) == distTo.end() || distTo[edge._to] > distTo[edge._from] + edge._weight)
			{
				distTo[edge._to] = distTo[edge._from] + edge._weight;
				edgeTo[edge._to] = edge._from;

				//change函数会判断，如果不存在就插入
				indexPQ.change(edge._to->_data, distTo[edge._to]);
			}
		}
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