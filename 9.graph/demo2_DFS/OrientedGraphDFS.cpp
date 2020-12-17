#include "OrientedGraphDFS.h"
#include <stack>

void OrientedGraphDFS::printfHelp(Node *node, set<Node *> &setNode)
{
    if (node == NULL)
        return;
    cout << node->_data << "  ";
    setNode.insert(node);

    for (auto it = _mapOrientedGraph[node].begin(); it != _mapOrientedGraph[node].end(); it++)
    {
        if (setNode.find(*it) == setNode.end())
        {
            //在遍历的同时，记录前一个节点
            _mapNodePaths[*it] = node;
            printfHelp(*it, setNode);
        }
    }
}

void OrientedGraphDFS::printfAllNodes()
{
    set<Node *> setNode;
    for (auto it = _mapAllNode.begin(); it != _mapAllNode.end(); it++)
    {
        if (setNode.find(it->second) == setNode.end())
            printfHelp(it->second, setNode);
    }
    cout << endl;
}

void OrientedGraphDFS::printf(Node *node)
{
    set<Node *> setNode;
    printfHelp(node, setNode);
    cout << endl;
}

bool OrientedGraphDFS::findPathsStartToEnd(Node *start, Node *end)
{
    //先填充 _mapNodePaths
    set<Node *> setNode;
    printfHelp(start, setNode);
    cout << endl;

    /*
        要先检查 start节点到end节点是否可达
        _mapNodePaths 被填充了以后，如果是可达的，
        那么 _mapNodePaths.find(end) != _mapNodePaths.end();
    */

    if (_mapNodePaths.find(end) == _mapNodePaths.end())
    {
        cout << start->_data << " not path to " << end->_data << endl;
        return false;
    }

    cout << start->_data << " to " << end->_data << ": ";
    //因为查找的顺序是反着查，使用栈让数据正序
    stack<Node *> stackNode;
    //反向一直找到start
    Node *curr = end;
    while (curr != start)
    {
        stackNode.push(curr);
        curr = _mapNodePaths[curr];
    }

    cout << start->_data;
    while (!stackNode.empty())
    {
        Node *curr = stackNode.top();
        stackNode.pop();
        cout << "->" << curr->_data;
    }
    cout << endl;

    return true;
}

bool OrientedGraphDFS::findPaths(Node *end)
{
    //先填充 _mapNodePaths，递归遍历所有的有向边
    set<Node *> setNode;
    for (auto it = _mapOrientedGraph.begin(); it != _mapOrientedGraph.end(); it++)
    {
        if (setNode.find(it->first) == setNode.end())
        {
            printfHelp(it->first, setNode);
        }
    }
    cout << endl;

    if (_mapNodePaths.find(end) == _mapNodePaths.end())
    {
        cout << " not path to " << end->_data << endl;
        return false;
    }

    cout << " have path to " << end->_data << endl;
    return true;
}