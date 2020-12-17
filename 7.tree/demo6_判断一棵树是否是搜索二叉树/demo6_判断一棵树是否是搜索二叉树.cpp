#include <iostream>
#include <string>
#include "../Tree/Tree.h"
#include <stack>
#include <limits.h>

using namespace std;

/*
	搜索二叉树：又叫作二叉树查找树或者二叉排序树
		对于树上任何一个节点，它的左子树的所有结点都比这个根结点要小，
							  它的右子树的所有结点都比这个根结点要大

		注意是根结点与左右子树上所有的结点进行比较而不是仅仅与左右孩子结点进行比较
		当按照中序遍历来遍历一棵搜索二叉树时，必然是单调递增的，
		即是有序的序列，反之，如果一棵二叉树按照中序遍历得到的序列是有序的，
		那么这棵二叉树一定是搜索二叉树，因此对于搜索二叉树通常总是进行中序遍历的操作
*/

/*
	思路：
		通常来说，搜索二叉树不含有重复节点 
		在树上，以每个节点为根节点的子树，根节点都要比所有的左子树上的节点小，比所有的右子树上的节点大
		用中序遍历，因为中遍历的顺序是左中右，在中序遍历的时候，只需要判断
		当前节点的值，比它前一个遍历的节点的值大就可以了。注意，等于也不可以

		先改非递归遍历，递归的比较麻烦

*/

bool not_recursion(TreeNode *root)
{
	if (root == NULL)
		return false;
	TreeNode *curr = root;
	stack<TreeNode *> stackNode;

	//当前节点不为空，当前节点入栈，当前节点向左移动
	//当前节点为空，从栈中取一个数，打印，当前节点向右移动，打印的过程，换成比较。
	long preValue = (long)INT_MIN - 1; //-1; //上一个节点的值
	while (curr != NULL || !stackNode.empty())
	{
		if (curr != NULL)
		{
			stackNode.push(curr);
			curr = curr->left;
		}
		else
		{
			curr = stackNode.top();
			stackNode.pop();
			//和前一个数比较，等于也不可以
			if (curr->data <= preValue)
				return false;
			else
				preValue = curr->data;

			curr = curr->right;
		}
	}
	return true;
}

//中序遍历时，判断当前节点是否大于中序遍历的前一个节点，如果大于，说明满足，继续遍历；否则直接返回 false。
long _preValue = (long)INT_MIN - 1;
bool isValidBST(TreeNode *node)
{
	if (node == NULL)
		return true;
	//判断左子树是否符合
	if (!isValidBST(node->left))
		return false;

	//当前节点是否大于前一个节点
	if (node->data <= _preValue)
		return false;
	_preValue = node->data;

	//判断右子树是否符合
	return isValidBST(node->right);
}

int main()
{
	TreeNode *root = new TreeNode;
	root->data = 4;

	root->left = new TreeNode;
	root->right = new TreeNode;
	root->left->data = 2;
	root->right->data = 6;

	root->left->left = new TreeNode;
	root->left->left->data = 1;
	root->left->right = new TreeNode;
	root->left->right->data = 3;

	root->right->left = new TreeNode;
	root->right->left->data = 5;
	root->right->right = new TreeNode;
	root->right->right->data = 7;

	if (not_recursion(root))
		cout << "是搜索二叉树" << endl;
	else
		cout << "不是搜索二叉树" << endl;

	if (isValidBST(root))
		cout << "是搜索二叉树" << endl;
	else
		cout << "不是搜索二叉树" << endl;

	return 0;
}