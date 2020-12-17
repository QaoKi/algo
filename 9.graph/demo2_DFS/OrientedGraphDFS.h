#ifndef ORIENTED_GRAPH_DFS_H
#define ORIENTED_GRAPH_DFS_H

#include <iostream>
#include <set>
#include "../OrientedGraph/OrientedGraph.h"

using namespace std;

class OrientedGraphDFS : public OrientedGraph
{
public:
    OrientedGraphDFS(){};
    ~OrientedGraphDFS(){};

    void printfHelp(Node *node, set<Node *> &setNode);

    //递归遍历节点，输出所有的节点
    void printfAllNodes();

    //递归遍历节点，输出所有从node出发可以到达的节点
    void printf(Node *node);

    //有向图的单点可达性：给定节点start和end，是否存在一条从 start到达end的有向路径
    bool findPathsStartToEnd(Node *start, Node *end);

    /*
        多点可达性：给定一个节点end，和一个节点集合，是否存在一条有向路径可以到达end，这条有向路径的起点可以是给定集合中任意节点
            也就是说，节点end，在给定的集合中，是否有节点指向它。这里直接用图中所有节点代替集合

        多点可达性的应用：垃圾回收：在一副有向图中，一个顶点表示一个对象，一条有向边则表示一个对象对
            另一个对象的引用，如果一个对象，没有指向它的边，说明这个对象没有被引用，就可以被释放
    */
    bool findPaths(Node *end);

protected:
    unordered_map<Node *, Node *> _mapNodePaths;
};

#endif