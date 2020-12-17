#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

//坐标
typedef pair<int, int> coord;

class UnionFind
{
public:
	//初始化的时候，一次性的把数据给过来，不能动态添加删除
	UnionFind(vector<coord> &vectorCoord);
	~UnionFind();

public:
	//给定两元素，看这两个元素是否来自同一集合
	bool isSameSet(coord a, coord b);

	//给定两元素，合并这两个元素所在的集合
	void unionSet(coord a, coord b);

	//集合的数量
	int GetSetSize();

private:
	//用用户给的数据，创建集合
	void makeSets(vector<coord> &vectorCoord);

	/*
	给定一个元素，找个这个元素所在集合的代表元素，也就是所在树的根节点
	并且让这个元素到代表元素之间的元素，都直接指向代表元素，也就是让该节点的父节点及父节点的父节点
	都直接指向根节点
	*/
	coord findRoot(coord a);

	//用map表示指向，key是child，value是father
	map<coord, coord> _mapFatherCoord;

	//节点所在集合的元素个数
	map<coord, int> _mapSetSize;

	//集合的数量
	int _setSize;
};

#endif