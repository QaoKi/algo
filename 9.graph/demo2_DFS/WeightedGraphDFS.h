#ifndef WEIGHTED_GRAPH_DFS_H
#define WEIGHTED_GRAPH_DFS_H

#include <iostream>
#include <set>
#include "../Edge.h"
#include "../WeightedGraph/WeightedGraph.h"

using namespace std;

class WeightedGraphDFS : public WeightedGraph
{
public:
    WeightedGraphDFS(){};
    ~WeightedGraphDFS(){};

    void printfHelp(Node *node, set<Node *> &setNode);

    //递归遍历节点，输出所有的节点，并返回图的连通量数量
    int printfAllNodes();

    void printfAllEdge(multiset<Edge> &setAllEdge);

protected:
    unordered_map<Node *, Node *> _mapNodePaths;
};

#endif