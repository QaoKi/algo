#ifndef _TRIE_TREE_H_
#define _TRIE_TREE_H_
#include <iostream>
#include <string>
#include <memory.h>

using namespace std;

/*
	需要知道一个节点能延伸出多少条路
	比如，如果字符串中只有小写字母，26个，那么一个节点最多延伸出26条路。
			如果有特殊字符，一个字节的char，取值范围为 0~255，最多延伸出256条路。
			也可以申请一个map<char,Node>，key可以有很多，代表延伸出很多条路，value代表这个字符指向的节点，
			用map内存会消耗更少，但是时间上会消耗更多。因为每次都要find()		
*/

//假设都是小写字母，一共26个
const int R = 26;
struct Node
{

	int path; //有多少字符串路过了这个节点
	int end;  //有多少字符串是以这个节点结尾的

	/*
		每个节点，都有大小为R的Node*数组，保存指向Node节点的指针。
		数组的每一个值，都是一个指向Node节点的指针。
		数组的每一个下标都表示以一个字母延伸出去的路。
		那么，给定一个字母char，怎么判断该节点是否有从char延伸出去的路？怎么区分某一条路是哪个字符的路呢？
			用char - 'a',如果char是'a'，减完以后为0，如果是'z'，减完以后为25，正好对应nexts的下标，
			如果 nexts[i] != NULL，说明该节点在下标 i 处指向了另一个节点，也就是已经有一条沿着字符 i+'a' 延伸出去的路。

		需要注意的是，字母不是保存在节点中的，nexts是路径信息，字母保存在路径上
	*/

	//假设数组中，nexts[0] = nodeA，有从字符a出发的路径，我们把这个nodeA节点叫做字符a所指向的节点
	Node *nexts[26] = {NULL};
	Node()
	{
		path = 0;
		end = 0;
	}
};

class TireTree
{
public:
	TireTree();
	~TireTree();

public:
	void insert(string strWord);

	//是否存在 strWord这条字符串
	bool search(string strWord);

	//在树中删除某一字符串
	void deleteStr(string strWord);

	//树中有多少字符串是以strWord为前缀的
	int prefixNumber(string strWord);

	//给定一个节点，返回这个节点扩散出去的路的条数
	int nextNumber(Node *curr);

private:
	//给定一个节点，析构这个节点及这个节点后面的所有节点
	void makeEmpty(Node *node);

public:
	Node *_root; //头节点
};

#endif