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

void split(const string &s, queue<string> &sq, const char flag)
{
	istringstream iss(s);
	string temp;

	while (getline(iss, temp, flag))
		sq.push(temp);
}

string serialize(TreeNode *root)
{
	//�������������
	if (root == NULL)
		return "#!";
	//�����е�ǰ�ڵ�
	string str = to_string(root->data) + "!";
	//����������
	str += serialize(root->left);
	//����������
	str += serialize(root->right);
	return str;
}

//ע�⣬queueҪ�������õķ�ʽ����
TreeNode *recursion(queue<string> &queueString)
{
	if (queueString.empty())
		return NULL;
	//ÿ�δӶ�����ȡһ����
	string str = queueString.front();
	queueString.pop();

	if (str.compare("#") == 0)
		return NULL;

	//�½�һ���ڵ�
	TreeNode *node = new TreeNode;
	//����������������ҵ�˳�������Ȱѵ�ǰ�ڵ㻹ԭ
	node->data = stoi(str);
	//�ٻ�ԭ��ǰ�ڵ��������
	node->left = recursion(queueString);
	//���ԭ��ǰ�ڵ��������
	node->right = recursion(queueString);

	return node;
}

TreeNode *deserialize(string str)
{
	queue<string> queueString;
	split(str, queueString, '!');

	return recursion(queueString);
}

void PrintTree(TreeNode *node)
{
	if (node == NULL)
		return;
	cout << node->data << "  ";

	PrintTree(node->left);
	PrintTree(node->right);
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