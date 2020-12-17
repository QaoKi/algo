#include <iostream>
#include <string>
#include <queue>
#include "../Tree/Tree.h"

using namespace std;

/*
	求一个二叉树的最大深度和最小深度
	比如一棵树
				1
		2				3
					4		5
				6
	最大深度为最深的叶子节点的深度，最小深度为最浅的叶子节点的深度
	所以最大深度为4，最小深度为2

*/

/*
	思路：
		三种方法：
		1，递归DFS，从根节点开始，找根节点左子树的max和min，和根节点右子树的max和min，比较一下，再加上根节点就可以了
		2，BFS，按层进行遍历，遍历的时候，遇到的第一个叶子节点就是最小深度的节点。遍历到的最后一层，就是最大深度的节点
*/

//递归最大深度
int recursion_maxDepth(TreeNode *root)
{
	if (root == NULL)
		return 0;
	//找左子树的高度
	int left = recursion_maxDepth(root->left);
	//找右子树的高度
	int right = recursion_maxDepth(root->right);

	//返回左子树和右子树中较大的高度，加上自己本身的高度
	return left > right ? left + 1 : right + 1;
}

//递归最小深度
int recursion_minDepth(TreeNode *root)
{
	if (root == NULL)
		return 0;
	int left = recursion_minDepth(root->left);
	int right = recursion_minDepth(root->right);
	//要特殊处理一下，如果左子树不为空，右子树为空
	//比如 left等于1，right等于0，直接比较两个值的大小，然后把较小的加1 返回，会出错
	if (root->left == NULL || root->right == NULL)
		//left 和 right 必有一个等于0，至于是哪个就不管了，这样写简便些
		return left + right + 1;

	//左子树和右子树都存在
	return left < right ? left + 1 : right + 1;
}

//BFS最大深度
int BFS_maxDepth(TreeNode *root)
{
	if (root == NULL)
		return 0;
	queue<TreeNode *> queueNode;
	queueNode.push(root);

	int depth = 0;
	while (!queueNode.empty())
	{
		//这一层中只要有节点，层数就加1
		depth++;
		int size = queueNode.size();
		//遍历这一层的所有节点
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

//BFS最小深度
int BFS_minDepth(TreeNode *root)
{
	if (root == NULL)
		return 0;
	queue<TreeNode *> queueNode;
	queueNode.push(root);

	int depth = 0;
	while (!queueNode.empty())
	{
		//这一层中只要有节点，层数就加1
		//注意，BFS最小深度的时候， depth++要先执行，因为在for循环的过程中可能会return，如果不先执行++，深度会少1
		depth++;
		int size = queueNode.size();
		//遍历这一层的所有节点
		for (int i = 0; i < size; i++)
		{
			TreeNode *curr = queueNode.front();
			queueNode.pop();

			//遇到第一个叶子节点，将深度返回
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

	cout << "最大深度:  " << recursion_maxDepth(root) << endl;

	return 0;
}