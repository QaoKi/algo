#ifndef TREE_H
#define TREE_H
#include <string>

struct TreeNode
{
    TreeNode *left;   //左子树
    TreeNode *right;  //右子树
    TreeNode *parent; //父节点
    int data;
    TreeNode()
    {
        left = NULL;
        right = NULL;
        parent = NULL;
        data = 0;
    }
    TreeNode(int num)
    {
        left = NULL;
        right = NULL;
        parent = NULL;
        data = num;
    }
};

#endif