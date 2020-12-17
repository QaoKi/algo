#ifndef ORIENTED_GRAPH_CYCLE_H
#define ORIENTED_GRAPH_CYCLE_H

#include <iostream>
#include <map>
#include "../OrientedGraph/OrientedGraph.h"

using namespace std;

/*
    1.DFS
    (算法第四版 P369)
    一个有向图中环的数量可能是图的大小的指数级别，因此只需要找到一个环即可，而不是所有的环。

    因为由系统维护的递归调用的栈表示的正是 “当前” 正在遍历的有向路径，一旦我们找到了一条边 v ——> w 且w已经存在于栈中
    就找到了一个环。
        使用一个栈，dfs遍历图，刚开始遍历到节点v的时候，将v放入栈，接着dfs遍历v所指向的节点，并一条道走到底，
        将这条道上的所有节点都入栈，如果这条道有环，那么最终会再次指向栈中已有的数据
        当节点v所指向的节点都遍历完了，让v出栈
    2.拓扑排序
        见 demo5_拓扑排序的 bfs方法
*/

/*
    时间复杂度：
        方法1，遍历一遍所有的节点和所有的边，所以复杂度为 O(E + V)
        方法2，O(E + V)
        
    额外空间复杂度： O(V)
*/

class OrientedGraphCycle : public OrientedGraph
{
public:
    OrientedGraphCycle();
    ~OrientedGraphCycle(){};

    bool hasCycle();
    void checkCycle(Node *node, set<Node *> &setNode, map<Node *, bool> &mapNodeOnStack);

protected:
    //<a, b>，a和b直接相连，b是a的上一层节点
    unordered_map<Node *, Node *> _mapNodePaths;

    bool _bHasCycle;
};

#endif