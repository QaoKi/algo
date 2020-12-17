#include <iostream>
#include <string>
#include <queue>
#include "../UndirectedGraph/UndirectedGraph.h"
#include "../OrientedGraph/OrientedGraph.h"
#include "../WeightedGraph/WeightedGraph.h"
//#include "../Graph/Graph.h"

using namespace std;

/*
	图：
			a ——> b  有向图，表示a指向b
			a —— b   无向图，表示a指向b，b也指向a
			
			   3
			a —— b   带权图
	图的表示方式：
		1，邻接表法：			
			比如有一个图：无向图：
			1 —— 2 —— 3 —— 5
				|
			   	4

			1：2			1指向2
			2：1——>3——>4	2指向1和3，4
			3：2——>5		3指向2和5
			4：2			4指向2
			5：3			5指向3
			
			链表可以用红黑树或者调表替换，这样查找起来快
		2，邻接矩阵法：

			  3   2   4	
			1——>2——>3 ——>1

			如果图中有权重，比如1指向2的代价是3，2指向3的代价是2，3指向1的代价是4
			2不指向1，所以2指向1的代价就是无穷大，用&表示
				1	2	3
			1	0	3	5	
			2	&	0	2
			3	4	&	0

		3，数组矩阵表示：
			[
				[1,2,5]	1指向2，权重为5
				[1,3,3]	1指向3，权重为3
				[2,3,5]	2指向3，权重为5
			]

	连通图：图上的一个顶点到任意其他一个顶点，都有路径可达到
*/
int main()
{
	/*
		节点和边都单独定义
		int arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
		Graph *graph = new Graph();
		graph->GetGraph(arr);
	*/

	UndirectedGraph undirectedGraph;
	undirectedGraph.addEdge(1, 2);
	undirectedGraph.addEdge(2, 3);

	OrientedGraph orientedGraph;
	orientedGraph.addEdge(3, 4);
	orientedGraph.addEdge(5, 6);

	WeightedGraph weightedGraph;
	weightedGraph.addEdge(7, 8, 1);
	weightedGraph.addEdge(8, 9, 2);

	return 0;
}