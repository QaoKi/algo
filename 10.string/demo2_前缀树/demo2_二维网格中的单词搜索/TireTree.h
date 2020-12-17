#pragma once

#include <iostream>
#include <string>
#include <map>

using namespace std;


struct Node
{
	int path;		//�ж����ַ���·��������ڵ�
	int end;		//�ж����ַ�����������ڵ��β��
	map<char, Node*> nexts;

	Node()
	{
		path = 0;
		end = 0;
	}
	
	/*
		��Ҫ��¼һ���ڵ��ܲ���������·
		���磬����ַ�����ֻ����ĸ��26����ĸ��һ���ڵ������26��·
				�����ַ�һ��95����Ҳ����Ϊÿ���ڵ㽨��95��·
				Ҳ��������һ��map<char,Node>��key�����кܶ࣬�����кܶ���·��value��������ַ�ָ��Ľڵ�

				���綼����ĸ�����26��·
				Node* nexts[26];

				��ô�ж�ĳһ��·��û�к����أ���ô����ĳһ��·���ĸ��ַ���·��
					ĳ���ַ�char�����Ժ�char - 'a',���char��a�������Ժ�Ϊ0�������z��
					�����Ժ�Ϊ25�����ö�Ӧnexts���±꣬�������һ��b�������Ժ�Ϊ0�����ж�
					nexts[0]�Ƿ�Ϊ�գ����Ϊ�գ�˵���ڵ㻹û�п����ַ�a��·������һ��
	*/

};

class TireTree
{
public:
	TireTree();
	~TireTree();

public:
	void insert(char* chIn);
	//�ַ��������˼���
	int search(char* chIn);

	//������ɾ��ĳһ�ַ���
	void deleteStr(char* chIn);

	//�����ж����ַ�������chInΪǰ׺��
	int prefixNumber(char* chIn);

	//����һ���ڵ㣬��������ڵ���ɢ��ȥ��·������
	int nextNumber(Node* curr);

	//����һ���ڵ㣬��������ڵ㼰����ڵ��������нڵ�
	void makeEmpty(Node* root);

public:
	Node* m_head;	//ͷ�ڵ�
};

