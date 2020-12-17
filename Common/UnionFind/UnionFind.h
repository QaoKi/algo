#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct Node
{
	int _data;

	Node(int data)
	{
		_data = data;
	}

	Node(const Node &other)
	{
		_data = other._data;
	}
};

class UnionFind
{
public:
	//��ʼ����ʱ��Ҫһ���Եİ����ݸ����������ܶ�̬���ɾ��
	UnionFind(vector<Node *> vectorNode);
	~UnionFind();

public:
	//������Ԫ�أ���������Ԫ���Ƿ�����ͬһ����
	bool isSameSet(Node *a, Node *b);

	//������Ԫ�أ��ϲ�������Ԫ�����ڵļ���
	void unionSet(Node *a, Node *b);

	//���ϵ�����
	int GetSetSize();

private:
	//���û��������ݣ���������
	void makeSets(vector<Node *> vectorNode);

	/*
	����һ��Ԫ�أ��Ҹ����Ԫ�����ڼ��ϵĴ���Ԫ�أ�Ҳ�����������ĸ��ڵ�
	���������Ԫ�ص�����Ԫ��֮���Ԫ�أ���ֱ��ָ�����Ԫ�أ�Ҳ�����øýڵ�ĸ��ڵ㼰���ڵ�ĸ��ڵ�
	��ֱ��ָ����ڵ�
	*/
	Node *findRoot(Node *node);

	//��map��ʾָ��key��child��value��father
	map<Node *, Node *> _mapFatherNode;

	//�ڵ����ڼ��ϵ�Ԫ�ظ���
	map<Node *, int> _mapSetSize;

	//���ϵ�����
	int _setSize;
};

#endif