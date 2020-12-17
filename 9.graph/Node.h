#ifndef _NODE_H_
#define _NODE_H_

struct Node
{
    int _data;

    Node(int data)
    {
        _data = data;
    }

    Node(const Node &other)
    {
        _data = other._data;
    }
};

#endif