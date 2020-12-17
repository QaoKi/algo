#include <iostream>
#include <string>
#include "../../Tree/Tree.h"
#include <vector>
#include <sstream>
#include <queue>
#include <stack>

using namespace std;

/*
	二叉树的序列化，就是先序中序后序的其中一个，表示树的结构，把树用字符串表示，同时也能
	把这个字符串重新转化为树
*/

/*
			如有一个二叉树		 1
							2  		3
					     4	  5	  6	  7
			先序遍历为 1 2 4 5 3 6 7
			用！表示一个节点的结束，用#表示null
			4的左子树和右子树为null,所以为4!#!#!
			总的为：1!2!4!#!#!5!#!#!3!6!#!#!7!#!#!
			中序：
				#!4!#!2!#!5!#!1!#!6!#!3!#!7!#!
			后序:
				#!#!4!#!#!5!2!#!#!6!#!#!7!3!1!
*/

/*
	中序遍历不能用来序列化和反序列化：
		因为中序遍历得到的二叉树不唯一,不能保证反序列化的二叉树为原来的树.
		比如树，
				 	1
				2  		3
			#	  #	  #	  #
		和树
						3
					1		#
				2	  #   
			#	   #
		中序遍历都为  #!2!#!1!#!3!#!
		序列化的二叉树不唯一。并且，因为第一个字符和最后一个字符都是 #，所以采用中序反序列化的时候，找不到第一个有效节点
		
	序列化时，先序，后序都可以完成，
	但是如果采用递归的方式反序列化，先序没有问题，中序和后序，因为第一个字符都是 #，直接就返回了
	后序可以采用从后往前遍历字符串的方式递归反序列化，但是中序不能采用递归的方式反序列化，因为找不到第一个有效节点
*/

void split(const string &s, stack<string> &sq, const char flag)
{
	istringstream iss(s);
	string temp;

	while (getline(iss, temp, flag))
		sq.push(temp);
}

string serialize(TreeNode *root)
{
	//和后序遍历类似
	if (root == NULL)
		return "#!";

	//序列左子树
	string str;
	str += serialize(root->left);
	//序列右子树
	str += serialize(root->right);

	//序列化当前节点
	str += to_string(root->data) + "!";
	return str;
}

//注意，stack要采用引用的方式传参
TreeNode *recursion(stack<string> &stackString)
{
	if (stackString.empty())
		return NULL;

	string str = stackString.top();
	stackString.pop();

	if (str.compare("#") == 0)
		return NULL;

	//新建一个节点
	TreeNode *node = new TreeNode;
	//后序遍历，放入栈中的顺序是 左右中的顺序，取出来是 中右左的顺序
	//所以先还原当前节点
	node->data = stoi(str);
	//再还原当前节点的右子树
	node->right = recursion(stackString);
	//最后还原当前节点的左子树
	node->left = recursion(stackString);

	return node;
}

TreeNode *deserialize(string str)
{
	//后序递归反序列化时，每次要从字符串的尾部取数，所以采用栈
	stack<string> stackString;
	split(str, stackString, '!');

	return recursion(stackString);
}

void PrintTree(TreeNode *node)
{
	if (node == NULL)
		return;

	PrintTree(node->left);
	PrintTree(node->right);
	cout << node->data << "  ";
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

	PrintTree(root);
	cout << endl;
	//后序，递归
	string str = serialize(root);
	cout << "后序序列化：" << str << endl;
	//将字符串再变为树
	TreeNode *newTree = deserialize(str);
	PrintTree(newTree);
	cout << endl;

	return 0;
}