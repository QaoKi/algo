#include <iostream>
#include <string>
#include "../Tree/Tree.h"

using namespace std;

/*
	题目：
		现在有一种新的二叉树节点类型，该结构比普通二叉树节点结构多了一个指向父节点的parent指针。
		假设有一棵Node类型的节点组成的二叉树，树中每个节点的parent指针都正确地指向自己的父节点，
		头节点的parent指向null。只给一个在二叉树中的某个节点 node，请实现返回node的后继节点的函数。

		前驱节点和后继节点，只在中序遍历中，前驱节点和父节点是不一样的
		在二叉树的中序遍历的序列中， node的下一个节点叫作node的后继节点。
		如有一个二叉树		1 
					  2  	      3
				   4	 5	   6     7

		中序遍历为：4 2 5 1 6 3 7
		4的后继节点为2，2的后继节点为5
		2的前驱节点为4，5的前驱节点为2

		扩展，给定一个节点K，找这个节点的前驱节点，前驱节点和父节点是不一样的

*/

/*
	思路：
		给定树中的某一节点K，找到该节点的后继节点，
		1，根据K节点，找到根节点，再对整个数中序遍历，再找到K节点的后继节点
			这样因为要遍历整个树，所以复杂度高
		2，K节点如果有右节点，设右节点为 A，那么它的后继节点是：
				以 A 为根节点的子树中最左边界的节点，因为中序遍历的顺序为左中右，
				所以当一个节点有右节点时，把它的右子树看成一个新的树，这个新的树首先要遍历最左的节点
				如果 A 没有左节点，那么K节点的后继节点就是 A
		   K节点没有右节点，根据parent指针找它的父节点X，
			  如果K是X的左节点，那么K的后继节点就是X，因为中序遍历为左中右，
					K节点是左节点，左孩子遍历完以后要遍历中，也就是它的父节点X
			  如果K是X的右节点，根据X的parent指针，去找X的父节点Y，看看X是不是Y的左节点，如果是，
					那么K的后继节点就是Y，如果不是，接着向上找Y的父节点Z，看看Y是不是Z的左节点，如果是，
					那么K的后继节点就是Z，不是就向上找，找不到就没有后继节点

					因为K是X的右节点，遍历完K以后，X作为中，已经被遍历了，就不需要再遍历，此时向上找，
					如果X是它父节点Y的左节点，左遍历完，要遍历中，那么Y就是K的后继节点，
					如果X还是Y的右节点，说明Y作为中以已经遍历过了，再往上找


		扩展，给定一个节点K，找这个节点的前驱节点，前驱节点和父节点是不一样的
			K如果有左节点，前驱节点就为左节点
			K如果没有左节点，找它的父节点，如果它是父节点的右节点，那么前驱节点为父节点，
				如果不是父节点的右节点，找父节点的父节点，看父节点是不是父节点的父节点的右节点。。。

*/

TreeNode *GetNext(TreeNode *node)
{
	if (node == NULL)
		return NULL;

	TreeNode *retNode = NULL;
	//如果该节点有右子树，找右子树中最左的节点，就是后继节点
	if (node->right != NULL)
	{
		//如果右子树没有左子树，那么右子树就是后继节点
		retNode = node->right;
		//如果右子树有左子树，一直向左找
		while (retNode->left != NULL)
		{
			retNode = retNode->left;
		}
	}
	else
	{
		//没有右子树，找该节点的父节点，看看该节点是不是父节点的左孩子
		TreeNode *curr = node;
		TreeNode *pre = node->parent;
		while (pre != NULL)
		{
			//如果是父节点的左孩子，那么父节点就是后继节点
			if (pre->left == curr)
			{
				retNode = pre;
				break;
			}
			else
			{
				//否则继续向上找，看看父节点是不是爷爷节点的左孩子
				curr = pre;
				pre = pre->parent;
			}
		}
	}

	return retNode;
}

//找前驱节点
TreeNode *GetPrecursor(TreeNode *node)
{
	if (node == NULL)
		return;
	TreeNode *retNode = NULL;
	//如果有左子树，前驱节点就是左子树
	if (retNode->left != NULL)
		retNode = retNode->left;
	else
	{
		//没有左子树，找父节点，如果是父节点的右子树，那么前驱节点就是父节点
		//如果不是父节点的右子树，继续向上找
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

	//给一个节点，找这个节点的后继节点
	TreeNode *curr = root->right->left;
	TreeNode *next = GetNext(curr);
	if (next != NULL)
		cout << "后续节点： " << next->data << endl;
	else
		cout << "没有后续节点" << endl;

	TreeNode *pre = GetPrecursor(curr);
	if (pre != NULL)
		cout << "前驱节点： " << pre->data << endl;
	else
		cout << "没有前驱节点" << endl;

	return 0;
}