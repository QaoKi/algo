#ifndef UNDIRECTED_GRAPH_DFS_H
#define UNDIRECTED_GRAPH_DFS_H

#include <iostream>
#include <set>
#include "../UndirectedGraph/UndirectedGraph.h"

using namespace std;

/*
    时间复杂度：
        每条边最多会被访问两次，一次是遍历，一次是回退。所以，图上的深度优先搜索算法的时间复杂度是 O(E)，E 表示边的个数
        函数 printfAllNodes() 又遍历了一遍所有的节点，所以时间复杂度为 O(E + V)
        总的空间复杂度：O(V)，V是顶点个数
*/

class UndirectedGraphDFS : public UndirectedGraph
{
public:
    UndirectedGraphDFS(){};
    ~UndirectedGraphDFS(){};

    //递归遍历节点，找出所有与根节点相连通的节点。
    void printf();
    void printfHelp(Node *node, set<Node *> &setNode);

    //递归遍历节点，输出所有的节点，并返回图的连通量数量
    int printfAllNodes();

    //非递归遍历节点，找出所有与根节点相连通的节点。
    void printf_noRecursion();

    //DFS是一条路走到头，到头以后再回溯，不适合找最短路径
    //输出以start节点为开始节点，到其他节点的所有路径，这些节点都和 start节点连通
    void printfAllPaths(Node *start);

    //输出以start节点为开始节点，到end节点的路径
    void printfPathsStartToEnd(Node *start, Node *end);

protected:
    /*   
		DFS，是从根节点开始，沿着一条路走到底，然后一个节点一个节点的回溯，
        <a, b>, a和b是相互连接的，b是a的前一个节点，通过a可以找到它的前一个节点b，
        当查找节点 root-w之间的路径时，需要根据w的前一个节点是谁，一直往回找，回溯一遍经过的节点
        但是这样找到的路径不是最短路径，因为无法控制DFS访问的顺序，比如，root和a是连接的
        root和b也是连接的，b和a也是连接的，root-a最短的路径是 root -> a，但是可能会出现 root ->b->a
	*/
    unordered_map<Node *, Node *> _mapNodePaths;
};

#endif