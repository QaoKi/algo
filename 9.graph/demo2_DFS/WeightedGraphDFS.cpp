#include "WeightedGraphDFS.h"
#include <stack>

void WeightedGraphDFS::printfHelp(Node *node, set<Node *> &setNode)
{
    if (node == NULL)
        return;
    cout << node->_data << "  ";
    setNode.insert(node);

    for (auto it = _mapWeightedGraph[node].begin(); it != _mapWeightedGraph[node].end(); it++)
    {
        if (setNode.find(it->first) == setNode.end())
        {
            //在遍历的同时，记录前一个节点
            _mapNodePaths[it->first] = node;
            printfHelp(it->first, setNode);
        }
    }
}

int WeightedGraphDFS::printfAllNodes()
{
    /*
        上面的printf()函数，是输出所有与根节点相连通的节点，
        但是有的节点不和根节点相连通，所有要遍历所有的节点，进行dfs
        这样同时也能求出连通量的数量
    */
    int count;
    set<Node *> setNode;
    for (auto it = _mapWeightedGraph.begin(); it != _mapWeightedGraph.end(); it++)
    {
        if (setNode.find(it->first) == setNode.end())
        {
            printfHelp(it->first, setNode);
            count++;
        }
    }

    cout << endl;
    return count;
}

void WeightedGraphDFS::printfAllEdge(multiset<Edge> &setAllEdge)
{
    //set中不能直接保存 Edge，因为Edge类重写了 <，
    //将edge对象加入set中时，如果两个edge的_weight相同，会被认为是同一个edge
    //用 set<pair<Node *, Node *>> 或者 multiset<Edge> 的方式，最好用 multiset<Edge>
    //因为在用set<pair<Node *, Node *>>处理有向图的重复遍历时会不准确

    for (auto it = _mapWeightedGraph.begin(); it != _mapWeightedGraph.end(); it++)
    {
        Node *from = it->first;
        for (auto itToNode = it->second.begin(); itToNode != it->second.end(); itToNode++)
        {
            Edge edge(from, itToNode->first, itToNode->second);
            if (setAllEdge.find(edge) == setAllEdge.end())
            {
                cout << from->_data << " to " << itToNode->first->_data << endl;
                setAllEdge.insert(edge);
            }
        }
    }
}