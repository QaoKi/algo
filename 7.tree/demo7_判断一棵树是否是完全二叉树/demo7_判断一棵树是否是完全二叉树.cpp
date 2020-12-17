#include <iostream>
#include <string>
#include "../Tree/Tree.h"
#include <queue>

using namespace std;

/*
	完全二叉树：
		堆就是一个完全二叉树，可以用数组表示	
*/

/*
	思路：
	两种情况：
		1.一个节点，有右孩子，但是没有左孩子，肯定不是完全二叉树 
		2，当一个节点，有左孩子没有右孩子，或者左右孩子都没有时，这个节点后面所有的节点，
			都必须是叶节点（没有左右孩子）
	比如：
								  1
							2			3
						4		5	6		7
					 8	   9 10

		当节点遍历到5号，符合第2种情况，那么5之后的节点，都必须没有左右孩子
		要设置一个开关，开关开启之后，之后的节点都必须没有左右孩子

	需要进行按层遍历（宽度遍历），对每个节点进行分析
		用一个队列实现按层遍历
*/
bool check(TreeNode *root)
{
	TreeNode *curr = root;
	queue<TreeNode *> queueNode;
	queueNode.push(curr);

	//当第一次遇到有左孩子但没有右孩子，或者第一次遇到左右孩子都没有的时候，这之后的节点都必须没有左右孩子
	bool bLock = false;

	//一个节点一个节点的去判断
	while (!queueNode.empty())
	{
		curr = queueNode.front();
		queueNode.pop();

		//第一种情况，直接返回false
		if (curr->left == NULL && curr->right != NULL)
			return false;

		//第一次遇到有左孩子但没有右孩子，或者第一次遇到左右孩子都没有的时候
		//注意，这两个 if 不能合并到一起
		if (!bLock)
		{
			//此时只要判断没有右孩子即可
			if (curr->right == NULL)
				bLock = true;
		}
		else
		{
			//如果开关开启了，节点还有左孩子或者右孩子，返回false
			if (curr->left != NULL || curr->right != NULL)
				return false;
		}

		if (curr->left != NULL)
			queueNode.push(curr->left); //先将左孩子加入队列中

		if (curr->right != NULL)
			queueNode.push(curr->right); //再将右孩子加入队列中
	}

	return true;
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

	//检测是否是完全二叉树
	if (check(root))
		cout << "是完全二叉树" << endl;
	else
		cout << "不是完全二叉树" << endl;

	return 0;
}