#include <iostream>
#include <string>
#include "../Tree/Tree.h"

using namespace std;
/*
	二叉数可以用数组来存储
	但是完全二叉树用数组存储比较好，下标 i 的左节点是 2 * i + 1，右节点为 2 * i + 2
	如果不是完全二叉数，数组的空隙比较多，浪费空间
*/

/*
	递归遍历，时间复杂度O(n)
	每个节点会访问三次，访问此节点的时候一次，访问完左子树回来的时候一次，访问完
	右子树回来的时候一次，一共三次
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

	//先序遍历，先遍历根节点，再遍历左子树，最后遍历右子树
	cout << "先序遍历为：  ";
	preOrder(root);
	cout << endl;

	//中序遍历，先遍历左子树，再遍历根节点，最后遍历右子树
	cout << "中序遍历为：  ";
	inOrder(root);
	cout << endl;

	//后序遍历，先遍历左子树，再遍历右子树，最后遍历根节点
	cout << "后序遍历为：  ";
	postOrder(root);
	cout << endl;

	return 0;
}