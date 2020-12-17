#include <iostream>
#include <string>
#include <queue>
#include "../UndirectedGraph/UndirectedGraph.h"
#include "../OrientedGraph/OrientedGraph.h"
#include "../WeightedGraph/WeightedGraph.h"
//#include "../Graph/Graph.h"

using namespace std;

/*
	ͼ��
			a ����> b  ����ͼ����ʾaָ��b
			a ���� b   ����ͼ����ʾaָ��b��bҲָ��a
			
			   3
			a ���� b   ��Ȩͼ
	ͼ�ı�ʾ��ʽ��
		1���ڽӱ���			
			������һ��ͼ������ͼ��
			1 ���� 2 ���� 3 ���� 5
				|
			   	4

			1��2			1ָ��2
			2��1����>3����>4	2ָ��1��3��4
			3��2����>5		3ָ��2��5
			4��2			4ָ��2
			5��3			5ָ��3
			
			��������ú�������ߵ����滻����������������
		2���ڽӾ��󷨣�

			  3   2   4	
			1����>2����>3 ����>1

			���ͼ����Ȩ�أ�����1ָ��2�Ĵ�����3��2ָ��3�Ĵ�����2��3ָ��1�Ĵ�����4
			2��ָ��1������2ָ��1�Ĵ��۾����������&��ʾ
				1	2	3
			1	0	3	5	
			2	&	0	2
			3	4	&	0

		3����������ʾ��
			[
				[1,2,5]	1ָ��2��Ȩ��Ϊ5
				[1,3,3]	1ָ��3��Ȩ��Ϊ3
				[2,3,5]	2ָ��3��Ȩ��Ϊ5
			]

	��ͨͼ��ͼ�ϵ�һ�����㵽��������һ�����㣬����·���ɴﵽ
*/
int main()
{
	/*
		�ڵ�ͱ߶���������
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