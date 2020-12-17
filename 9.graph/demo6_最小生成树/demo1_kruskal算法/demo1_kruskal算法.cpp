#include <iostream>
#include <string>
#include <set>
#include <queue>
#include "../UnionFind/UnionFind.h"
#include "../Edge.h"
#include "../demo2_DFS/WeightedGraphDFS.h"
using namespace std;

/*
	��С����������Ȩ��������ͨͼ
		�ڱ�֤ͼ�нڵ㶼��ͨ������£�Ȩ����С�ıߵļ��ϡ�
		��С��������һ�������������������԰���ȫ��v���ڵ㣬��v-1����
		���账���ͼ������ͨͼ�����������ͨͼ����С��������ֹһ����
	���磺
		   2
		A----B
		|	 |
	  3	|	 |100
		|	 |
		C---->D
		   5
		��Ϊ������ͼ������ȥ��Ȩ��Ϊ100�����ߣ�ͼ�еĽڵ���Ȼ����ͨ��
		��Ȩ��Ϊ2��3��5�ıߣ�����С�������ļ���
*/

/*
	kruskal�㷨��
		��ÿ���ڵ㶼������ֻ��һ���ڵ���������ϵ�ȡ��СȨ�صıߣ��������ϵĺϲ�������ֻʣһ����ʱ��������С������

			2		2
		 --------A-------
		|	   1 |		 |
		|	1	 |	 3	 |
		E------- C-------F	
		|				|
		-----------------
				4

	˼·��
		��һ�����鼯���ж��Ƿ��γ��˻����տ�ʼ��ͼ��ÿ���ڵ㶼��Ϊһ��С���ϼ��뵽���鼯��
		  ����ACEF��4���ڵ���Ϊ�ĸ����ϼ��뵽���鼯�С�
		  �ٰ�ÿ���߷���һ�����ȼ������У����ձߵ�Ȩ�أ���С��������ÿ��ȡ������ͷ��Ȩ����С�ıߣ�
		  �ж������ߵ�from��to���Ƿ�����ͬһ������
		  �������ͬһ�����ϣ������߱��棬����from��to���Ϻϲ�
		  �����ͬһ�����ϣ��ṹ�ɻ�·����Ҫ������
		  ��������ȡ��A��C�ıߣ���AC���Ϻϲ�����ȡ��C��E�ıߣ���CE���Ϻϲ�����ʱACE�ʹ���ͬһ���������ˣ�
		  ��ȡ��A��E�ıߣ���ⷢ��A��E��ͬһ�����ϣ���Ҫ������

		  �������ü���set���ж��Ƿ��γ��˻�������ִ����ж�
*/

/*
	kruskal�㷨�ܹ����������Ȩ����ͼ����С��������
	���Ӷȣ�
		����ռ临�Ӷ�Ϊ O(E + V)
		ʱ�临�Ӷ�Ϊ O(ElogE) �������£�

	���ȼ����У���ౣ��E���ߣ����鼯��ౣ��V���ڵ㣬���Զ���ռ临�Ӷ�ΪO(E + V)

	ʱ��ɱ���Ҫ���������ȼ����еĲ����ɾ���У�ÿ�β��롢ɾ��ʱ�临�Ӷ�Ϊ logE��
	�������ɾ��E���ߣ�����ʱ�临�Ӷ�Ϊ ElogE
	���鼯�Ĺ����� unionSet Ҳ��Ҫʱ�䣬���Ƕ��ǳ������𣬺��Բ���

*/

void MST_kruskal(WeightedGraphDFS &weightedGraph, multiset<Edge> &setResult)
{
	vector<Node *> vectorNode;
	for (auto it = weightedGraph._mapAllNode.begin(); it != weightedGraph._mapAllNode.end(); it++)
		vectorNode.push_back(it->second);

	//��ͼ�����нڵ㣬����һ�����鼯���տ�ʼʱ��ÿ���ڵ㶼��һ�������ļ���
	UnionFind unionFind(vectorNode);

	multiset<Edge> setAllEdge;
	weightedGraph.printfAllEdge(setAllEdge);
	//����һ���Աߵ�Ȩ��Ϊ�����С��С����
	priority_queue<Edge> priorityQueue;
	for (auto it = setAllEdge.begin(); it != setAllEdge.end(); ++it)
		priorityQueue.push(*it);

	//��С����������V���ڵ㣬��V-1����
	while (!priorityQueue.empty() && setResult.size() < weightedGraph._mapAllNode.size() - 1)
	{
		//ÿ��ȡһ��Ȩ����С�ı�
		Edge edge = priorityQueue.top();
		priorityQueue.pop();

		//�ж������ߵ�from��to���Ƿ�����ͬһ������
		//�����ͬһ�����ϣ��ṹ�ɻ�·����Ҫ������
		if (unionFind.isSameSet(edge._from, edge._to))
			continue;
		//�������ͬһ�����ϣ������߱��棬����from��to���Ϻϲ�
		setResult.insert(edge);
		unionFind.unionSet(edge._from, edge._to);
	}
}

int main()
{
	/*
		һ���ĸ���1��2��3��4

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
	multiset<Edge> setResult;

	MST_kruskal(weightedGraphDFS, setResult);
	for (auto it = setResult.begin(); it != setResult.end(); ++it)
		cout << (*it)._from->_data << " to " << (*it)._to->_data << endl;
	return 0;

	/*
	����java����

		public static Set<Edge> kruskalMST(Graph graph) {
		UnionFind unionFind = new UnionFind();
		unionFind.makeSets(graph.nodes.values());
		PriorityQueue<Edge> priorityQueue = new PriorityQueue<>(new EdgeComparator());
		for (Edge edge : graph.edges) {
			priorityQueue.add(edge);
		}
		Set<Edge> result = new HashSet<>();
		while (!priorityQueue.isEmpty()) {
			Edge edge = priorityQueue.poll();
			if (!unionFind.isSameSet(edge.from, edge.to)) {
				result.add(edge);
				unionFind.union(edge.from, edge.to);
			}
		}
		return result;
	}
	
	
	*/
	return 0;
}