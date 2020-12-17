#include <iostream>
#include <string>
#include <queue>
#include "../Tree/Tree.h"

using namespace std;

/*
	��һ���������������Ⱥ���С���
	����һ����
				1
		2				3
					4		5
				6
	������Ϊ�����Ҷ�ӽڵ����ȣ���С���Ϊ��ǳ��Ҷ�ӽڵ�����
	����������Ϊ4����С���Ϊ2

*/

/*
	˼·��
		���ַ�����
		1���ݹ�DFS���Ӹ��ڵ㿪ʼ���Ҹ��ڵ���������max��min���͸��ڵ���������max��min���Ƚ�һ�£��ټ��ϸ��ڵ�Ϳ�����
		2��BFS��������б�����������ʱ�������ĵ�һ��Ҷ�ӽڵ������С��ȵĽڵ㡣�����������һ�㣬���������ȵĽڵ�
*/

//�ݹ�������
int recursion_maxDepth(TreeNode *root)
{
	if (root == NULL)
		return 0;
	//���������ĸ߶�
	int left = recursion_maxDepth(root->left);
	//���������ĸ߶�
	int right = recursion_maxDepth(root->right);

	//�������������������нϴ�ĸ߶ȣ������Լ�����ĸ߶�
	return left > right ? left + 1 : right + 1;
}

//�ݹ���С���
int recursion_minDepth(TreeNode *root)
{
	if (root == NULL)
		return 0;
	int left = recursion_minDepth(root->left);
	int right = recursion_minDepth(root->right);
	//Ҫ���⴦��һ�£������������Ϊ�գ�������Ϊ��
	//���� left����1��right����0��ֱ�ӱȽ�����ֵ�Ĵ�С��Ȼ��ѽ�С�ļ�1 ���أ������
	if (root->left == NULL || root->right == NULL)
		//left �� right ����һ������0���������ĸ��Ͳ����ˣ�����д���Щ
		return left + right + 1;

	//��������������������
	return left < right ? left + 1 : right + 1;
}

//BFS������
int BFS_maxDepth(TreeNode *root)
{
	if (root == NULL)
		return 0;
	queue<TreeNode *> queueNode;
	queueNode.push(root);

	int depth = 0;
	while (!queueNode.empty())
	{
		//��һ����ֻҪ�нڵ㣬�����ͼ�1
		depth++;
		int size = queueNode.size();
		//������һ������нڵ�
		for (int i = 0; i < size; i++)
		{
			TreeNode *curr = queueNode.front();
			queueNode.pop();

			if (curr->left != NULL)
				queueNode.push(curr->left);
			if (curr->right != NULL)
				queueNode.push(curr->right);
		}
	}

	return depth;
}

//BFS��С���
int BFS_minDepth(TreeNode *root)
{
	if (root == NULL)
		return 0;
	queue<TreeNode *> queueNode;
	queueNode.push(root);

	int depth = 0;
	while (!queueNode.empty())
	{
		//��һ����ֻҪ�нڵ㣬�����ͼ�1
		//ע�⣬BFS��С��ȵ�ʱ�� depth++Ҫ��ִ�У���Ϊ��forѭ���Ĺ����п��ܻ�return���������ִ��++����Ȼ���1
		depth++;
		int size = queueNode.size();
		//������һ������нڵ�
		for (int i = 0; i < size; i++)
		{
			TreeNode *curr = queueNode.front();
			queueNode.pop();

			//������һ��Ҷ�ӽڵ㣬����ȷ���
			if (curr->left == NULL && curr->right == NULL)
				return depth;
			if (curr->left != NULL)
				queueNode.push(curr->left);
			if (curr->right != NULL)
				queueNode.push(curr->right);
		}
	}

	return depth;
}

int main()
{
	TreeNode *root = new TreeNode;
	root->data = 1;

	//root->left = new TreeNode;
	root->right = new TreeNode;
	//root->left->data = 2;
	root->right->data = 3;

	//root->left->left = new TreeNode;
	//root->left->left->data = 4;
	//root->left->right = new TreeNode;
	//root->left->right->data = 5;

	root->right->left = new TreeNode;
	root->right->left->data = 6;
	root->right->right = new TreeNode;
	root->right->right->data = 7;

	root->right->right->left = new TreeNode;
	root->right->right->left->data = 8;

	cout << "������:  " << recursion_maxDepth(root) << endl;

	return 0;
}