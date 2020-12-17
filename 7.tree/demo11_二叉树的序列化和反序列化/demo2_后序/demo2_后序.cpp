#include <iostream>
#include <string>
#include "../../Tree/Tree.h"
#include <vector>
#include <sstream>
#include <queue>
#include <stack>

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
		���л��Ķ�������Ψһ�����ң���Ϊ��һ���ַ������һ���ַ����� #�����Բ����������л���ʱ���Ҳ�����һ����Ч�ڵ�
		
	���л�ʱ�����򣬺��򶼿�����ɣ�
	����������õݹ�ķ�ʽ�����л�������û�����⣬����ͺ�����Ϊ��һ���ַ����� #��ֱ�Ӿͷ�����
	������Բ��ôӺ���ǰ�����ַ����ķ�ʽ�ݹ鷴���л������������ܲ��õݹ�ķ�ʽ�����л�����Ϊ�Ҳ�����һ����Ч�ڵ�
*/

void split(const string &s, stack<string> &sq, const char flag)
{
	istringstream iss(s);
	string temp;

	while (getline(iss, temp, flag))
		sq.push(temp);
}

string serialize(TreeNode *root)
{
	//�ͺ����������
	if (root == NULL)
		return "#!";

	//����������
	string str;
	str += serialize(root->left);
	//����������
	str += serialize(root->right);

	//���л���ǰ�ڵ�
	str += to_string(root->data) + "!";
	return str;
}

//ע�⣬stackҪ�������õķ�ʽ����
TreeNode *recursion(stack<string> &stackString)
{
	if (stackString.empty())
		return NULL;

	string str = stackString.top();
	stackString.pop();

	if (str.compare("#") == 0)
		return NULL;

	//�½�һ���ڵ�
	TreeNode *node = new TreeNode;
	//�������������ջ�е�˳���� �����е�˳��ȡ������ �������˳��
	//�����Ȼ�ԭ��ǰ�ڵ�
	node->data = stoi(str);
	//�ٻ�ԭ��ǰ�ڵ��������
	node->right = recursion(stackString);
	//���ԭ��ǰ�ڵ��������
	node->left = recursion(stackString);

	return node;
}

TreeNode *deserialize(string str)
{
	//����ݹ鷴���л�ʱ��ÿ��Ҫ���ַ�����β��ȡ�������Բ���ջ
	stack<string> stackString;
	split(str, stackString, '!');

	return recursion(stackString);
}

void PrintTree(TreeNode *node)
{
	if (node == NULL)
		return;

	PrintTree(node->left);
	PrintTree(node->right);
	cout << node->data << "  ";
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