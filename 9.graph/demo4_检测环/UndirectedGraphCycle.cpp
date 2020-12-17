#include "UndirectedGraphCycle.h"
#include <queue>
#include <stack>

UndirectedGraphCycle::UndirectedGraphCycle()
{
    _bHasCycle = false;
    _iCycleCount = 0;
}
bool UndirectedGraphCycle::hasCycle()
{
    _bHasCycle = false;
    //将所有的连通量都遍历一遍
    set<Node *> setNode;
    for (auto it = _mapUndirectedGraph.begin(); it != _mapUndirectedGraph.end(); ++it)
    {
        if (setNode.find(it->first) == setNode.end())
            checkCycle(it->first, setNode);
    }

    return _bHasCycle;
}

void UndirectedGraphCycle::checkCycle(Node *node, set<Node *> &setNode)
{
    setNode.insert(node);
    //遍历该节点指向的所有节点
    for (auto it = _mapUndirectedGraph[node].begin(); it != _mapUndirectedGraph[node].end(); ++it)
    {
        if (_bHasCycle)
            return;
        //如果这条边指向的节点 curr，之前已经访问过，并且 curr 不是 node 按照dfs路径过来的父节点，那么就有环
        Node *curr = *it;
        if (setNode.find(curr) != setNode.end() && _mapNodePaths[node] != curr)
            _bHasCycle = true;
        //否则如果没有访问过，继续递归
        else if (setNode.find(curr) == setNode.end())
        {
            _mapNodePaths[curr] = node;
            checkCycle(curr, setNode);
        }
    }
}

void UndirectedGraphCycle::printAllCycles()
{
    if (!hasCycle())
    {
        cout << "not have cycle" << endl;
        return;
    }

    //记录每个节点的状态，0,1,2，也能替代set的作用，防止重复访问
    map<Node *, int> mapNodeStatus;
    //所有的节点状态先设为0
    for (auto it = _mapUndirectedGraph.begin(); it != _mapUndirectedGraph.end(); it++)
    {
        mapNodeStatus[it->first] = 0;
    }

    for (auto it = _mapUndirectedGraph.begin(); it != _mapUndirectedGraph.end(); it++)
    {
        if (mapNodeStatus[it->first] == 0)
        {
            printCycleHelp(it->first, mapNodeStatus);
        }
    }
}

void UndirectedGraphCycle::printCycleHelp(Node *node, map<Node *, int> &mapNodeStatus)
{
    //被访问过，状态改为 1
    mapNodeStatus[node] = 1;

    for (auto it = _mapUndirectedGraph[node].begin(); it != _mapUndirectedGraph[node].end(); it++)
    {
        Node *curr = *it;
        //状态是1，并且 curr 不是 node 按照dfs路径过来的父节点，那么就有环
        if (mapNodeStatus[curr] == 1 && _mapNodePaths[node] != curr)
        {
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
            _iCycleCount++;
        }
        //否则如果没有访问过，继续递归
        else if (mapNodeStatus[curr] == 0)
        {
            _mapNodePaths[curr] = node;
            printCycleHelp(curr, mapNodeStatus);
        }
    }
    //和node节点连通的所有节点都访问完，node节点的状态变为2
    mapNodeStatus[node] = 2;
}