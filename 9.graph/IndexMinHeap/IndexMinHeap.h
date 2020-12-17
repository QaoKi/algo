#ifndef INDEX_MIN_HEAP_H
#define INDEX_MIN_HEAP_H

#include <iostream>
#include <string>
#include "../Node.h"
using namespace std;

/*
    https://zhuanlan.zhihu.com/p/35381524
    https://www.jianshu.com/p/e13406ae5b1b
    https://cloud.tencent.com/developer/article/1065252
    
    普通优先级队列，只能弹出队列头部数据，不能随便更改队列中的数据
    _value数组，存放的是实际真实数据，insert(int key, int data)，将 data 放到_value[key]位置
    _pq数组作为小根堆（优先级队列），里面存放的是_value的下标，也就是key值。这个key值就是索引
    排序的规则，根据_value数组的类型来自定义（排序的不是key值的大小，而是根据_value[key]数据自定义，只不过_pq数组保存的是key值）
    _qp存放的是_pq数组的逆序对，可以根据key值，找到该key在_pq数组中的下标，
    比如，_pq[index] = key，那么_qp[key] = index，index是_pq的下标，
    初始化时让_qp的数据都为-1，如果_qp[key] == -1，说明该key没有保存在_pq中

    索引优先队列的好处是，
    1，可以随时更改key处的数据，change(int key, int data)，将key处的数据改为 data
    2，可以通过key找到数据，数据在_value中不需要移动，要调整数据的位置，只需要在_pq中调整key值的位置
*/

/*
    使用索引优先队列，要注意一点，在初始化索引队列的时候，要传入最大的索引值，以此来初始化内存
    在之后 insert(key, data)时，key不能超过这个值
*/

class IndexMinHeap
{

public:
    IndexMinHeap(int capacity);
    ~IndexMinHeap();

    //在 _value[key] 处插入数据
    void insert(int key, int data);
    void pop();

    bool isEmpty();

    //位置key是否存在元素，有数据返回true
    bool contain(int key);

    //返回队列头数据
    int top();

    //返回队列头部数据所对应的key值
    int topIndex();

    //改变key位置的数据
    void change(int key, int data);

    void del(int key);

private:
    //从下往上，上浮，n是 _pq 的下标
    void swim(int n);
    //从下往上，下沉，n是 _pq 的下标
    void sink(int n);

    //交换数据，a和b是 _pq的下标
    void exch(int a, int b);

private:
    //优先级队列
    int *_pq;
    //pq的逆序
    int *_qp;
    //用无向联调权重图的边为数据
    int *_value;
    int _capacity;
    int _size;
};

#endif