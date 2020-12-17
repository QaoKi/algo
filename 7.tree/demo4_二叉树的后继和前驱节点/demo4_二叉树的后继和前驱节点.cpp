#include <iostream>
#include <string>
#include "../Tree/Tree.h"

using namespace std;

/*
	��Ŀ��
		������һ���µĶ������ڵ����ͣ��ýṹ����ͨ�������ڵ�ṹ����һ��ָ�򸸽ڵ��parentָ�롣
		������һ��Node���͵Ľڵ���ɵĶ�����������ÿ���ڵ��parentָ�붼��ȷ��ָ���Լ��ĸ��ڵ㣬
		ͷ�ڵ��parentָ��null��ֻ��һ���ڶ������е�ĳ���ڵ� node����ʵ�ַ���node�ĺ�̽ڵ�ĺ�����

		ǰ���ڵ�ͺ�̽ڵ㣬ֻ����������У�ǰ���ڵ�͸��ڵ��ǲ�һ����
		�ڶ���������������������У� node����һ���ڵ����node�ĺ�̽ڵ㡣
		����һ��������		1 
					  2  	      3
				   4	 5	   6     7

		�������Ϊ��4 2 5 1 6 3 7
		4�ĺ�̽ڵ�Ϊ2��2�ĺ�̽ڵ�Ϊ5
		2��ǰ���ڵ�Ϊ4��5��ǰ���ڵ�Ϊ2

		��չ������һ���ڵ�K��������ڵ��ǰ���ڵ㣬ǰ���ڵ�͸��ڵ��ǲ�һ����

*/

/*
	˼·��
		�������е�ĳһ�ڵ�K���ҵ��ýڵ�ĺ�̽ڵ㣬
		1������K�ڵ㣬�ҵ����ڵ㣬�ٶ�������������������ҵ�K�ڵ�ĺ�̽ڵ�
			������ΪҪ���������������Ը��Ӷȸ�
		2��K�ڵ�������ҽڵ㣬���ҽڵ�Ϊ A����ô���ĺ�̽ڵ��ǣ�
				�� A Ϊ���ڵ������������߽�Ľڵ㣬��Ϊ���������˳��Ϊ�����ң�
				���Ե�һ���ڵ����ҽڵ�ʱ������������������һ���µ���������µ�������Ҫ��������Ľڵ�
				��� A û����ڵ㣬��ôK�ڵ�ĺ�̽ڵ���� A
		   K�ڵ�û���ҽڵ㣬����parentָ�������ĸ��ڵ�X��
			  ���K��X����ڵ㣬��ôK�ĺ�̽ڵ����X����Ϊ�������Ϊ�����ң�
					K�ڵ�����ڵ㣬���ӱ������Ժ�Ҫ�����У�Ҳ�������ĸ��ڵ�X
			  ���K��X���ҽڵ㣬����X��parentָ�룬ȥ��X�ĸ��ڵ�Y������X�ǲ���Y����ڵ㣬����ǣ�
					��ôK�ĺ�̽ڵ����Y��������ǣ�����������Y�ĸ��ڵ�Z������Y�ǲ���Z����ڵ㣬����ǣ�
					��ôK�ĺ�̽ڵ����Z�����Ǿ������ң��Ҳ�����û�к�̽ڵ�

					��ΪK��X���ҽڵ㣬������K�Ժ�X��Ϊ�У��Ѿ��������ˣ��Ͳ���Ҫ�ٱ�������ʱ�����ң�
					���X�������ڵ�Y����ڵ㣬������꣬Ҫ�����У���ôY����K�ĺ�̽ڵ㣬
					���X����Y���ҽڵ㣬˵��Y��Ϊ�����Ѿ��������ˣ���������


		��չ������һ���ڵ�K��������ڵ��ǰ���ڵ㣬ǰ���ڵ�͸��ڵ��ǲ�һ����
			K�������ڵ㣬ǰ���ڵ��Ϊ��ڵ�
			K���û����ڵ㣬�����ĸ��ڵ㣬������Ǹ��ڵ���ҽڵ㣬��ôǰ���ڵ�Ϊ���ڵ㣬
				������Ǹ��ڵ���ҽڵ㣬�Ҹ��ڵ�ĸ��ڵ㣬�����ڵ��ǲ��Ǹ��ڵ�ĸ��ڵ���ҽڵ㡣����

*/

TreeNode *GetNext(TreeNode *node)
{
	if (node == NULL)
		return NULL;

	TreeNode *retNode = NULL;
	//����ýڵ�������������������������Ľڵ㣬���Ǻ�̽ڵ�
	if (node->right != NULL)
	{
		//���������û������������ô���������Ǻ�̽ڵ�
		retNode = node->right;
		//�������������������һֱ������
		while (retNode->left != NULL)
		{
			retNode = retNode->left;
		}
	}
	else
	{
		//û�����������Ҹýڵ�ĸ��ڵ㣬�����ýڵ��ǲ��Ǹ��ڵ������
		TreeNode *curr = node;
		TreeNode *pre = node->parent;
		while (pre != NULL)
		{
			//����Ǹ��ڵ�����ӣ���ô���ڵ���Ǻ�̽ڵ�
			if (pre->left == curr)
			{
				retNode = pre;
				break;
			}
			else
			{
				//������������ң��������ڵ��ǲ���үү�ڵ������
				curr = pre;
				pre = pre->parent;
			}
		}
	}

	return retNode;
}

//��ǰ���ڵ�
TreeNode *GetPrecursor(TreeNode *node)
{
	if (node == NULL)
		return;
	TreeNode *retNode = NULL;
	//�������������ǰ���ڵ����������
	if (retNode->left != NULL)
		retNode = retNode->left;
	else
	{
		//û�����������Ҹ��ڵ㣬����Ǹ��ڵ������������ôǰ���ڵ���Ǹ��ڵ�
		//������Ǹ��ڵ��������������������
		TreeNode *curr = node;
		TreeNode *pre = node->parent;
		while (pre != NULL)
		{
			if (pre->right == curr)
			{
				retNode = pre->right;
				break;
			}
			else
			{
				curr = pre;
				pre = pre->parent;
			}
		}
	}

	return retNode;
}

int main()
{
	TreeNode *root = new TreeNode;
	root->data = 1;
	root->parent = NULL;

	root->left = new TreeNode;
	root->right = new TreeNode;
	root->left->data = 2;
	root->left->parent = root;
	root->right->data = 3;
	root->right->parent = root;

	root->left->left = new TreeNode;
	root->left->left->data = 4;
	root->left->left->parent = root->left;
	root->left->right = new TreeNode;
	root->left->right->data = 5;
	root->left->right->parent = root->left;

	root->right->left = new TreeNode;
	root->right->left->data = 6;
	root->right->left->parent = root->right;
	root->right->right = new TreeNode;
	root->right->right->data = 7;
	root->right->right->parent = root->right;

	//��һ���ڵ㣬������ڵ�ĺ�̽ڵ�
	TreeNode *curr = root->right->left;
	TreeNode *next = GetNext(curr);
	if (next != NULL)
		cout << "�����ڵ㣺 " << next->data << endl;
	else
		cout << "û�к����ڵ�" << endl;

	TreeNode *pre = GetPrecursor(curr);
	if (pre != NULL)
		cout << "ǰ���ڵ㣺 " << pre->data << endl;
	else
		cout << "û��ǰ���ڵ�" << endl;

	return 0;
}