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
		//�ȿ���ǰ�ڵ��Ƿ��Ѿ��д�����ַ������ȥ��·

		//��ǰ�ڵ���û������·�����½�һ��
		if (curr->nexts[c - 'a'] == NULL)
			curr->nexts[c - 'a'] = new Node;

		//��ǰ�ڵ��Ѿ����ˣ������Ѿ��½�������
		//���ַ�c��ָ��Ľڵ㣬·���Ĵ�����1
		curr->nexts[c - 'a']->path++;

		//��ǰָ������ƶ�
		curr = curr->nexts[c - 'a'];
	}

	//����ʱ����ǰָ��ָ���ַ��������һ���ַ���ָ��Ľڵ�
	curr->end++;
}

bool TireTree::search(string strWord)
{
	if (strWord.length() == 0)
		return false;

	Node *curr = _root;
	for (char c : strWord)
	{
		//��һ��û���ҵ��ģ��ͷ���false
		if (curr->nexts[c - 'a'] == NULL)
			return false;
		curr = curr->nexts[c - 'a'];
	}

	//ÿ���ַ����ҵ��ˣ�Ҫ���ж�һ�½ڵ�� end�Ƿ�Ϊ0�����Ϊ0��˵��strWordֻ��ĳһ���ַ�����ǰ׺��������һ���������������е��ַ���
	return curr->end;
}

void TireTree::deleteStr(string strWord)
{
	if (!search(strWord))
		return;

	/*
		ɾ��ǰ׺����ĳһ���ַ������������ַ��������в�ֹһ��������;�Ľڵ�path--�������һ���ַ���end--���ɡ�
		����������ַ���"abcdfg"��"abkjh"���ַ�a��b��path����2
		����Ҫɾ��"abkjh"����������a��b��path--������path����1�Ժ��Ǵ���0��
		���ö��������ߣ���k��path--�����ּ����Ժ�Ϊ0��
		˵��ֻ��һ���ַ���������k����Ϊ����search()�����Ѿ�ȷ��������
		�϶�����"abkjh"������Ҫɾ������ַ��������ַ�k��path��Ϊ0�Ժ󣬺����Ľڵ㲻�ñ����ˣ�ֱ���ͷŵ�

	*/
	Node *curr = _root;
	Node *pre = NULL;
	for (char c : strWord)
	{
		//�϶�������ַ���������ȥ�ж��Ƿ����ҵ�
		pre = curr; //��¼һ��ǰһ���ڵ�
		curr = curr->nexts[c - 'a'];
		//path��1�Ժ�Ϊ0��˵��ֻ����һ����������ڵ�ͺ������еĽڵ�ֱ���ͷ�
		if (--curr->path == 0)
		{
			//������ɾ��ǰһ���ڵ�ָ��curr�ڵ��·������һ����makeEmpty()��������
			pre->nexts[c - 'a'] = NULL;
			makeEmpty(curr);

			return;
		}
	}

	//path�������Ժ�currָ�����һ���ַ�
	curr->end--;
}

int TireTree::prefixNumber(string strWord)
{
	Node *curr = _root;
	for (char c : strWord)
	{
		//��һ��û���ҵ��ģ��ͷ���0
		if (curr->nexts[c - 'a'] == NULL)
			return 0;
		curr = curr->nexts[c - 'a'];
	}

	//·�����ַ������ж��ٸ�
	return curr->path;
}

int TireTree::nextNumber(Node *curr)
{
	//�������mapһ����ֱ�ӷ���map��size()�����ˣ���Ҫ��������
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
		����һ���ڵ㣬������ڵ㼰�����Ľڵ㶼�ͷ�
		dfs�����ͷ�
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
