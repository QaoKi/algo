#pragma once

#include <iostream>
#include <string>
#include <map>

using namespace std;


struct Node
{
	int path;		//有多少字符串路过了这个节点
	int end;		//有多少字符串是以这个节点结尾的
	map<char, Node*> nexts;

	Node()
	{
		path = 0;
		end = 0;
	}
	
	/*
		需要记录一个节点能产生多少条路
		比如，如果字符串中只有字母，26个字母，一个节点最多有26条路
				可显字符一共95个，也可以为每个节点建立95条路
				也可以申请一个map<char,Node>，key可以有很多，代表有很多条路，value代表这个字符指向的节点

				比如都是字母，最多26条路
				Node* nexts[26];

				怎么判断某一条路有没有后续呢？怎么区分某一条路是哪个字符的路呢
					某个字符char进来以后，char - 'a',如果char是a，减完以后为0，如果是z，
					减完以后为25，正好对应nexts的下标，比如进来一个b，减完以后为0，则判断
					nexts[0]是否为空，如果为空，说明节点还没有开辟字符a的路，开辟一条
	*/

};

class TireTree
{
public:
	TireTree();
	~TireTree();

public:
	void insert(char* chIn);
	//字符串出现了几次
	int search(char* chIn);

	//在树中删除某一字符串
	void deleteStr(char* chIn);

	//树中有多少字符串是以chIn为前缀的
	int prefixNumber(char* chIn);

	//给定一个节点，返回这个节点扩散出去的路的条数
	int nextNumber(Node* curr);

	//给定一个节点，析构这个节点及这个节点后面的所有节点
	void makeEmpty(Node* root);

public:
	Node* m_head;	//头节点
};

