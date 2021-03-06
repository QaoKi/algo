#ifndef BSTREE_H
#define BSTREE_H
#include <string>
#include "../Tree/Tree.h"

/*
    二叉搜索树中，一般没有重复值
    二叉搜索树，支持动态数据集合的快速插入、删除、查找操作
    中序遍历二叉查找树，可以输出有序的数据序列，时间复杂度是 O(n)，非常高效
*/

/*
    支持重复数据的二叉查找树:
        方法1：二叉查找树中每一个节点不仅会存储一个数据，因此我们通过链表和支持动态扩容的数组等数据结构，
                把值相同的数据都存储在同一个节点上。
        方法2：每个节点仍然只存储一个数据。在插入的过程中，
                如果碰到一个节点的值，与要插入数据的值相同，我们就将这个要插入的数据放到这个节点的右子树，
                也就是说，把这个新插入的数据当作大于这个节点的值来处理。

                查找数据的时候，遇到值相同的节点，我们并不停止查找操作，而是继续在右子树中查找，
                直到遇到叶子节点，才停止。这样就可以把键值等于要查找值的所有节点都找出来。

                删除操作，我们也需要先查找到每个要删除的节点，然后再按前面讲的删除操作的方法，依次删除。
*/

/*
    二叉搜索树查找，插入，删除的时间复杂度：
    最坏情况下，二叉搜索树退化成链表，时间复杂度为 O(n)
    最好情况下，二叉搜索树是一个完全二叉树，时间复杂度也就是树的高度，为O(logn)
*/

/*
    有了散列表，为什么还要有二叉搜索树？ 极客 P24
*/
class BSTree
{
public:
    BSTree();
    ~BSTree();

    TreeNode *Find(int num);
    void Insert(int num);
    bool Del(int num);

    //后续遍历的方式释放所有节点
    void DestroyTree(TreeNode *node);

private:
    TreeNode *_root; //指向树的 root 节点
    int _count;      //节点的个数
};

#endif