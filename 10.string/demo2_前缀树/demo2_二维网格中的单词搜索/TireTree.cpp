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
		//�ȿ���ǰ�ڵ��Ƿ��Ѿ��д�����ַ���ȥ��·

		//��ǰ�ڵ���û������·�����½�һ��
		if (curr->nexts.find(chCurr) == curr->nexts.end())
		{
			Node* node = new Node;
			//��������
			curr->nexts[chCurr] = node;
		}

		//��ǰ�ڵ��Ѿ����ˣ������Ѿ��½�������
		curr->nexts[chCurr]->path++;
	
		//��ǰָ������ƶ�
		curr = curr->nexts[chCurr];
	}
	//�ַ��������Ժ󣬵�ǰָ��ָ���ַ��������һ���ַ�
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
		//��һ��û���ҵ��ģ��ͷ���0
		if (curr->nexts.find(chCurr) == curr->nexts.end())
			return 0;

		//�ҵ���
		curr = curr->nexts[chCurr];
	}

	//���ҵ����Ժ�currָ���ַ������һ���ַ�
	return curr->end;

}

void TireTree::deleteStr(char* chIn)
{
	if (search(chIn) == 0)
		return;

	/*
		ɾ��ǰ׺����ĳһ���ַ������������ַ��������в�ֹһ��������;�Ľڵ�path--��
		�����һ���ַ���end--����
		����������ַ���"abcdfg"��"abkjh"���ַ�a��b��path����2
		����Ҫɾ��"abkjh"����������a��b��path--������path����1�Ժ��Ǵ���0��
		���ö��������ߣ���k��path--�����ּ����Ժ�Ϊ0��
		˵��ֻ��һ���ַ���������k����Ϊ����search()�����Ѿ�ȷ��������
		�϶�����"abkjh",��������ַ�������"abkjh"������Ҫɾ������ַ�����
		���Ե��ַ�k��path��Ϊ0�Ժ󣬺����Ľڵ㲻�ñ����ˣ�ֱ���ͷŵ�

	*/
	int nLne = strlen(chIn);
	Node* curr = m_head;
	char chCurr = chIn[0];
	int nPathNum = 0;
	Node* pre = NULL;
	for (int i = 0;i < nLne;i++)
	{
		//�϶�������ַ��������Բ���ȥ�ж��Ƿ����ҵ�
		chCurr = chIn[i];
		pre = curr;		//��¼һ��ǰһ���ڵ㣬����ɾ��map�еļ�¼
		curr = curr->nexts[chCurr];
		nPathNum = curr->path;
		//path��1�Ժ�Ϊ0��˵��ֻ����һ����������ڵ�ͺ������еĽڵ�ֱ���ͷ�
		//�ͷ����Ժ�������ڵ��ǰһ���ڵ��map��ɾ������ڵ�
		if (--nPathNum == 0)
		{
			makeEmpty(curr);
			pre->nexts.erase(chCurr);
			return;
		}
	}
	//path�������Ժ�currָ�����һ���ַ�
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
		//��һ��û���ҵ��ģ��ͷ���0
		if (curr->nexts.find(chCurr) == curr->nexts.end())
			return 0;

		//�ҵ���
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

//����һ���ڵ㣬������ڵ㼰�����Ľڵ㶼�ͷţ�����Ҫ��map��Ҳɾ��
/*
	����root��������"abc","bac"�ȵȣ�Ҫ�ͷ�root���������еĽڵ�
		����root���ж���·�ֱ�·��a,b�ȵ�
*/
																										
/*
			a	      b         c
	ͷ�ڵ�	--> node --> node1 --> node2

	�����node�����ַ�a��ָ��Ľڵ�

	�տ�ʼrootΪͷ�ڵ�
	it��ͷ�ڵ��map�в��Ҵ�ͷ�ڵ��Ƿ��������·�����û�У��Ͱ�root�ڵ��ͷŵ�
	����У������ҵ���<a,node>
	��ʱcurrָ�� a��ָ��Ľڵ㣬chCurrΪa,rootΪͷ�ڵ㣬�ٴν���makeEmpty()��
	��a�ڵ������ȥ��·��ѡһ��������b,<b,node>,��ʱcurrָ�� b��ָ��Ľڵ㣬chCurrΪb��rootΪa
	�ٴν���makeEmpty()����b�ڵ������ȥ��·��ѡһ��������c,<c,node>
	��ʱcurrָ�� c��ָ��Ľڵ㣬chCurrΪc,rootΪb,�ٽ�ȥmakeEmpty()
	rootΪc��ָ��Ľڵ�ʱ��cû�������·������c��ָ��Ľڵ��У�mapû�����ݣ�
	���Բ������forѭ����ֱ�Ӱ�root�ͷŵ�
		c���ͷŵ��Ժ󣬳���ص�mankeEmpty()�����㣬��ʱcurrΪc,chCurrΪc��rootΪb
		��ʱҪ��root��map�е�cɾ��
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
