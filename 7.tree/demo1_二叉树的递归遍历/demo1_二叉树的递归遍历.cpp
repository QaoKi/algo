#include <iostream>
#include <string>
#include "../Tree/Tree.h"

using namespace std;
/*
	�������������������洢
	������ȫ������������洢�ȽϺã��±� i ����ڵ��� 2 * i + 1���ҽڵ�Ϊ 2 * i + 2
	���������ȫ������������Ŀ�϶�Ƚ϶࣬�˷ѿռ�
*/

/*
	�ݹ������ʱ�临�Ӷ�O(n)
	ÿ���ڵ��������Σ����ʴ˽ڵ��ʱ��һ�Σ�������������������ʱ��һ�Σ�������
	������������ʱ��һ�Σ�һ������
*/
void preOrder(TreeNode *root)
{
	if (root == NULL)
		return;
	cout << root->data << "  ";
	preOrder(root->left);
	preOrder(root->right);
}

void inOrder(TreeNode *root)
{
	if (root == NULL)
		return;
	inOrder(root->left);
	cout << root->data << "  ";
	inOrder(root->right);
}

void postOrder(TreeNode *root)
{
	if (root == NULL)
		return;
	postOrder(root->left);
	postOrder(root->right);
	cout << root->data << "  ";
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

	//����������ȱ������ڵ㣬�ٱ�����������������������
	cout << "�������Ϊ��  ";
	preOrder(root);
	cout << endl;

	//����������ȱ������������ٱ������ڵ㣬������������
	cout << "�������Ϊ��  ";
	inOrder(root);
	cout << endl;

	//����������ȱ������������ٱ��������������������ڵ�
	cout << "�������Ϊ��  ";
	postOrder(root);
	cout << endl;

	return 0;
}