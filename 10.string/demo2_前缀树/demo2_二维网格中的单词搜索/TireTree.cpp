#include "TireTree.h"



TireTree::TireTree()
{
	m_head = new Node;
}


TireTree::~TireTree()
{
	makeEmpty(m_head);
}

void TireTree::insert(char* chIn)
{
	if (chIn == NULL)
		return;

	int nLne = strlen(chIn);
	Node* curr = m_head;
	char chCurr = chIn[0];

	for (int i = 0;i < nLne;i++)
	{
		chCurr = chIn[i];
		//先看当前节点是否已经有从这个字符出去的路

		//当前节点中没有这条路径，新建一个
		if (curr->nexts.find(chCurr) == curr->nexts.end())
		{
			Node* node = new Node;
			//关联起来
			curr->nexts[chCurr] = node;
		}

		//当前节点已经有了，或者已经新建出来了
		curr->nexts[chCurr]->path++;
	
		//当前指针向后移动
		curr = curr->nexts[chCurr];
	}
	//字符串走完以后，当前指针指向字符串的最后一个字符
	curr->end++;
}

int TireTree::search(char* chIn)
{
	if (chIn == NULL)
		return 0;

	int nLne = strlen(chIn);
	Node* curr = m_head;
	char chCurr = chIn[0];

	for (int i = 0;i < nLne;i++)
	{
		chCurr = chIn[i];
		//有一个没有找到的，就返回0
		if (curr->nexts.find(chCurr) == curr->nexts.end())
			return 0;

		//找到了
		curr = curr->nexts[chCurr];
	}

	//都找到了以后，curr指向字符串最后一个字符
	return curr->end;

}

void TireTree::deleteStr(char* chIn)
{
	if (search(chIn) == 0)
		return;

	/*
		删除前缀树中某一个字符串，如果这个字符串在树中不止一个，让沿途的节点path--，
		让最后一个字符的end--即可
		如果树中有字符串"abcdfg"和"abkjh"，字符a和b的path都是2
		现在要删除"abkjh"，遍历，让a和b的path--，发现path减完1以后还是大于0，
		不用动，向下走，让k的path--，发现减完以后为0，
		说明只有一个字符串经过了k，因为经过search()函数已经确定了树中
		肯定是有"abkjh",所以这个字符串就是"abkjh"，现在要删除这个字符串，
		所以当字符k的path变为0以后，后续的节点不用遍历了，直接释放掉

	*/
	int nLne = strlen(chIn);
	Node* curr = m_head;
	char chCurr = chIn[0];
	int nPathNum = 0;
	Node* pre = NULL;
	for (int i = 0;i < nLne;i++)
	{
		//肯定有这个字符串，所以不用去判断是否能找到
		chCurr = chIn[i];
		pre = curr;		//记录一下前一个节点，用于删除map中的记录
		curr = curr->nexts[chCurr];
		nPathNum = curr->path;
		//path减1以后为0，说明只有这一个，让这个节点和后面所有的节点直接释放
		//释放完以后，让这个节点的前一个节点的map中删除这个节点
		if (--nPathNum == 0)
		{
			makeEmpty(curr);
			pre->nexts.erase(chCurr);
			return;
		}
	}
	//path都减完以后，curr指向最后一个字符
	curr->end--;
}

int TireTree::prefixNumber(char* chIn)
{
	if (chIn == NULL)
		return 0;
	int nLne = strlen(chIn);
	Node* curr = m_head;
	char chCurr = chIn[0];
	for (int i = 0;i < nLne;i++)
	{
		chCurr = chIn[i];
		//有一个没有找到的，就返回0
		if (curr->nexts.find(chCurr) == curr->nexts.end())
			return 0;

		//找到了
		curr = curr->nexts[chCurr];
	}

	return curr->path;
}

int TireTree::nextNumber(Node* curr)
{
	return curr->nexts.size();
}

void TireTree::makeEmpty(Node* root)
{

//给定一个节点，把这个节点及后续的节点都释放，并且要把map中也删除
/*
	比如root中现在有"abc","bac"等等，要释放root及后面所有的节点
		现在root中有多条路分别路过a,b等等
*/
																										
/*
			a	      b         c
	头节点	--> node --> node1 --> node2

	把这个node叫做字符a所指向的节点

	刚开始root为头节点
	it在头节点的map中查找从头节点是否有延伸的路，如果没有，就把root节点释放掉
	如果有，比如找到了<a,node>
	此时curr指向 a所指向的节点，chCurr为a,root为头节点，再次进入makeEmpty()，
	从a节点延伸出去的路中选一条，比如b,<b,node>,此时curr指向 b所指向的节点，chCurr为b，root为a
	再次进入makeEmpty()，从b节点延伸出去的路中选一条，比如c,<c,node>
	此时curr指向 c所指向的节点，chCurr为c,root为b,再进去makeEmpty()
	root为c所指向的节点时，c没有延伸的路，所以c所指向的节点中，map没有数据，
	所以不会进入for循环，直接把root释放掉
		c被释放掉以后，程序回到mankeEmpty()结束点，此时curr为c,chCurr为c，root为b
		此时要把root的map中的c删掉
*/

	map<char, Node*>::iterator it;

	while (!root->nexts.empty())
	{
		it = root->nexts.begin();

		char chCurr = it->first;

		Node* curr = it->second;
		if (curr != NULL)
		{
			makeEmpty(curr);
			root->nexts.erase(it);	
		}
	}

	if (root)
	{
		delete root;
		root = NULL;
	}


}
