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
	//两个节点所在集合的根节点是否是同一个
	return findRoot(a) == findRoot(b);
}

void UnionFind::unionSet(Node *a, Node *b)
{
	Node *rootA = findRoot(a);
	Node *rootB = findRoot(b);

	if (rootA != rootB)
	{
		//元素少的元素合并到元素多的集合中
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
	//取出vector中的数据，刚开始的时候，每一个节点就是一个集合，代表元素就是自己
	for (int i = 0; i < vectorNode.size(); i++)
	{
		Node *node = vectorNode[i];
		_mapFatherNode[node] = node; //每个节点的父节点都是自己
		_mapSetSize[node] = 1;		 //初始化时集合大小为1

		_setSize++;
	}
}

Node *UnionFind::findRoot(Node *node)
{
	//可以采用递归，也可以不用
	Node *root = node;
	//保存沿途遇到的不是根节点的节点
	stack<Node *> stackNode;
	//当父节点是自己时，才是代表节点
	while (root != _mapFatherNode[root])
	{
		//将沿途的节点都保存下来
		stackNode.push(root);
		//继续向上寻找
		root = _mapFatherNode[root];
	}

	//已经找到了代表节点
	//将沿途遇到的节点，都直接变成根节点的子节点，这样下次 findRoot()，速度会加快
	while (!stackNode.empty())
	{
		Node *curr = stackNode.top();
		stackNode.pop();
		_mapFatherNode[curr] = root;
	}

	return root;
}
