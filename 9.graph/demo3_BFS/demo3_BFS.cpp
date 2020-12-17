#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <list>
#include <stack>

#include "../UndirectedGraph/UndirectedGraph.h"
#include "UndirectedGraphBFS.h"

using namespace std;

/*
	宽度优先(广度优先)：BFS
	某个节点到头节点的最短的距离是几，该节点就是第几层，比如1指向2，指向3，指向4
	2指向5，3指向6
	2	3	4距离头节点1的长度都是1，所以2，3，4是同一层，5，6是同一层
	同一层的节点的打印顺序没有关系
*/

int main()
{

	/*
		0->1, 0->2, 0->5 
		1->2
		2->3, 2->4
		3->4, 3->5
	*/
	//建立一个无向的连通图
	UndirectedGraphBFS UndirectedGraphBFS;
	UndirectedGraphBFS.addEdge(0, 1);
	UndirectedGraphBFS.addEdge(0, 2);
	UndirectedGraphBFS.addEdge(0, 5);
	UndirectedGraphBFS.addEdge(1, 2);
	UndirectedGraphBFS.addEdge(2, 3);
	UndirectedGraphBFS.addEdge(2, 4);
	UndirectedGraphBFS.addEdge(3, 4);
	UndirectedGraphBFS.addEdge(3, 5);

	cout << "BFS: ";
	UndirectedGraphBFS.printf(UndirectedGraphBFS._nodeRoot);
	cout << endl;

	cout << "printf 0 to all paths：";
	UndirectedGraphBFS.printfAllPaths(UndirectedGraphBFS._nodeRoot);

	cout << "printf 2 to all paths：";
	auto start = UndirectedGraphBFS._mapAllNode[2];
	UndirectedGraphBFS.printfAllPaths(start);

	cout << "printf 0 to 3 path：";
	auto endNode = UndirectedGraphBFS._mapAllNode[3];
	UndirectedGraphBFS.printfPathsStartToEnd(UndirectedGraphBFS._nodeRoot, endNode);

	return 0;
}