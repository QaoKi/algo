#ifndef UNDIRECTED_GRAPH_BFS_H
#define UNDIRECTED_GRAPH_BFS_H

#include <iostream>
#include "../UndirectedGraph/UndirectedGraph.h"

using namespace std;

/*
    时间复杂度：
        每条边都会被访问一次，时间复杂度是 O(E)
        总的空间复杂度：O(V)，V是顶点个数
*/

class UndirectedGraphBFS : public UndirectedGraph
{
public:
    UndirectedGraphBFS(){};
    ~UndirectedGraphBFS(){};

    //设start节点为第0层，和start节点直接相连的是第1层节点，和第1层节点直接相连的是第2层节点
    //相当于按层遍历
    void printf(Node *start);

    //BFS可以用来找最短路径，因为是按层遍历，其实函数流程和DFS是一样的，只不过BFS找到的路径就是最短路径而已
    //输出从start节点到其他节点的最短路径
    void printfAllPaths(Node *start);

    //以start为第0层节点开始遍历，第一次遍历到end节点，那么就是从start到end的最短路径
    void printfPathsStartToEnd(Node *start, Node *end);

protected:
    //<a, b>，a和b直接相连，b是a的上一层节点
    unordered_map<Node *, Node *> _mapNodePaths;
};

#endif