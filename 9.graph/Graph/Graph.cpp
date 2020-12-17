#include "Graph.h"

Graph::Graph()
{
}

Graph::~Graph()
{
}

/*
	��һ�����飬[[1,2,3],[2,3,4],[4,5,6]]
	1	2	3	
	2	3	4
	4	5	6
	����һ��ͼ
	��һ�б�ʾȨ��
	�ڶ��б�ʾform
	�����б�ʾto
*/
Node *Graph::GetGraph(int arr[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		int weight = arr[i][0];
		int from = arr[i][1];
		int to = arr[i][2];
		//from��������ͼ����û�У�û�еĻ����½�һ����
		if (this->nodes.find(from) == this->nodes.end())
		{
			this->nodes[from] = new Node(from);
		}

		//to��������ͼ����û�У�û�еĻ��½�һ���ڵ�
		if (this->nodes.find(to) == this->nodes.end())
		{
			this->nodes[to] = new Node(to);
		}

		//����from��to��ͼ�ж����ˣ�����ǵĹ�ϵ
		//ȡ����from��to�ڵ�
		Node *fromNode = this->nodes[from];
		Node *toNode = this->nodes[to];
		//�½�һ����
		Edge *newEdge = new Edge(weight, fromNode, toNode);

		//fromָ��to
		fromNode->nexts.push_back(toNode);
		fromNode->out++; //�ڵ�ָ��Ľڵ������+1
		toNode->in++;	 //�ڵ㱻ָ�������+1
		//�ڵ���Ϊfrom�ı�
		fromNode->edges.push_back(newEdge);
		this->edges.insert(newEdge);
	}

	return this->nodes[1];
}
