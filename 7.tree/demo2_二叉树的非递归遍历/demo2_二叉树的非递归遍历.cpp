#include <iostream>
#include <string>
#include "../Tree/Tree.h"
#include <stack>

using namespace std;

/*
	非递归遍历：递归遍历的本质是系统给我们将数据放到栈中，现在自己用一个栈把数据存起来

		先序遍历是先遍历节点，再遍历左子树，最后遍历右子树，那么压栈的时候，先把右子树压栈，
		再把左子树压栈
*/

void preOrder(TreeNode *root)
{
	if (root == NULL)
		return;
	stack<TreeNode *> stackNode;
	stackNode.push(root);

	TreeNode *curr = root;
	while (!stackNode.empty())
	{
		curr = stackNode.top();
		stackNode.pop();
		cout << curr->data << "  ";
		//右节点先入栈，先入后出
		if (curr->right != NULL)
			stackNode.push(curr->right);
		//左节点再入栈，出栈的时候左节点先出栈
		if (curr->left != NULL)
			stackNode.push(curr->left);
	}
}

void inOrder(TreeNode *root)
{
	if (root == NULL)
		return;
	stack<TreeNode *> stackNode;

	TreeNode *curr = root;
	/*
		思路：
			当前节点不为空，当前节点压入栈，当前节点往左移动
			当前节点为空，从栈中拿一个，打印，当前节点向右移动
	*/
	while (curr != NULL || !stackNode.empty())
	{
		//当前节点不为空，当前节点压入栈，当前节点往左移动
		//因为要把当前树的左边界先都压到栈中
		if (curr != NULL)
		{
			stackNode.push(curr);
			curr = curr->left; //如果节点还有左子树，继续把左子树压栈，一直找到树的最左的节点
		}
		else
		{
			//当前节点为空，从栈中拿一个，打印，当前节点向右移动
			curr = stackNode.top();
			stackNode.pop();
			cout << curr->data << "  ";
			curr = curr->right;
		}
	}
}

//后序非递归实现
void postOrder(TreeNode *root)
{
	if (root == NULL)
		return;

	/*
		先序遍历，是中左右，是先将当前节点打印，再把右子树压栈，再把左子树压栈，这样左子树就比右子树先出栈

		后序遍历是实现，左右中的顺序，如果倒过来看，就是中右左的顺序，所以可以让节点，按中右左的顺序
			进入另一个栈 stackHelp，stackHelp再出栈就是左右中的顺序，
			要实现中左右的的顺序，当前节点先入栈stackHelp，然后左子树入stackHelp,最后右子树入stackHelp
	*/
	stack<TreeNode *> stackNode;
	stack<TreeNode *> stackHelp;

	TreeNode *curr = root;
	stackNode.push(curr);

	while (!stackNode.empty())
	{
		curr = stackNode.top();
		stackNode.pop();

		//当前节点先入stackHelp,把先序遍历中的打印变成入栈
		stackHelp.push(curr);

		//让左子树入栈
		if (curr->left != NULL)
			stackNode.push(curr->left);

		//让右子树入栈
		if (curr->right != NULL)
			stackNode.push(curr->right);
	}

	//此时 stackHelp 中，就是中右左的顺序，再依次出栈打印，就是左右中的顺序

	while (!stackHelp.empty())
	{
		curr = stackHelp.top();
		stackHelp.pop();
		cout << curr->data << "  ";
	}
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