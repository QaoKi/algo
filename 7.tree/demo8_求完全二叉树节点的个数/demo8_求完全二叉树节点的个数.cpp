#include <iostream>
#include <string>
#include "../Tree/Tree.h"
#include <math.h>

using namespace std;

/*
	已知一棵完全二叉树，求其节点的个数
		要求：时间复杂度低于O(N)，N为这棵树的节点个数
*/

/*
	如果一棵满二叉树，高度为h，那么节点个数为2^h - 1
	利用这个特性：
		一个完全二叉树，curr指向root,先求出树的高度,h
		遍历curr的右子树的高度 r,
		如果r = h - 1，那么说明根节点的右子树的最左边界的节点，到了最后一层
				也就是说明，根节点的左子树是满二叉树
				如图：					  1
									2			3
								4		5	6	
					h 为3，根节点右子树的高度 r 为2，右子树的最左边界6号节点，到了最后一层，
					则根节点的左子树是满二叉树
				左子树是满二叉树，左子树的高度为 h - 1，则左子树的节点数为2^(h-1) -1 ,所以，
				左子树加上根节点，一共2^(h-1) 个节点，再让curr指向根节点的右子树，以右子树为
				根节点，判断curr的右子树的高度是否达到最后一层，来判断curr的左子树是否是满二叉树
		如果r != h - 1，左子树可能不是满二叉树，但是右子树肯定是满二叉树，同理，求出右子树加根节点的节点数
		再让curr指向根节点的左子树，递归求

*/

int recursion(TreeNode *root, int h)
{
	//递归终止条件
	if (root == NULL || h <= 0)
		return 0;

	int nodeNum = 0;
	//先求出右子树的高度
	int rh = 0;
	TreeNode *curr = root->right;
	while (curr != NULL)
	{
		rh++;
		curr = curr->left;
	}

	/*
		当左子树不是满的，先求右子树加上根节点的节点数
		当根节点的右子树为空，右子树节点数为0，加上根节点，总共为1，
		而2^0 正好为1，所以不需要特殊处理
		下面是特殊处理

	if (rH == nH - 1)
	{
		nodeNum += pow(2,rH);
		//再以根节点的右子树为根节点，递归求
		nodeNum += digui(root->right, nH - 1);
	}
	else if(rH != 0)		//因为2^0为1，会产生错误
	{
		//右子树是满的

		nodeNum += pow(2, rH);
		//再以根节点的左子树为根节点，递归求
		nodeNum += digui(root->left, nH - 1);
	}
	else
	{
		nodeNum = 1;

		//再以根节点的左子树为根节点，递归求
		nodeNum += digui(root->left, nH - 1);
	}
	*/

	//左子树满的
	if (rh == h - 1)
	{
		nodeNum += pow(2, rh) - 1 + 1; //加上根节点
		//再以根节点的右子树为根节点，递归求
		nodeNum += recursion(root->right, h - 1);
	}
	else
	{
		//右子树是满的
		nodeNum += pow(2, rh) - 1 + 1; //加上根节点
		//再以根节点的左子树为根节点，递归求
		nodeNum += recursion(root->left, h - 1);
	}

	return nodeNum;
}

int GetNodeNum(TreeNode *root)
{
	if (root == NULL)
		return 0;
	//求树的高度
	TreeNode *curr = root;
	int h = 0;
	while (curr != NULL)
	{
		h++;
		curr = curr->left;
	}

	return recursion(root, h);
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

	cout << "节点数量：" << GetNodeNum(root) << endl;

	return 0;
}