#include <iostream>
#include <string>
#include <queue>
#include "../Edge.h"
#include "../demo2_DFS/WeightedGraphDFS.h"

using namespace std;

/*
	https://segmentfault.com/a/1190000021555887
	
	prim�㷨�������зֶ���������̰���㷨
	ԭ��
		����ͨ������ΪG(V,E)�������㼯��V�ֳ������Ӽ���T��T1���зֶ�����
			T����ǰ���������㼯�ϣ�
			T1�������ڵ�ǰ�������Ķ��㼯�ϡ�
		����Ȼ��T��T1 = V��Ŀ�������T1�����еĶ��㲻�ϼ��뵽T�����С�Prim�ľ���������£�

			1������ͨ������G��ѡ��һ����ʼ����u0�����Ƚ������뵽����T�У���һ��set����ʾ�Ƿ�����ˣ���
			2��������u0�����ӵıߣ�����Ȩ������������ȼ����С�
			3���Ӷ�����ȡ��һ��Ȩֵ��С�ı�e(u0, u1, weigh)
				������Ȩ����С�ıߣ���ζ��ĿǰT1�е����нڵ㣬����T���ϣ���С��������������� u1�ڵ㣬������ weigh��
			4�����u1�Ƿ��Ѿ����뼯��T������У����������ߣ����û�У���e����������
			5���� u1���뵽����T�У�set��
			6�������� u1�����ӵıߣ����뵽���ȼ������У�e�ٴμӽ�����Ҳû�й�ϵ���Ӷ���ȡ�����ı߻��ڵ�4�������жϣ�
			7����ʱ�Ķ����а�������u0�����ӵıߺ���u1�����ӵıߣ��ظ���3������

			������Ĳ��裬ֱ�����ж��㶼���뵽����T�У�Ҳ����ζ�����еĶ��㶼��������С��������
	�ص㣺
		�����ȼ�������ȡ��һ����e(u0, u1, weigh)����ζ��ĿǰT1�е����нڵ㣬����T����������� u1�ڵ㣬������ weigh��
		����������Ϊ��С��������һ���ַ���������u1���뼯��T
*/

/*
	prim�㷨�ܹ����������Ȩ����ͼ����С��������
	���Ӷȣ�
		���㺬��V���ڵ��E���ߵ���ͨ��Ȩ����ͼ������ռ临�Ӷ�Ϊ O(E)
		ʱ�临�Ӷ� ElogE

		�㷨��ƿ���������ȶ��У��ѣ���insert()��delMin()�����ȶ�������������E���ߣ����Զ���ռ临�Ӷ�Ϊ O(E)
		�Ѳ����ɾ����ʱ�临�Ӷ�ΪO(logE)����Ϊ������E���ߺ�ɾ��E���ߣ�����ʱ�临�Ӷ�ΪO(ElogE)
		visit()���������ڵ�ı�Ҳ������ʱ�䣬�������Ҳ�ͱ���E���ߣ�ʱ��Ͳ�����
*/

void visit(WeightedGraphDFS &weightedGraph, Node *node, priority_queue<Edge> &priorityQueue)
{
	//������node�ڵ�����ͨ�����бߣ����뵽���ȼ�������
	for (auto it = weightedGraph._mapWeightedGraph[node].begin(); it != weightedGraph._mapWeightedGraph[node].end(); it++)
	{
		Edge edge(node, it->first, it->second);
		//�������ȼ�����
		priorityQueue.push(edge);
	}
}

/*	
ǰ�᣺
	�� set<Edge> setEdgeResult ��Ϊ�������
		 ������set<Node* > ��Ϊ���������Ϊ��С��������Ȼ�ǰ������еĽڵ㣬
		 ��set<Node *> ����ֻ�������еĽڵ㣬������֪��ȡ����Щ���������
	��set�в���ֱ�ӱ��� Edge����ΪEdge����д�� <����edge�������set��ʱ���������edge��_weight��ͬ��
	�ᱻ��Ϊ��ͬһ��edge���� multiset<Edge> �ķ�ʽ
*/
void MST_Prim(WeightedGraphDFS &weightedGraph, int nodeCount, multiset<Edge> &setEdgeResult)
{
	//���뵽setNode�еĽڵ㣬���Ѿ����뼯��T�Ľڵ�
	set<Node *> setNode;
	priority_queue<Edge> priorityQueue;

	//�� root �ڵ�Ϊ��ʼ�ڵ㣬��root���뵽����T�У�������root�ڵ�����ͨ�ı߼������ȼ�����
	//root�ڵ������С������
	setNode.insert(weightedGraph._nodeRoot);
	visit(weightedGraph, weightedGraph._nodeRoot, priorityQueue);

	while (!priorityQueue.empty() && setNode.size() < nodeCount)
	{
		//ȡ��һ��Ȩ����С�ı�
		Edge edge = priorityQueue.top();
		priorityQueue.pop();
		/*
			��������ߵ�from��to���Ѿ������˼���T����������Ȼ���γɻ�
			�㷨���İ����ж���from��to�����ڵ㣬����ʵֻ�ж�to�ڵ�Ϳ�����
			��Ϊ�������Ǵ���С������ȡ���ģ����ܽ�����С�����еıߣ��ߵ�from�ڵ㶼���Ѿ����뼯��T�еģ�
			����from�ڵ�϶��Ѿ����뵽��С���������ˣ�Ҳ���Ǽ��뵽��setNode�У����Բ���д����ô����

			������ôд�Ļ�������������
		*/
		/*
			�㷨���İ��д����
			if (setNode.find(edge._from) != setNode.end() && setNode.find(edge._to) != setNode.end())
				continue;
			//��������
			setEdgeResult.insert(edge);
		
			//������Բ�д�ģ���Ϊ_from�϶���setNode��
			if (setNode.find(edge._from) == setNode.end())
				visit(weightedGraph, edge._from, priorityQueue, setNode);
			
			if (setNode.find(edge._to) == setNode.end())
				visit(weightedGraph, edge._to, priorityQueue, setNode);
		*/

		//���to�ڵ��Ѿ������˼���T����������Ȼ���γɻ�
		if (setNode.find(edge._to) != setNode.end())
			continue;
		//�����߷�������
		setEdgeResult.insert(edge);
		//to�ڵ��Ǽ���T1�о��뼯��T����Ľڵ㣬���뼯��T
		setNode.insert(edge._to);
		//����to���ӵı߼������ȼ�����
		visit(weightedGraph, edge._to, priorityQueue);
	}
}

int main()
{

	/*
		һ���ĸ���1��2��3��4

			2		2
		 --------1-------
		|	   1 |		 |
		|	1	 |	 3	 |
		3------- 2-------4
		|				 |
		-----------------
				4
	*/
	int nodeCount = 4;
	WeightedGraphDFS weightedGraphDFS;
	weightedGraphDFS.addEdge(1, 2, 1);
	weightedGraphDFS.addEdge(1, 3, 2);
	weightedGraphDFS.addEdge(1, 4, 2);
	weightedGraphDFS.addEdge(2, 3, 1);
	weightedGraphDFS.addEdge(2, 4, 3);
	weightedGraphDFS.addEdge(3, 4, 4);

	weightedGraphDFS.printfAllNodes();
	//weightedGraphDFS.printfAllEdge();
	multiset<Edge> setResult;

	MST_Prim(weightedGraphDFS, nodeCount, setResult);
	for (auto it = setResult.begin(); it != setResult.end(); ++it)
		cout << (*it)._from->_data << " to " << (*it)._to->_data << endl;
	return 0;
}