#include "UnionFind.h"
#include <stack>

UnionFind::UnionFind(vector<coord> &vectorCoord)
{
	_setSize = 0;
	makeSets(vectorCoord);
}

UnionFind::~UnionFind()
{
}

bool UnionFind::isSameSet(coord a, coord b)
{
	//�����ڵ����ڼ��ϵĸ��ڵ��Ƿ���ͬһ��
	return findRoot(a) == findRoot(b);
}

void UnionFind::unionSet(coord a, coord b)
{
	coord coordA = findRoot(a);
	coord coordB = findRoot(b);

	if (coordA != coordB)
	{
		//Ԫ���ٵ�Ԫ�غϲ���Ԫ�ض�ļ�����
		int sizeA = _mapSetSize[coordA];
		int sizeB = _mapSetSize[coordB];

		if (sizeA >= sizeB)
		{
			_mapFatherCoord[coordA] = coordB;
		}
		else
		{
			_mapFatherCoord[coordB] = coordA;
		}

		_mapSetSize[coordA] = _mapSetSize[coordB] = sizeA + sizeB;

		_setSize--;
	}
}

int UnionFind::GetSetSize()
{
	return _setSize;
}

void UnionFind::makeSets(vector<coord> &vectorCoord)
{
	//ȡ��vector�е����ݣ��տ�ʼ��ʱ��ÿһ���ڵ����һ�����ϣ�����Ԫ�ؾ����Լ�
	for (int i = 0; i < vectorCoord.size(); i++)
	{
		coord node = vectorCoord[i];
		_mapFatherCoord[node] = node; //ÿ���ڵ�ĸ��ڵ㶼���Լ�
		_mapSetSize[node] = 1;		  //��ʼ��ʱ���ϴ�СΪ1
		_setSize++;
	}
}

coord UnionFind::findRoot(coord a)
{
	//���Բ��õݹ飬Ҳ���Բ���
	coord root = a;
	//������;�����Ĳ��Ǹ��ڵ�Ľڵ�
	stack<coord> stackCoord;
	//�����ڵ����Լ�ʱ�����Ǵ���ڵ�
	while (root != _mapFatherCoord[root])
	{
		//����;�Ľڵ㶼��������
		stackCoord.push(root);
		//��������Ѱ��
		root = _mapFatherCoord[root];
	}

	//�Ѿ��ҵ��˴���ڵ�
	//����;�����Ľڵ㣬��ֱ�ӱ�ɸ��ڵ���ӽڵ㣬�����´� findRoot()���ٶȻ�ӿ�
	while (!stackCoord.empty())
	{
		coord curr = stackCoord.top();
		stackCoord.pop();
		_mapFatherCoord[curr] = root;
	}

	return root;
}
