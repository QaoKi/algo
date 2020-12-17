#include "IndexMinHeap.h"

IndexMinHeap::IndexMinHeap(int capacity)
{
    if (capacity > 0)
    {
        _capacity = capacity;
        _size = 0;
        //_pq数组下标从0开始使用
        _pq = new int[capacity];
        _qp = new int[capacity];
        _value = new int[capacity];

        //逆序数组中值初始化为-1
        for (int i = 0; i < capacity; i++)
            _qp[i] = -1;
    }
}

IndexMinHeap::~IndexMinHeap()
{
    delete[] _pq;
    delete[] _qp;
    delete[] _value;
}

void IndexMinHeap::insert(int key, int data)
{
    if (key >= _capacity || key < 0)
        return;

    //先确保key初没有数据
    if (contain(key))
        return;

    //插入到小根堆的尾部，稍后调整位置，_pq中保存的是 key值
    _pq[_size] = key;
    //_pq的逆序
    _qp[key] = _size;
    //数据插入到key下标
    _value[key] = data;

    //调整key在小根堆中的位置，放置到堆中合适的位置
    swim(_size);
    //下标从0开始使用的情况下，_size指向下一个可以插入数据的位置下标
    _size++;
}

void IndexMinHeap::pop()
{
    if (_size > 0)
    {
        //弹出根顶元素，让最后一个元素替换上去，再下沉
        //和最后一个元素交换，_size指向下一个可以插入数据的位置下标，所以最后一个元素的下标为 _size - 1
        exch(0, _size - 1);
        //在调整之前让size减少
        _size--;
        sink(0);
        //清除数据，_value中的数据就不清了，存放的不是指针
        //_size已经减过
        _qp[_pq[_size]] = -1;
    }
}

bool IndexMinHeap::isEmpty()
{
    return _size == 0;
}

bool IndexMinHeap::contain(int key)
{
    return _qp[key] != -1;
}

int IndexMinHeap::top()
{
    return _value[_pq[0]];
}

int IndexMinHeap::topIndex()
{
    return _pq[0];
}

void IndexMinHeap::change(int key, int data)
{
    if (key >= _capacity || key < 0)
        return;

    //key处原来没有数据，直接插入
    if (!contain(key))
    {
        insert(key, data);
    }
    else
    {
        //key处原来有数据
        _value[key] = data;
        //swim操作的是_pq的下标，_qp[key]就是该key在_pq的下标
        swim(_qp[key]);
        sink(_qp[key]);
    }
}

void IndexMinHeap::del(int key)
{
    //把尾部数据和key处交换，然后调整位置
    int index = _qp[key];
    exch(index, _size - 1);
    //在调整之前让size减少
    _size--;

    swim(index);
    sink(index);

    //清除数据，_value中的数据就不清了，存放的不是指针
    _qp[key] = -1;
}

void IndexMinHeap::swim(int n)
{
    /*
        上浮，和父节点比较，
        _pq从下标0开始使用，下标n的父节点的下标是(n - 1) / 2
        _pq从下标1开始使用，下标n的父节点的下标是 n / 2
        用边的权重比较，
        n只是 _pq的下标，数据在 _value 中的下标为 _pq[n]，所以 _value[_pq[n]] 就是权重
    */
    int index = n;
    while (index > 0 && _value[_pq[index]] < _value[_pq[(n - 1) / 2]])
    {
        //_value中的数据不用动，_pq中存的是_value的下标
        //交换数据，将_pq[index]和_pq[(n - 1) / 2]互换
        exch(index, (n - 1) / 2);
        index = (n - 1) / 2;
    }
}

void IndexMinHeap::sink(int n)
{
    //下沉，和左右节点中，较小的那个比较
    int index = n;
    int left = 2 * index + 1; //左节点
    while (left < _size)
    {
        int compare = left + 1 < _size && _value[_pq[left + 1]] < _value[_pq[left]] ? left + 1 : left;
        if (_value[_pq[index]] < _value[_pq[compare]])
            return;
        //交换
        exch(index, compare);
        index = compare;
        left = 2 * index + 1;
    }
}

void IndexMinHeap::exch(int a, int b)
{
    //因为_qp数据也要变，所以要先预存下来
    int i = _pq[a], j = _pq[b];
    swap(_pq[a], _pq[b]);
    swap(_qp[i], _qp[j]);
}