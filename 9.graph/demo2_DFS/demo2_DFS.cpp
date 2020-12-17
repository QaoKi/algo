#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <list>
#include <stack>

#include "UndirectedGraphDFS.h"

using namespace std;

/*
	深度优先遍历：DFS
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
	UndirectedGraphDFS UndirectedGraphDFS;
	UndirectedGraphDFS.addEdge(0, 1);
	UndirectedGraphDFS.addEdge(0, 2);
	UndirectedGraphDFS.addEdge(0, 5);
	UndirectedGraphDFS.addEdge(1, 2);
	UndirectedGraphDFS.addEdge(2, 3);
	UndirectedGraphDFS.addEdge(2, 4);
	UndirectedGraphDFS.addEdge(3, 4);
	UndirectedGraphDFS.addEdge(3, 5);

	cout << "DFS: ";
	UndirectedGraphDFS.printf();
	cout << endl;

	cout << "DFS not recursion：";
	UndirectedGraphDFS.printf_noRecursion();
	cout << endl;

	cout << "printf 0 to all paths：";
	UndirectedGraphDFS.printfAllPaths(UndirectedGraphDFS._nodeRoot);

	cout << "printf 2 to all paths：";
	auto start = UndirectedGraphDFS._mapAllNode[2];
	UndirectedGraphDFS.printfAllPaths(start);

	cout << "printf 0 to 3 path：";
	auto endNode = UndirectedGraphDFS._mapAllNode[3];
	UndirectedGraphDFS.printfPathsStartToEnd(UndirectedGraphDFS._nodeRoot, endNode);

	return 0;
}