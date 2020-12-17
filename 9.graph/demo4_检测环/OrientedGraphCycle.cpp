#include "OrientedGraphCycle.h"
#include <queue>
#include <stack>

OrientedGraphCycle::OrientedGraphCycle()
{
    _bHasCycle = false;
}
bool OrientedGraphCycle::hasCycle()
{
    _bHasCycle = false;
    set<Node *> setNode;
    //节点是否在栈中
    map<Node *, bool> mapNodeOnStack;

    //遍历一遍所有的节点
    for (auto it = _mapAllNode.begin(); it != _mapAllNode.end(); it++)
    {
        if (setNode.find(it->second) == setNode.end())
            checkCycle(it->second, setNode, mapNodeOnStack);
    }
    return _bHasCycle;
}

void OrientedGraphCycle::checkCycle(Node *node, set<Node *> &setNode, map<Node *, bool> &mapNodeOnStack)
{
    setNode.insert(node);
    //将节点node入栈
    mapNodeOnStack[node] = true;
    //遍历该节点指向的所有节点
    for (auto it = _mapOrientedGraph[node].begin(); it != _mapOrientedGraph[node].end(); ++it)
    {
        if (_bHasCycle)
            return;

        //如果这条边指向的节点 curr，之前已经访问过，并且 curr 在栈中，那么说明有环
        Node *curr = *it;
        if (setNode.find(curr) == setNode.end())
        {
            _mapNodePaths[curr] = node;
            checkCycle(curr, setNode, mapNodeOnStack);
        }
        else if (mapNodeOnStack[curr])
        {
            //有环
            _bHasCycle = true;
            //从后往前输出环
            //这一条路，是 curr -> .....->node -> curr
            //所以，从node节点开始朝后找，一直找到curr
            Node *temp = node;
            while (temp != curr)
            {
                cout << temp->_data << "  ";
                temp = _mapNodePaths[temp];
            }

            cout << curr->_data << "  " << endl;
        }
    }

    //这一条道遍历完了，让node出栈
    mapNodeOnStack[node] = false;
}