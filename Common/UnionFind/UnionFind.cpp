#include "UnionFind.h"
#include <stack>

UnionFind::UnionFind(vector<Node *> vectorNode)
{
	_setSize = 0;
	makeSets(vectorNode);
}

UnionFind::~UnionFind()
{
}

bool UnionFind::isSameSet(Node *a, Node *b)
{
	//�����ڵ����ڼ��ϵĸ��ڵ��Ƿ���ͬһ��
	return findRoot(a) == findRoot(b);
}

void UnionFind::unionSet(Node *a, Node *b)
{
	Node *rootA = findRoot(a);
	Node *rootB = findRoot(b);

	if (rootA != rootB)
	{
		//Ԫ���ٵ�Ԫ�غϲ���Ԫ�ض�ļ�����
		int sizeA = _mapSetSize[rootA];
		int sizeB = _mapSetSize[rootB];

		if (sizeA >= sizeB)
		{
			_mapFatherNode[rootB] = rootA;
		}
		else
		{
			_mapFatherNode[rootA] = rootB;
		}

		_mapSetSize[rootA] = _mapSetSize[rootB] = sizeA + sizeB;

		_setSize--;
	}
}

int UnionFind::GetSetSize()
{
	return _setSize;
}

void UnionFind::makeSets(vector<Node *> vectorNode)
{
	//ȡ��vector�е����ݣ��տ�ʼ��ʱ��ÿһ���ڵ����һ�����ϣ�����Ԫ�ؾ����Լ�
	for (int i = 0; i < vectorNode.size(); i++)
	{
		Node *node = vectorNode[i];
		_mapFatherNode[node] = node; //ÿ���ڵ�ĸ��ڵ㶼���Լ�
		_mapSetSize[node] = 1;		 //��ʼ��ʱ���ϴ�СΪ1

		_setSize++;
	}
}

Node *UnionFind::findRoot(Node *node)
{
	//���Բ��õݹ飬Ҳ���Բ���
	Node *root = node;
	//������;�����Ĳ��Ǹ��ڵ�Ľڵ�
	stack<Node *> stackNode;
	//�����ڵ����Լ�ʱ�����Ǵ���ڵ�
	while (root != _mapFatherNode[root])
	{
		//����;�Ľڵ㶼��������
		stackNode.push(root);
		//��������Ѱ��
		root = _mapFatherNode[root];
	}

	//�Ѿ��ҵ��˴���ڵ�
	//����;�����Ľڵ㣬��ֱ�ӱ�ɸ��ڵ���ӽڵ㣬�����´� findRoot()���ٶȻ�ӿ�
	while (!stackNode.empty())
	{
		Node *curr = stackNode.top();
		stackNode.pop();
		_mapFatherNode[curr] = root;
	}

	return root;
}
