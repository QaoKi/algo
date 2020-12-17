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
	�������(�������)��BFS
	ĳ���ڵ㵽ͷ�ڵ����̵ľ����Ǽ����ýڵ���ǵڼ��㣬����1ָ��2��ָ��3��ָ��4
	2ָ��5��3ָ��6
	2	3	4����ͷ�ڵ�1�ĳ��ȶ���1������2��3��4��ͬһ�㣬5��6��ͬһ��
	ͬһ��Ľڵ�Ĵ�ӡ˳��û�й�ϵ
*/

int main()
{

	/*
		0->1, 0->2, 0->5 
		1->2
		2->3, 2->4
		3->4, 3->5
	*/
	//����һ���������ͨͼ
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

	cout << "printf 0 to all paths��";
	UndirectedGraphBFS.printfAllPaths(UndirectedGraphBFS._nodeRoot);

	cout << "printf 2 to all paths��";
	auto start = UndirectedGraphBFS._mapAllNode[2];
	UndirectedGraphBFS.printfAllPaths(start);

	cout << "printf 0 to 3 path��";
	auto endNode = UndirectedGraphBFS._mapAllNode[3];
	UndirectedGraphBFS.printfPathsStartToEnd(UndirectedGraphBFS._nodeRoot, endNode);

	return 0;
}