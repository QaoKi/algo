#ifndef INDEX_MIN_HEAP_H
#define INDEX_MIN_HEAP_H

#include <iostream>
#include <string>
#include "../../9.graph/Edge.h"
using namespace std;

/*
    https://zhuanlan.zhihu.com/p/35381524
    https://www.jianshu.com/p/e13406ae5b1b
    普通优先级队列，只能弹出队列头部数据，不能随便更改队列中的数据
    用无向连通权重图的边为数据。普通的优先级队列，排序的是边的权重（Edge重写了 < 操作符），索引优先队列，排序的是key值，
    这个key值，是_value数组的下标，insert(int k, Edge e)，将e放到_value[k]位置
    _pq数组作为优先级队列，里面存放的是_value的下标，排序的规则，按照Edge的权重
    这样的好处是，
    1，可以通过key找到数据，数据在_value中不需要移动，要调整数据的位置，只需要在pq中调整key值的位置
    2，可以随时更改key处的数据，change(int key, Edge f)，将key处的数据改为f
*/

class IndexMinHeapEdge
{

public:
    IndexMinHeapEdge(int capacity);
    ~IndexMinHeapEdge();

    //在 _value[key] 处插入数据
    void insert(int key, Edge e);
    void pop();

    //位置key是否存在元素，有数据返回true
    bool contain(int key);

    //返回队列头数据
    Edge top();

    //返回队列头部数据所对应的key值
    int topIndex();

    //改变key位置的数据
    void change(int key, Edge e);

    void del(int key);

private:
    //从下往上，上浮，n是 _pq 的下标
    void swim(int n);
    //从下往上，下沉，n是 _pq 的下标
    void sink(int n);

    void exch(int a, int b);

private:
    //优先级队列
    int *_pq;
    //pq的逆序
    int *_qp;
    //用无向联调权重图的边为数据
    Edge *_value;
    int _capacity;
    int _size;
};

#endif