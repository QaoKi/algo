#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <list>
#include <stack>

#include "../UndirectedGraph/UndirectedGraph.h"
#include "UndirectedGraphCycle.h"
#include "OrientedGraphCycle.h"

using namespace std;

int main()
{

	//https://www.cnblogs.com/tenosdoit/p/3644225.html

	/*
		0->1, 0->2, 0->5 
		1->2
		2->3, 2->4
		3->4, 3->5
	*/
	//建立一个无向的连通图
	// UndirectedGraphCycle UndirectedGraphCycle;
	// UndirectedGraphCycle.addEdge(0, 1);
	// UndirectedGraphCycle.addEdge(0, 2);
	// UndirectedGraphCycle.addEdge(0, 5);
	// UndirectedGraphCycle.addEdge(1, 2);
	// UndirectedGraphCycle.addEdge(2, 3);
	// UndirectedGraphCycle.addEdge(2, 4);
	// UndirectedGraphCycle.addEdge(3, 4);
	// UndirectedGraphCycle.addEdge(3, 5);

	// UndirectedGraphCycle.printAllCycles();

	//建立一个有向图
	OrientedGraphCycle orientedGraphCycle;
	//有环
	// orientedGraphCycle.addEdge(0, 1);
	// orientedGraphCycle.addEdge(1, 2);
	// orientedGraphCycle.addEdge(2, 3);
	// orientedGraphCycle.addEdge(3, 1);

	//无环
	orientedGraphCycle.addEdge(5, 2);
	orientedGraphCycle.addEdge(5, 4);
	orientedGraphCycle.addEdge(3, 2);
	orientedGraphCycle.addEdge(3, 1);
	orientedGraphCycle.addEdge(2, 1);
	orientedGraphCycle.addEdge(4, 1);

	orientedGraphCycle.hasCycle();
	return 0;
}