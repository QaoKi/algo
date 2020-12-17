#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>
#include <unordered_set>
#include "../Edge.h"
#include "../demo2_DFS/WeightedGraphDFS.h"
#include "../IndexMinHeap/IndexMinHeap.h"

using namespace std;

/*
	prim�㷨�Ľ���
	segmentfault.com/a/1190000021555887
	���潲���������� edgeTo �� distTo �ľ����÷�	

˼·��
	V���ϱ�ʾͼ�����нڵ㣬U���ϱ�ʾ��С�������ļ��ϣ���V�нڵ㶼ת�Ƶ�U�У���С���������
	���� edgeTo[i] = j ��ʾ���� V �еĽڵ� i ������ U �е����нڵ�ľ��룬������� j�ڵ�
	���� distTo[i] = 100 ��ʾ i �� j ��ȨֵΪ100
	ֻ��Ҫ�ڼ��� V ���� distTo[]ֵ��С�Ķ��㼴��

�ȿ�һ�����Ӷȸߵ�
	V���ϱ�ʾͼ�����нڵ㣬U���ϱ�ʾ��С�������ļ��ϣ���V�нڵ㶼ת�Ƶ�U�У���С���������
	һ�� bool����s[]��s[i] = true��˵���ڵ�i�Ѽ��뼯��U��
	���� closest[i] = j ��ʾ���� V �еĽڵ� i ������ U �е����нڵ�ľ��룬������� j�ڵ�
	���� lowcost[i] = 100 ��ʾ i �� j ��ȨֵΪ100
	ֻ��Ҫ�ڼ��� V ����lowcost[]ֵ��С�Ķ��㼴��
	����1����ʼ����ָ��һ���ڵ�u���� U = {u}��������u����ʼ��closest[].lowcost[]��s[]
	����2����V��������lowcost��С�Ľڵ�t,���ڵ�t���뼯��U
	����3���Լ���V-U�е����ж���j,������lowcost[]��closest[]��
		  ���ڴ�ʱt�Ѿ���U�еĽڵ㣬������U-V�е�һЩ�ڵ������ӣ�
		  �����Ҫ���µ�������Uʱ������������������ϵ�Ȩֵ��С�ıߵı仯�����
		  ���¹�ʽΪ��if(c[t][j] < lowcost[j]) {lowcost[j] = c[t][j] ; closest[j] = t;},ת����2��
	ע��lowcost�������ȼ����д��棬pair<i, 100>

ΪʲôҪʹ���������ȶ��У�֮ǰʹ�����ȼ����У������д洢���Ǳߣ��������������ȶ��У��洢���ǽڵ�
*/

/*
	prim�㷨�ܹ����������Ȩ����ͼ����С��������
	���Ӷȣ�
		���㺬��V���ڵ��E���ߵ���ͨ��Ȩ����ͼ������ռ临�Ӷ�Ϊ O(V)
		ʱ�临�Ӷ� ElogV

		���ȶ����У��������V�Σ����Զ���ռ临�Ӷ�Ϊ O(V)
		�����V�β��������V��ɾ����СԪ�صĲ����ͣ��������£�E�θı����ȼ��Ĳ���
		����ʱ�临�Ӷ�ΪElogV
*/

/*
	prim�㷨��kruskal�㷨
	kruskal�㷨ʱ�临�Ӷ�Ϊ ElogE���Ľ����prim�㷨ʱ�临�Ӷ�Ϊ ElogV���߳��ܵ�ͼ�������� prim����ϡ���ͼ������ Kruskal�㷨
*/

void visit(WeightedGraphDFS &weightedGraph, Node *v, IndexMinHeap &indexPQ, set<Node *> &setNode, map<Node *, Node *> &edgeTo, map<Node *, int> &distTo)
{
	//����v�ڵ�����б�
	for (auto it = weightedGraph._mapWeightedGraph[v].begin(); it != weightedGraph._mapWeightedGraph[v].end(); it++)
	{
		Node *w = it->first;
		int weight = it->second;
		//�Ѿ����뼯��U�еĽڵ�Ͳ��ù���
		if (setNode.find(w) != setNode.end())
			continue;

		if (distTo.find(w) == distTo.end())
		{
			edgeTo[w] = v;
			distTo[w] = weight;
			//��¼w�ڵ���뼯��U��Ȩ��
			indexPQ.insert(w->_data, weight);
		}
		else if (weight < distTo[w])
		{
			//w�ڵ㵽����U����ѱ߱��  w ���� v
			edgeTo[w] = v;
			distTo[w] = weight;
			//�ı�w�ڵ���뼯��U��Ȩ��
			indexPQ.change(w->_data, weight);
		}
	}
}

map<Node *, Node *> MST_QuickPrim(WeightedGraphDFS &weightedGraph)
{
	/*
	�ڵ��Ƿ��Ѿ����뵽��С�������У����set����Ҫ�ģ���Ȼ�����
		���� e(u0, u1, 10), e1(u1, u2, 5)
		�տ�ʼdistTo[u0] = 0,������e��distTo[u1] = 10����ʱu0��u1�Ѿ����뵽�˼���T�У�
		���ű�����e1��distTo[u2] = 5��u2���뼯��T����Ϊ������ͼ�����´α������� e2(u2, u1, 5)��
		ʱ�򣬴�ʱdistTo[u1] = 10�������ȥ�ж� u1�Ƿ��Ѿ������˼���T��
		ֱ���ж� weight < distTo[u1] �Ļ���������ὫdistTo[u1]��ֵ��Ϊ5��u1���ٴμ����������ȶ�����
	*/

	set<Node *> setNode;
	//�������飬��С�������Ľ���ͷ���edgeTo��
	map<Node *, Node *> edgeTo;
	map<Node *, int> distTo;
	/*
		�����������ȶ��У�Ҫע��һ�㣬�ڳ�ʼ���������е�ʱ��Ҫ������������ֵ���������������ֵ�����ڴ棬
		����ʹ��ͼ�нڵ��ֵ��Ϊ������key��������Ҫ�ҵ�ͼ�����нڵ�����ֵ����
		��Ϊ�� insert(key, data)��ʱ�򣬻��� _value[key] = data�������ʼ����ʱ�����ֵ��keyС����ô������_value�����Խ����
		���ù�data�Ĵ�С����Ϊ�����������飬_pq��_qp����û�нӴ���data
	*/
	//���ͼ���Ľڵ�ֵӦ�ò��ᳬ���ڵ�������������ü�����
	IndexMinHeap indexPQ(weightedGraph._mapAllNode.size());
	/*
		�� root �ڵ���Ϊ��һ�����뼯��U�Ľڵ�
		�ýڵ��ֵ��Ϊkey������key��Ψһ�ģ�Ȩ����Ϊ����
	*/
	//��Ϊroot�ڵ��ǵ�һ�����뼯��U�ģ����������뼯��U��Ȩ��Ϊ0
	indexPQ.insert(weightedGraph._nodeRoot->_data, 0);

	//��ΪindexPQ ���������V���ڵ㣬���Բ���Ҫʹ�� while(!indexPQ.isEmpty() && setNode.size() < nodeCount) ���жϽ���
	while (!indexPQ.isEmpty())
	{
		//�Ӷ�����ȡһ���ڵ� node��node �����ڼ���V�У����ұ��𼯺�V�е������ڵ㣬node ������U��Ȩ����С
		//�����������д�����ʱ���ڵ��ֵ��Ϊkey��Ȩ����Ϊvalue�����Խڵ��ֵ�� topIndex()�ķ���ֵ
		//��һ��ȡ��������root
		int valueData = indexPQ.topIndex();
		indexPQ.pop();
		//���ݽڵ�ֵ�ҵ��ڵ�ָ�룬����Ͳ��ж�_mapAllNode���Ƿ���valueData���key��
		Node *node = weightedGraph._mapAllNode[valueData];

		//����ڵ��Ѿ����뵽�˼���U���Ͳ�����
		if (setNode.find(node) != setNode.end())
			continue;

		//��node���뼯��U
		setNode.insert(node);
		visit(weightedGraph, node, indexPQ, setNode, edgeTo, distTo);
	}

	//��С�������Ľ���ͷ���edgeTo��
	return edgeTo;
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
	map<Node *, Node *> edgeTo = MST_QuickPrim(weightedGraphDFS);
	for (auto it = edgeTo.begin(); it != edgeTo.end(); ++it)
		cout << it->first->_data << " to " << it->second->_data << endl;

	return 0;
}