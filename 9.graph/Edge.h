#ifndef _EDGE_H_
#define _EDGE_H_

#include <iostream>
#include "Node.h"

class Edge
{
public:
    Edge()
    {
        _from = NULL;
        _to = NULL;
        _weight = 0;
    }
    Edge(Node *from, Node *to, int weight)
    {
        _from = from;
        _to = to;
        _weight = weight;
    }
    ~Edge(){};

    Edge(const Edge &other)
    {
        _from = other._from;
        _to = other._to;
        _weight = other._weight;
    }
    //放入优先级队列中
    bool operator<(const Edge &other) const
    {
        return _weight > other._weight; //小根堆
    }

public:
    int _weight; //这条边的权重是多少
    Node *_from; //从哪来
    Node *_to;   //指向谁
};
#endif