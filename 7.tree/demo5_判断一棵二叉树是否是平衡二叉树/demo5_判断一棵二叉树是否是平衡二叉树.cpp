#include <iostream>
#include <string>
#include "../Tree/Tree.h"

using namespace std;

/*
	平衡二叉树：
		在树中的任何一个节点，它的左子树和右子树的高度差不超过1
		如有一个二叉树			1
							2  		3
						 	  4	  5
		节点1的左子树高度为2，右子树高度为2，平衡
		节点2和3的左子树右子树高度差都为1，平衡
		如有一个二叉树			1
							2  		3
							  4   5
							6       7
		节点2的左子树高度为0，右子树高度为2，不平衡
		节点3的左子树高度为2，右子树高度为0，不平衡.

*/

/*
	思路：
		用递归分治思想，整棵树要平衡，那么每个节点的左右子树都要平衡，
		左右子树平衡了以后，需要根据左子树的高和右子树的高来判断左子树右子树合在一起的树平不平衡
		所以需要返回左子树是否平衡，左子树的高，右子树是否平衡，右子树的高，用一个结构体来存储
		也可以不用结构体，返回-1，表示子树不平衡，返回0，表示空树，是平衡的，返回>0，表示树的高度，是平衡的

		列出可能性，整理出返回值的类型，整个递归过程按照同样的结构，得到子树的信息，整合子树的信息，
		加工出我需要的信息，往上返回，因为是递归，所以结构要求一样
*/

/*
	举例分析过程：n表示null
				   1
			2		       3
		n		4      n	     5
			 n     n   

		当前节点curr指向1，先去找左子树，curr指向2，再找2的左子树，curr指向2的
		左子树 null，curr为null，返回true和0，表示是平衡的，高度为0，2号节点会知道它的左子树
		是平衡的，高度为0，再去判断右子树，curr指向4号，再分别指向4的左子树null和右子树Null，
		则4号会得到两个true和0，4号知道它的左右子树都是平衡的，再判断两个子树合并以后还平不平衡
		两个子树高度都为0，是平衡的，此时返回左右子树最大的高度加1，也就是1
		curr指回2号，2号会得到左子树的true和0，得到右子树的true和1，2号再去判断左右子树合并以后还
		平不平衡，检查为平衡，给1号返回true和左右子树最大高度加1，为2，所以2号给1号返回true和2
		同理，1号的右子树也返回数据以后，再进行判断左右子树合并以后是否平衡
*/

//返回 -1，表示不平衡，返回 >= 0 ，表示树的深度，平衡
int depth(TreeNode *node)
{
	if (node == NULL) //如果是空树，也是平衡的
		return 0;

	//先判断左子树是否平衡
	int leftHigh = depth(node->left);
	//node 的左子树不平衡，那么以 node 为根节点的树也不平衡
	if (leftHigh == -1)
		return -1;
	//再去判断右子树是否平衡
	int rightHigh = depth(node->right);
	//同理，node 的右子树不平衡，那么以 node 为根节点的树也不平衡
	if (rightHigh == -1)
		return -1;

	//此时，左子树和右子树已经平衡，判断左子树和右子树合并后的数是否平衡
	if (leftHigh - rightHigh > 1 || rightHigh - leftHigh > 1)
		return -1;

	//返回左子树和右子树中高度更大的那个高度加1
	return leftHigh > rightHigh ? leftHigh + 1 : rightHigh + 1;
}

bool isBalanced(TreeNode *root)
{
	return depth(root) != -1;
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

	if (isBalanced(root))
		cout << "是平衡的" << endl;
	else
		cout << "不是平衡的" << endl;

	return 0;
}