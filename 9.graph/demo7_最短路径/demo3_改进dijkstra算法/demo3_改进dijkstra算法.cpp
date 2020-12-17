#include <iostream>
#include <string>
#include <queue>
#include <map>
#include "../../Edge.h"
#include "../../OrientedWeightedGraph/OrientedWeightedGraph.h"
#include "../../IndexMinHeap/IndexMinHeap.h"

using namespace std;

/*
	ʹ���������ȶ��У���ʱ�临�ӶȽ�Ϊ ElogV
	ʹ�����ȼ����е�Dijkstra�㷨��ÿ����ӵ���С·�����ϵĶ����ǵ�ǰ��������ķ������㣬��ʹ���������ȶ��е�Dijkstra�㷨��
	ÿ����ӵ����ϵĶ��㣬�ǵ�ǰ�������s����Ķ��㡣
	ʹ���������ȶ��У������ֵ��key�������distToֵ�� value��ÿ�δӶ�����ȡ���Ķ��㣬����distToֵ����С�ģ�Ҳ����˵�������
	�������s�����
*/

/*
	ʱ�临�Ӷȣ��͸Ľ���prim�㷨һ����ʵ��ԭ��һ������ʱ�临�Ӷ�Ϊ O(ElogV)
*/

//����ͼ�У���sΪ��㣬�������ɴ�ڵ�����·��
void ShortPath(OrientedWeightedGraph &weightedGraph, Node *s, map<Node *, int> &indistTo, map<Node *, Node *> &inedgeTo)
{
	/*
		�������������ҪsetNode���ж϶����Ƿ��Ѿ��������·������֮ǰ�ж������ظ�����������ɴ���
		�����ɳڲ������ᣬ�����������e(v, w, weigh)������distTo[w] = distTo[v] + weigh����w���뵽�������ȶ��У�
		�´�ȡ������w��ʱ�򣬱�������e1(w, v, weigh)����ʱ distTo[v]��ֵ�϶���С��distTo[w] + weigh��������weigh�Ǹ�������
		��ΪdistTo[w]��ֵ������distTo[v] + weigh�����Բ����������ɳڲ��������Բ���Ҫ���ı�������һ��e���´α�����e1ʱ�����
		�����ڸĽ���prim�㷨�У�setNode������Ҫ��
	*/

	map<Node *, int> distTo;
	map<Node *, Node *> edgeTo;
	IndexMinHeap indexPQ(weightedGraph._mapAllNode.size());

	distTo[s] = 0;
	//�����ֵ��Ϊkey�������distToֵ��Ϊvalue
	indexPQ.insert(s->_data, distTo[s]);

	while (!indexPQ.isEmpty())
	{
		//�����������д�����ʱ���ڵ��ֵ��Ϊkey�����Խڵ��ֵ�� topIndex()�ķ���ֵ��key��
		int nodeData = indexPQ.topIndex();
		indexPQ.pop();
		//���ݽڵ�ֵ�ҵ��ڵ�ָ�룬����Ͳ��ж�_mapAllNode���Ƿ���nodeData���key��
		Node *node = weightedGraph._mapAllNode[nodeData];

		/*
			�Ӷ�����ȡ�����Ķ��� v���ǵ�ǰ���е����ж����� distToֵ��С�ģ�Ҳ���������s����Ķ��㣬distTo[v]���ֵ��������
			�ı��ˣ���֮�����������Ч�ߵ�ʱ��Ҳ�����ٸı�
			ȡ������Ĭ���Ǽӵ��˼���T�У������setNode�Ļ�������ͽ�node�ڵ�Ž�ȥ
		*/
		//������node��ͨ�����бߣ������ɳڲ�����������������
		for (auto it = weightedGraph._mapOrientedWeightedGraph[node].begin(); it != weightedGraph._mapOrientedWeightedGraph[node].end(); it++)
		{
			//��ɱߣ�����Ҳ�У�ֻ��Ϊ�˴����������
			Edge edge(node, it->first, it->second);
			//�����ɳڲ���
			if (distTo.find(edge._to) == distTo.end() || distTo[edge._to] > distTo[edge._from] + edge._weight)
			{
				distTo[edge._to] = distTo[edge._from] + edge._weight;
				edgeTo[edge._to] = edge._from;

				//change�������жϣ���������ھͲ���
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

	//������
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