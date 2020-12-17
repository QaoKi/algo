#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

//����
typedef pair<int, int> coord;

class UnionFind
{
public:
	//��ʼ����ʱ��һ���Եİ����ݸ����������ܶ�̬���ɾ��
	UnionFind(vector<coord> &vectorCoord);
	~UnionFind();

public:
	//������Ԫ�أ���������Ԫ���Ƿ�����ͬһ����
	bool isSameSet(coord a, coord b);

	//������Ԫ�أ��ϲ�������Ԫ�����ڵļ���
	void unionSet(coord a, coord b);

	//���ϵ�����
	int GetSetSize();

private:
	//���û��������ݣ���������
	void makeSets(vector<coord> &vectorCoord);

	/*
	����һ��Ԫ�أ��Ҹ����Ԫ�����ڼ��ϵĴ���Ԫ�أ�Ҳ�����������ĸ��ڵ�
	���������Ԫ�ص�����Ԫ��֮���Ԫ�أ���ֱ��ָ�����Ԫ�أ�Ҳ�����øýڵ�ĸ��ڵ㼰���ڵ�ĸ��ڵ�
	��ֱ��ָ����ڵ�
	*/
	coord findRoot(coord a);

	//��map��ʾָ��key��child��value��father
	map<coord, coord> _mapFatherCoord;

	//�ڵ����ڼ��ϵ�Ԫ�ظ���
	map<coord, int> _mapSetSize;

	//���ϵ�����
	int _setSize;
};

#endif