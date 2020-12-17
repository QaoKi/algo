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
	//两个节点所在集合的根节点是否是同一个
	return findRoot(a) == findRoot(b);
}

void UnionFind::unionSet(coord a, coord b)
{
	coord coordA = findRoot(a);
	coord coordB = findRoot(b);

	if (coordA != coordB)
	{
		//元素少的元素合并到元素多的集合中
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
	//取出vector中的数据，刚开始的时候，每一个节点就是一个集合，代表元素就是自己
	for (int i = 0; i < vectorCoord.size(); i++)
	{
		coord node = vectorCoord[i];
		_mapFatherCoord[node] = node; //每个节点的父节点都是自己
		_mapSetSize[node] = 1;		  //初始化时集合大小为1
		_setSize++;
	}
}

coord UnionFind::findRoot(coord a)
{
	//可以采用递归，也可以不用
	coord root = a;
	//保存沿途遇到的不是根节点的节点
	stack<coord> stackCoord;
	//当父节点是自己时，才是代表节点
	while (root != _mapFatherCoord[root])
	{
		//将沿途的节点都保存下来
		stackCoord.push(root);
		//继续向上寻找
		root = _mapFatherCoord[root];
	}

	//已经找到了代表节点
	//将沿途遇到的节点，都直接变成根节点的子节点，这样下次 findRoot()，速度会加快
	while (!stackCoord.empty())
	{
		coord curr = stackCoord.top();
		stackCoord.pop();
		_mapFatherCoord[curr] = root;
	}

	return root;
}
