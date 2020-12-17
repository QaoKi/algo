#ifndef _TRIE_TREE_H_
#define _TRIE_TREE_H_
#include <iostream>
#include <string>
#include <memory.h>

using namespace std;

/*
	��Ҫ֪��һ���ڵ��������������·
	���磬����ַ�����ֻ��Сд��ĸ��26������ôһ���ڵ���������26��·��
			����������ַ���һ���ֽڵ�char��ȡֵ��ΧΪ 0~255����������256��·��
			Ҳ��������һ��map<char,Node>��key�����кܶ࣬����������ܶ���·��value��������ַ�ָ��Ľڵ㣬
			��map�ڴ�����ĸ��٣�����ʱ���ϻ����ĸ��ࡣ��Ϊÿ�ζ�Ҫfind()		
*/

//���趼��Сд��ĸ��һ��26��
const int R = 26;
struct Node
{

	int path; //�ж����ַ���·��������ڵ�
	int end;  //�ж����ַ�����������ڵ��β��

	/*
		ÿ���ڵ㣬���д�СΪR��Node*���飬����ָ��Node�ڵ��ָ�롣
		�����ÿһ��ֵ������һ��ָ��Node�ڵ��ָ�롣
		�����ÿһ���±궼��ʾ��һ����ĸ�����ȥ��·��
		��ô������һ����ĸchar����ô�жϸýڵ��Ƿ��д�char�����ȥ��·����ô����ĳһ��·���ĸ��ַ���·�أ�
			��char - 'a',���char��'a'�������Ժ�Ϊ0�������'z'�������Ժ�Ϊ25�����ö�Ӧnexts���±꣬
			��� nexts[i] != NULL��˵���ýڵ����±� i ��ָ������һ���ڵ㣬Ҳ�����Ѿ���һ�������ַ� i+'a' �����ȥ��·��

		��Ҫע����ǣ���ĸ���Ǳ����ڽڵ��еģ�nexts��·����Ϣ����ĸ������·����
	*/

	//���������У�nexts[0] = nodeA���д��ַ�a������·�������ǰ����nodeA�ڵ�����ַ�a��ָ��Ľڵ�
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

	//�Ƿ���� strWord�����ַ���
	bool search(string strWord);

	//������ɾ��ĳһ�ַ���
	void deleteStr(string strWord);

	//�����ж����ַ�������strWordΪǰ׺��
	int prefixNumber(string strWord);

	//����һ���ڵ㣬��������ڵ���ɢ��ȥ��·������
	int nextNumber(Node *curr);

private:
	//����һ���ڵ㣬��������ڵ㼰����ڵ��������нڵ�
	void makeEmpty(Node *node);

public:
	Node *_root; //ͷ�ڵ�
};

#endif