#ifndef UNDIRECTED_GRAPH_CYCLE_H
#define UNDIRECTED_GRAPH_CYCLE_H

#include <iostream>
#include <map>
#include "../UndirectedGraph/UndirectedGraph.h"

using namespace std;

/*
    参考：https://www.cnblogs.com/tenosdoit/p/3644225.html
    只检测有没有环：
        1，深度优先遍历该图，如果在遍历的过程中，发现某个节点有一条边指向已经访问过的节点，
            并且这个已访问过的节点不是当前节点的父节点（这里的父节点表示dfs遍历顺序中的父节点），则表示存在环

    如果要输出所有的环：
        采用方法1就不可以了，比如图为 0 —— 1 —— 2
                                         \   /
                                           3
        从节点0开始遍历，遍历1-接着遍历2-接着遍历3，然后发现3有一条边指向遍历过的1，并且1不是3的父节点，则存在环。
        但是当回溯到1节点，它的另一条边指向已访问过的3，并且3不是1的父节点，又把这个环重复计算了一次
        
        解决：
            对每个节点分为三种状态，白、灰、黑。开始时所有节点都是白色，当开始访问某个节点时该节点变为灰色，
            当该节点的所有邻接点都访问完，该节点颜色变为黑色。
            算法则为：如果遍历的过程中发现某个节点有一条边指向颜色为灰的节点，那么存在环
            则在上面的例子中，回溯到1节点时，虽然有一条边指向已经访问过的3，但是3已经是黑色，所以环不会被重复计算
            用值0 1 2三种状态分别代表白色、灰色、黑色
*/

/*
    时间复杂度：
        方法1，只检测有没有环，dfs一遍图，但是要检测所有节点是否已经被遍历过（加入到set中），
                所以所有节点要遍历一遍，所以复杂度为 O(E + V)
        方法2，输出环，首先要遍历一遍所有的节点，让节点的状态等于0，再进行dfs，时间复杂度为O(E + V)

    额外空间复杂度： O(V)
*/

class UndirectedGraphCycle : public UndirectedGraph
{
public:
    UndirectedGraphCycle();
    ~UndirectedGraphCycle(){};

    bool hasCycle();
    void checkCycle(Node *node, set<Node *> &setNode);

    void printAllCycles();
    void printCycleHelp(Node *node, map<Node *, int> &mapNodeStatus);

protected:
    //<a, b>，a和b直接相连，b是a的上一层节点
    unordered_map<Node *, Node *> _mapNodePaths;

    bool _bHasCycle;
    int _iCycleCount;
};

#endif