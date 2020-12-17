#include "TireTree.h"

TireTree::TireTree()
{
	_root = new Node;
}

TireTree::~TireTree()
{
	makeEmpty(_root);
}

void TireTree::insert(string strWord)
{
	if (strWord.length() == 0)
		return;
	Node *curr = _root;
	for (char c : strWord)
	{
		//先看当前节点是否已经有从这个字符延伸出去的路

		//当前节点中没有这条路径，新建一个
		if (curr->nexts[c - 'a'] == NULL)
			curr->nexts[c - 'a'] = new Node;

		//当前节点已经有了，或者已经新建出来了
		//被字符c所指向的节点，路过的次数加1
		curr->nexts[c - 'a']->path++;

		//当前指针向后移动
		curr = curr->nexts[c - 'a'];
	}

	//到此时，当前指针指向字符串的最后一个字符所指向的节点
	curr->end++;
}

bool TireTree::search(string strWord)
{
	if (strWord.length() == 0)
		return false;

	Node *curr = _root;
	for (char c : strWord)
	{
		//有一个没有找到的，就返回false
		if (curr->nexts[c - 'a'] == NULL)
			return false;
		curr = curr->nexts[c - 'a'];
	}

	//每个字符都找到了，要再判断一下节点的 end是否为0，如果为0，说明strWord只是某一个字符串的前缀，并不是一个完整保存在树中的字符串
	return curr->end;
}

void TireTree::deleteStr(string strWord)
{
	if (!search(strWord))
		return;

	/*
		删除前缀树中某一个字符串，如果这个字符串在树中不止一个，让沿途的节点path--，让最后一个字符的end--即可。
		如果树中有字符串"abcdfg"和"abkjh"，字符a和b的path都是2
		现在要删除"abkjh"，遍历，让a和b的path--，发现path减完1以后还是大于0，
		不用动，向下走，让k的path--，发现减完以后为0，
		说明只有一个字符串经过了k，因为经过search()函数已经确定了树中
		肯定是有"abkjh"，现在要删除这个字符串，当字符k的path变为0以后，后续的节点不用遍历了，直接释放掉

	*/
	Node *curr = _root;
	Node *pre = NULL;
	for (char c : strWord)
	{
		//肯定有这个字符串，不用去判断是否能找到
		pre = curr; //记录一下前一个节点
		curr = curr->nexts[c - 'a'];
		//path减1以后为0，说明只有这一个，让这个节点和后面所有的节点直接释放
		if (--curr->path == 0)
		{
			//别忘了删除前一个节点指向curr节点的路径，这一步在makeEmpty()中做不到
			pre->nexts[c - 'a'] = NULL;
			makeEmpty(curr);

			return;
		}
	}

	//path都减完以后，curr指向最后一个字符
	curr->end--;
}

int TireTree::prefixNumber(string strWord)
{
	Node *curr = _root;
	for (char c : strWord)
	{
		//有一个没有找到的，就返回0
		if (curr->nexts[c - 'a'] == NULL)
			return 0;
		curr = curr->nexts[c - 'a'];
	}

	//路过该字符串的有多少个
	return curr->path;
}

int TireTree::nextNumber(Node *curr)
{
	//这个不像map一样，直接返回map的size()就行了，需要遍历数组
	int pathNum = 0;
	for (int i = 0; i < 26; i++)
	{
		if (curr->nexts[i] != NULL)
			pathNum++;
	}
	return pathNum;
}

void TireTree::makeEmpty(Node *node)
{

	/*
		给定一个节点，把这个节点及后续的节点都释放
		dfs遍历释放
	*/

	for (int i = 0; i < 26; i++)
	{
		if (node->nexts[i] != NULL)
		{
			makeEmpty(node->nexts[i]);
		}
	}

	if (node)
	{
		delete node;
		node = NULL;
	}
}
