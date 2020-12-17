#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>
#include "../Tree/Tree.h"
using namespace std;

/*
	两种方法：
		BFS(广度优先搜索)：
			采用队列的方式，对每一个节点，遍历它所有的子树，把子树插到队列的尾部，因为二叉树
			不会出现重复节点，所以不用使用set进行防止重复，但是要记录什么时候一层结束
			如何知道这一层已经遍历完了：比如第二层有2个节点，第三层有4个，开始遍历第二层的时候，
			队列中size为2，此时只循环2次，把第二层的节点都遍历完，第二层节点遍历完以后，队列中
			size会为4，此时再循环4次，把第三层遍历完

		DFS(深度优先搜索)：	
			要记住每个节点是第几层，比如1有2和3的子树，2有4和5的子树，3有6和7的子树
			每次遍历一个节点的时候，要记住这个节点是第几层，1是第一层，把1归到第一层
			1的左子树是2，1是第一层，那么它的子树是2，归到第二层，同理，2的左子树4归到第三层
			再回溯到2，2的右子树5归到第三层。。。
*/

//广度优先搜索
void BFS(TreeNode *root)
{
    if (root == NULL)
        return;
    //二叉树不需要用一个set来判断是不是重复的节点
    queue<TreeNode *> queueNode;
    queueNode.push(root);
    while (!queueNode.empty())
    {
        /*
            注意，要用一个变量来存储队列的长度
            如果直接  for (int i = 0; i < queueNode.size(); i++)
            当queueNode.push() 以后，queueNode.push(curr->left) 会变
        */
        int size = queueNode.size();
        for (int i = 0; i < size; i++)
        {
            TreeNode *curr = queueNode.front();
            queueNode.pop();
            cout << curr->data << "  ";

            //把当前节点的子节点都加入到队列中
            if (curr->left != NULL)
                queueNode.push(curr->left);
            if (curr->right != NULL)
                queueNode.push(curr->right);
        }
        cout << endl;
    }
}

void digui(TreeNode *root, int level, map<int, vector<TreeNode *>> &mapLevelNums)
{
    if (root == NULL)
        return;
    mapLevelNums[level].push_back(root);
    if (root->left != NULL)
        digui(root->left, level + 1, mapLevelNums);
    if (root->right != NULL)
        digui(root->right, level + 1, mapLevelNums);
}

//深度优先搜索
void DFS(TreeNode *root)
{
    if (root == NULL)
        return;
    //把当前节点，和当前是第几层，传给子过程,用一个二维数组保存结果
    map<int, vector<TreeNode *>> mapLevelNums;
    digui(root, 0, mapLevelNums);

    for (int i = 0; i < mapLevelNums.size(); i++)
    {
        for (int j = 0; j < mapLevelNums[i].size(); j++)
        {
            cout << mapLevelNums[i][j]->data << "  ";
        }
        cout << endl;
    }
    cout << endl;
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

    BFS(root);
    cout << "========" << endl;
    DFS(root);

    return 0;
}