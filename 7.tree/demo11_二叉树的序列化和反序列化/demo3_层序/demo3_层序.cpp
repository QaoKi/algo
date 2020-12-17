#include <iostream>
#include <string>
#include "../../Tree/Tree.h"
#include <vector>
#include <sstream>
#include <queue>

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
			层序：
				1!2!3!4!5!6!7!
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
		序列化不唯一。并且，因为第一个字符和最后一个字符都是 #，所以采用中序反序列化的时候，找不到第一个有效节点
		
	序列化时，先序，后序都可以完成，
	但是如果采用递归的方式反序列化，先序没有问题，中序和后序，因为第一个字符都是 #，直接就返回了
	后序可以采用从后往前遍历字符的方式递归反序列化，但是中序不能采用递归的方式反序列化，因为找不到第一个有效节点
*/

void split(const string &s, vector<string> &sq, const char flag)
{
	istringstream iss(s);
	string temp;

	while (getline(iss, temp, flag))
		sq.push_back(temp);
}

string serialize(TreeNode *root)
{
	//和层序遍历类似
	if (root == NULL)
		return "#!";
	queue<TreeNode *> queueNode;
	queueNode.push(root);

	string str;
	while (!queueNode.empty())
	{
		TreeNode *curr = queueNode.front();
		queueNode.pop();

		if (curr == NULL)
			str += "#!";
		else
		{
			str += to_string(curr->data) + "!";
			//不管子树是不是 null，都加进去，因为如果是null的话，也要输出 #!
			//当然，要判断一下 curr 是不是 null
			queueNode.push(curr->left);
			queueNode.push(curr->right);
		}
	}

	return str;
}

/*
	反序列化时，只有根节点的那层是一个节点，其他的几层，节点个数都是成对的，分别对应左右子节点
	在split字符串的时候，把结果放到一个 vector中（方便通过下标访问），下标0的值用来构建根节点，
	下标1,2用来构建根节点的左右子树。。。
*/

TreeNode *deserialize(string str)
{
	//层序反序列化时，需要能通过下标访问，所以采用vector
	vector<string> vectorString;
	split(str, vectorString, '!');

	//如果第一个节点，也就是根节点是空
	if (vectorString[0] == "#")
		return NULL;
	//用第一个字符构建根节点
	TreeNode *newTree = new TreeNode(stoi(vectorString[0]));
	//声明一个队列，存放非 null 节点，队列的功能，和序列化时的队列类似
	queue<TreeNode *> queueNode;
	queueNode.push(newTree);

	//从下标1开始处理其他节点
	int index = 1;
	while (!queueNode.empty())
	{
		//每次从队列中取一个节点，处理这个节点的左右子树，左右子树默认都是null
		TreeNode *curr = queueNode.front();
		queueNode.pop();
		//处理左子树
		if (vectorString[index] != "#")
		{
			curr->left = new TreeNode(stoi(vectorString[index]));
			//将当前节点的左节点加入到队列中，下次循环时取出，处理其左右子树
			queueNode.push(curr->left);
		}

		//处理右子树
		index++;
		if (vectorString[index] != "#")
		{
			curr->right = new TreeNode(stoi(vectorString[index]));
			//将当前节点的右节点加入到队列中
			queueNode.push(curr->right);
		}

		index++;
	}
	return newTree;
}

void PrintTree(TreeNode *node)
{
	if (node == NULL)
		return;
	queue<TreeNode *> queueNode;
	queueNode.push(node);

	string str;
	while (!queueNode.empty())
	{
		int size = queueNode.size();
		for (int i = 0; i < size; i++)
		{
			TreeNode *curr = queueNode.front();
			queueNode.pop();

			cout << curr->data << "  ";
			if (curr->left != NULL)
				queueNode.push(curr->left);
			if (curr->right != NULL)
				queueNode.push(curr->right);
		}
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

	PrintTree(root);
	cout << endl;
	//先序，递归
	string str = serialize(root);
	cout << "先序序列化：" << str << endl;
	//将字符串再变为树
	TreeNode *newTree = deserialize(str);
	PrintTree(newTree);
	cout << endl;

	return 0;
}