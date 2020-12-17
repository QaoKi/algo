#include "BSTree.h"

BSTree::BSTree()
{
    _root = NULL;
    _count = 0;
}

BSTree::~BSTree()
{
    //后续遍历的方式释放所有节点
    DestroyTree(_root);
}

TreeNode *BSTree::Find(int num)
{
    TreeNode *curr = _root;
    while (curr != NULL)
    {
        //比当前节点小，向左移动
        if (curr->data > num)
            curr = curr->left;
        //比当前节点大，向右移动
        else if (curr->data < num)
            curr = curr->right;
        else
            return curr;
    }
    return NULL;
}

void BSTree::Insert(int num)
{
    TreeNode *newNode = new TreeNode;
    newNode->data = num;
    _count++;
    /*
            新插入的数据一般都是在叶子节点上
            如果要插入的数据比节点的数据大，并且节点的右子树为空，就将新数据直接插到右子节点的位置；
            如果不为空，就再递归遍历右子树，查找插入位置。
            同理，如果要插入的数据比节点数值小，并且节点的左子树为空，就将新数据插入到左子节点的位置；
            如果不为空，就再递归遍历左子树，查找插入位置。
        */
    TreeNode *curr = _root;
    while (curr != NULL)
    {
        if (curr->data > num)
        {
            if (curr->left == NULL)
            {
                curr->left = newNode;
                return;
            }
            curr = curr->left;
        }
        else
        {
            if (curr->right == NULL)
            {
                curr->right = newNode;
                return;
            }
            curr = curr->right;
        }
    }
}

/*
    要删除的节点 p 有三种情况，
        1，如果没有子树，直接释放，让p的父节点 pp 指向 null，
        2，如果有一个子树，直接让p的父节点 pp 指向这颗子树
        3，如果有两个子树，去找右子树中最小的节点 x 来替换 p，因为右子树中的节点值都是比p大的，
            所以让右子树中最小的节点来替换p，不会影响其他节点。而右子树中最小节点，就是右子树的最左边的节点

            用x替换掉p以后，还要再走删除x的过程，因为x虽然是右子树中的最小值，x肯定是没有左子树的，但是可能会有右子树，
            所以还要走一遍情况1,2的过程

            或者x替换掉p以后，直接把 x 的右子树挂到x的父节点左子树下面，

*/
bool BSTree::Del(int num)
{
    TreeNode *curr = _root;   //找到要删除的节点
    TreeNode *currPre = NULL; //指向要删除节点的父节点

    while (curr != NULL && curr->data != num)
    {
        currPre = curr;
        if (curr->data > num)
            curr = curr->left;
        else
            curr = curr->right;
    }

    if (curr == NULL)
        return false; //没找到

    //有两个子树
    if (curr->left != NULL && curr->right != NULL)
    {
        //找右子树中的最小节点 x
        TreeNode *minNode = curr->right;
        //最小节点 x 的父节点，等下删除 x 的时候，要用到它的父节点
        TreeNode *minPreNode = curr;
        while (minNode->left != NULL)
        {
            minPreNode = minNode;
            minNode = minNode->left;
        }
        //此时 curr 指向要删除的节点，将这个节点的值用最小节点x的值替换
        curr->data = minNode->data;
        //此时 x 节点是一个没有子树，或者有一个子树的节点，再走下面的删除无子树或者一个子树的过程

        curr = minNode;
        currPre = minPreNode;
        /*
        或者直接把x的右子树，挂到x的父节点的左子树下，不用去管 x的右子树是不是空

        minPreNode->left = minNode->right;
        //释放掉节点
        delete minNode;
        minNode = NULL;
        return true;
        
        */
    }

    // 删除节点是叶子节点或者仅有一个子节点
    TreeNode *child = NULL;
    if (curr->left != NULL)
        child = curr->left;
    else
        child = curr->right;

    //改变父节点的指向
    if (currPre == NULL)
        //要删除的是头节点
        _root = child;
    else if (currPre->left == curr)
        currPre->left = child;
    else
        currPre->right = child;

    delete curr;
    curr = NULL;
    _count--;
    return true;
}

void BSTree::DestroyTree(TreeNode *node)
{
    if (node != NULL)
    {
        if (node->left != NULL)
            DestroyTree(node->left);

        if (node->right != NULL)
            DestroyTree(node->right);

        delete node;
        node = NULL;
    }
}