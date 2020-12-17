#include <iostream>
#include <string>
#include "../Tree/Tree.h"

using namespace std;

/*
	给定一个二叉树或者二叉搜索树，树上两个节点p和q
	找到p和q的最近的公共祖先
*/

/*
	任意的二叉树：
		后序遍历 DFS。
		从根节点root开始遍历，如果p和q中的任一个和root匹配，那么root就是最低公共祖先。 
		如果都不匹配，则分别递归左、右子树。如果有一个节点出现在左子树，
		并且另一个节点出现在右子树，则root就是最低公共祖先.  
		如果两个节点都出现在左子树，则说明最低公共祖先在左子树中，否则在右子树。 

	二叉搜索树：
		二叉搜索树是有序的，
		所以如果q节点的值大于root，并且p节点的值大于root，那么公共祖先在右子树，
		如果q节点的值小于root，p节点的值小于root，那么公共祖先在左子树，
		否则的话，两个节点分别在左子树和右子树，公共祖先就是root
*/

//任意二叉树
TreeNode *AnyTree(TreeNode *root, TreeNode *q, TreeNode *p)
{
	//终止条件，如果p和q中的任一个和root匹配，那么root就是最近公共祖先
	if (root == NULL || root->data == q->data || root->data == p->data)
		return root;
	//查看左子树中是否有目标结点，没有为null
	TreeNode *left = AnyTree(root->left, q, p);
	TreeNode *right = AnyTree(root->right, q, p);

	if (left == NULL)
		//左子树中没有任何一个目标节点，那么公共祖先在右子树中
		return right;
	if (right == NULL)
		//右子树中没有任何一个目标节点，那么公共祖先在左子树中
		return left;

	//都不为空，说明做右子树都有目标结点，则公共祖先就是本身
	return root;
}

//搜索二叉树
TreeNode *BSTree(TreeNode *root, TreeNode *q, TreeNode *p)
{
	//两个节点的值都比 root小，说明公共祖先在 root 的左子树
	if (root->data > q->data && root->data > p->data)
	{
		return BSTree(root->left, q, p);
	}
	else if (root->data < q->data && root->data < p->data)
	{
		return BSTree(root->right, q, p);
	}
	else
	{
		return root;
	}
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

	TreeNode *res = AnyTree(root, root->left->left, root->left->right);
	cout << "公共祖先：" << res->data << endl;

	return 0;
}