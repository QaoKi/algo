#include <iostream>
#include <string>
#include "../../Tree/Tree.h"
#include <vector>
#include <sstream>
#include <queue>

using namespace std;

/*
	�����������л�����������������������һ������ʾ���Ľṹ���������ַ�����ʾ��ͬʱҲ��
	������ַ�������ת��Ϊ��
*/

/*
			����һ��������		 1
							2  		3
					     4	  5	  6	  7
			�������Ϊ 1 2 4 5 3 6 7
			�ã���ʾһ���ڵ�Ľ�������#��ʾnull
			4����������������Ϊnull,����Ϊ4!#!#!
			�ܵ�Ϊ��1!2!4!#!#!5!#!#!3!6!#!#!7!#!#!
			����
				#!4!#!2!#!5!#!1!#!6!#!3!#!7!#!
			����:
				#!#!4!#!#!5!2!#!#!6!#!#!7!3!1!
			����
				1!2!3!4!5!6!7!
*/

/*
	������������������л��ͷ����л���
		��Ϊ��������õ��Ķ�������Ψһ,���ܱ�֤�����л��Ķ�����Ϊԭ������.
		��������
				 	1
				2  		3
			#	  #	  #	  #
		����
						3
					1		#
				2	  #   
			#	   #
		���������Ϊ  #!2!#!1!#!3!#!
		���л���Ψһ�����ң���Ϊ��һ���ַ������һ���ַ����� #�����Բ����������л���ʱ���Ҳ�����һ����Ч�ڵ�
		
	���л�ʱ�����򣬺��򶼿�����ɣ�
	����������õݹ�ķ�ʽ�����л�������û�����⣬����ͺ�����Ϊ��һ���ַ����� #��ֱ�Ӿͷ�����
	������Բ��ôӺ���ǰ�����ַ��ķ�ʽ�ݹ鷴���л������������ܲ��õݹ�ķ�ʽ�����л�����Ϊ�Ҳ�����һ����Ч�ڵ�
*/

void split(const string &s, vector<string> &sq, const char flag)
{
	istringstream iss(s);
	string temp;

	while (getline(iss, temp, flag))
		sq.push_back(temp);
}

string serialize(TreeNode *root)
{
	//�Ͳ����������
	if (root == NULL)
		return "#!";
	queue<TreeNode *> queueNode;
	queueNode.push(root);

	string str;
	while (!queueNode.empty())
	{
		TreeNode *curr = queueNode.front();
		queueNode.pop();

		if (curr == NULL)
			str += "#!";
		else
		{
			str += to_string(curr->data) + "!";
			//���������ǲ��� null�����ӽ�ȥ����Ϊ�����null�Ļ���ҲҪ��� #!
			//��Ȼ��Ҫ�ж�һ�� curr �ǲ��� null
			queueNode.push(curr->left);
			queueNode.push(curr->right);
		}
	}

	return str;
}

/*
	�����л�ʱ��ֻ�и��ڵ���ǲ���һ���ڵ㣬�����ļ��㣬�ڵ�������ǳɶԵģ��ֱ��Ӧ�����ӽڵ�
	��split�ַ�����ʱ�򣬰ѽ���ŵ�һ�� vector�У�����ͨ���±���ʣ����±�0��ֵ�����������ڵ㣬
	�±�1,2�����������ڵ����������������
*/

TreeNode *deserialize(string str)
{
	//�������л�ʱ����Ҫ��ͨ���±���ʣ����Բ���vector
	vector<string> vectorString;
	split(str, vectorString, '!');

	//�����һ���ڵ㣬Ҳ���Ǹ��ڵ��ǿ�
	if (vectorString[0] == "#")
		return NULL;
	//�õ�һ���ַ��������ڵ�
	TreeNode *newTree = new TreeNode(stoi(vectorString[0]));
	//����һ�����У���ŷ� null �ڵ㣬���еĹ��ܣ������л�ʱ�Ķ�������
	queue<TreeNode *> queueNode;
	queueNode.push(newTree);

	//���±�1��ʼ���������ڵ�
	int index = 1;
	while (!queueNode.empty())
	{
		//ÿ�δӶ�����ȡһ���ڵ㣬��������ڵ��������������������Ĭ�϶���null
		TreeNode *curr = queueNode.front();
		queueNode.pop();
		//����������
		if (vectorString[index] != "#")
		{
			curr->left = new TreeNode(stoi(vectorString[index]));
			//����ǰ�ڵ����ڵ���뵽�����У��´�ѭ��ʱȡ������������������
			queueNode.push(curr->left);
		}

		//����������
		index++;
		if (vectorString[index] != "#")
		{
			curr->right = new TreeNode(stoi(vectorString[index]));
			//����ǰ�ڵ���ҽڵ���뵽������
			queueNode.push(curr->right);
		}

		index++;
	}
	return newTree;
}

void PrintTree(TreeNode *node)
{
	if (node == NULL)
		return;
	queue<TreeNode *> queueNode;
	queueNode.push(node);

	string str;
	while (!queueNode.empty())
	{
		int size = queueNode.size();
		for (int i = 0; i < size; i++)
		{
			TreeNode *curr = queueNode.front();
			queueNode.pop();

			cout << curr->data << "  ";
			if (curr->left != NULL)
				queueNode.push(curr->left);
			if (curr->right != NULL)
				queueNode.push(curr->right);
		}
	}
}

int main()
{
	TreeNode *root = new TreeNode;
	root->data = 1;

	root->left = new TreeNode;
	root->right = new TreeNode;
	root->left->data = 2;
	root->right->data = 3;

	root->left->left = new TreeNode;
	root->left->left->data = 4;
	root->left->right = new TreeNode;
	root->left->right->data = 5;

	root->right->left = new TreeNode;
	root->right->left->data = 6;
	root->right->right = new TreeNode;
	root->right->right->data = 7;

	PrintTree(root);
	cout << endl;
	//���򣬵ݹ�
	string str = serialize(root);
	cout << "�������л���" << str << endl;
	//���ַ����ٱ�Ϊ��
	TreeNode *newTree = deserialize(str);
	PrintTree(newTree);
	cout << endl;

	return 0;
}