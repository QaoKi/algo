#include <iostream>
#include <string>
#include <queue>
#include <map>
#include "../../Edge.h"
#include "../../OrientedWeightedGraph/OrientedWeightedGraph.h"

using namespace std;

/*
	dijkstra�㷨���ʺϷǸ�Ȩ��ͼ��Ȩ�ز���Ϊ������Ϊ�������ɳڲ������и�Ȩֵ��������ܽ����Դ���·������

	��Ŀ������һ����Ȩͼ���������򶼿��ԣ�����ʹ��������ͼ��������һ�����s������ڵ�s�������ɵ���ڵ�����·��

	˼·����sΪ��㣬�������ɴ�ڵ�����·�����ǿ������һ�����·�����ġ�
			�� prim�㷨ʵ�����ƣ������㼯��V�ֳ������Ӽ���T��T1��
			T���Ѿ�������·���Ķ��㼯�ϣ��ڵ���������·������
			T1����δ������·���Ķ��㼯�ϣ��ڵ㻹û�н������·��������

		    ���ϵĽ�T1�еĶ�����뵽T�У�Prim�㷨ÿ����ӵĶ�����������ķ������㣬ʹ�����ȼ����е�Dijkstra�㷨ÿ����ӵ�
			��С·�����ϵĽڵ�Ҳ�ǵ�ǰ��������ķ�������

	ʵ�֣�
		1��������������:
			distTo[w] = 100��w ���� s�ĳ����� 100����s��w������·����Ȩ����100������ʼ��ʱ����distTo�����ֵ��Ϊ�����
			edgeTo[w] = v����s��w�����·�������һ������ v����w����ʼ��ʱ����edgeTo�����ֵ��ΪNULL
		1����distTo[s] = 0, edgeTo[s] = NULL����s�ڵ���뼯��T�У���һ��set����ʾ�Ƿ�����ˣ�
		2��������s�����ӵıߣ�����Ȩ������������ȼ����С�
		3���Ӷ�����ȡ��һ��Ȩֵ��С�ı�e(s, v, weigh)
			������Ȩ����С�ıߣ���ζ��ĿǰT1�е����нڵ㣬�������·����������� v�ڵ㣬������ weigh��
		4�����v �Ƿ��Ѿ����뼯��T������У����������ߣ����û�У�����distTo��edgeTo
			��θ��� distTo��edgeTo��
				�ɳڲ������������ҳ����̵����·����
					������ e ʱ
					if(distTo[e.to] > distTo[e.from] + e.weigh) {
						distTo[e.to] = distTo[e.from] + e.weigh;
						edgeTo[e.to] = e.from;
					}

			��һ�δӶ�����ȡ������ʱ��distTo[v]Ϊ�������ô�����߿϶������ɳڲ��ݣ�������������
		5���������ȼ�������ȡ��������ζ��s��v�����·���Ѿ��ҵ��ˣ���vֱ�ӽ��뼯��T
		6�������� v�����ӵıߣ����뵽���ȼ������У�e�ٴμӽ�����Ҳû�й�ϵ���Ӷ���ȡ�����ı߻��ڵ�4�������жϣ�
		7����ʱ�Ķ����а�������s�����ӵıߺ���v�����ӵıߣ��ظ���3������

		������Ĳ��裬֪�����ж��㶼���뵽����T�У�Ҳ����ζ�����еĶ��㶼��������С·������

	�ص㣺
		Dijkstra�㷨��Primʵ�����ƣ�Prim�㷨ÿ����ӵĶ�����������ķ������㣬ʹ�����ȼ����е�Dijkstra�㷨ÿ����ӵ�
		��С·�����ϵĽڵ�Ҳ�ǵ�ǰ��������ķ�������

*/

/*
	�ܽ᣺
		����һ��˼·�����������ȼ����У����Ǳ������еıߣ������ɳڲ����������ȱ����ĸ��ڵ�ͺ�����ĸ��ڵ���
		���ܿ��Ƶģ������͵��� distTo �������ݲ��ԣ��Ӷ�Ӱ������������ȱ���s���ڶ��α�����sֱ�������Ľڵ�w�������α���
		��vֱ�������Ľڵ�v���������vû�г��ȣ���ô�Ͳ����ڱ����������ڵ�ǰ����v�ڵ㣬��Ҫ���ݵ�w�ڵ㣬����������鷳
*/

/*
	ʱ�临�Ӷȣ���prim�㷨һ����ʵ��ԭ��һ������ʱ�临�Ӷ�Ϊ O(ElogE)
*/

void visit(OrientedWeightedGraph &weightedGraph, Node *node, priority_queue<Edge> &pq)
{
	//������node��ͨ�����б�
	for (auto it = weightedGraph._mapOrientedWeightedGraph[node].begin(); it != weightedGraph._mapOrientedWeightedGraph[node].end(); it++)
	{
		//��ɱߣ��������ȼ�����
		Edge edge(node, it->first, it->second);
		pq.push(edge);
	}
}

//����ͼ�У���sΪ��㣬�������ɴ�ڵ�����·��
void ShortPath(OrientedWeightedGraph &weightedGraph, Node *s, map<Node *, int> &indistTo, map<Node *, Node *> &inedgeTo)
{
	//�Ѿ��ҵ����·���Ľڵ�
	set<Node *> setNode;

	// <w, 100>	�� s�ڵ㵽w�ڵ�����·������Ȩ��Ϊ100
	map<Node *, int> distTo;
	/*
		<w, v> �� s�ڵ㵽w�ڵ�����·�������һ������ v����w
		ͬʱ edgeTo Ҳ�ǽ���������·��Ϊ edgeTo[w] ����
		Ҳ������ map<Node *, Edge>��һ����
	*/
	map<Node *, Node *> edgeTo;

	//��ʼ��ʱ��Ӧ���� distTo ֵΪ�����edgeToֵΪnull�����������map��if(find() == end())��˵��������
	//��distTo[s] = 0, edgeTo[s]�Ͳ���ΪNULL�ˣ�if(edgeTo.find(s) == edgeTo.end())�������� edgeTo[s] = NULL
	distTo[s] = 0;
	//s�ڵ�����·���Ѿ��ҵ�
	setNode.insert(s);

	priority_queue<Edge> pq;
	visit(weightedGraph, s, pq);

	while (!pq.empty() && setNode.size() < weightedGraph._mapAllNode.size())
	{
		Edge edge = pq.top();
		pq.pop();

		//���to�ڵ�����·���Ѿ��ҵ��ˣ�����
		if (setNode.find(edge._to) != setNode.end())
			continue;

		//�����ɳڲ���
		if (distTo.find(edge._to) == distTo.end() || distTo[edge._to] > distTo[edge._from] + edge._weight)
		{
			/*
				if (distTo.find(edge._to) == distTo.end())
					distTo��û�ҵ�edge._to�������� distTo[to] �����������ô�϶����� distTo[edge._from] + edge._weight
			*/
			distTo[edge._to] = distTo[edge._from] + edge._weight;
			//���� edge._from����edge._to �����߹�����
			edgeTo[edge._to] = edge._from;
		}

		//�ߴ����ȶ�����ȡ������ζ�űߵ�to�ڵ�����·���Ѿ��ҵ�
		setNode.insert(edge._to);
		//�ٱ���to�ڵ�
		visit(weightedGraph, edge._to, pq);
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