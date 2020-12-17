#include "heap.h"

Heap::Heap(HeapFlag flag, int capacity)
{
    _capacity = 0;
    _length = 0;
    _flag = flag;
    if (capacity > 0)
    {
        _heap = new int[capacity];
        _capacity = capacity;
    }
}

Heap::~Heap()
{
    if (_heap)
    {
        delete[] _heap;
        _heap = nullptr;
    }
}
bool Heap::heapInsert(int num)
{
    if (_length >= _capacity)
    {
        /*
            堆满了，如果是小根堆，进来的数据比堆顶大就让进入，如果是大根堆，进来的数据比堆顶小就让进入
            这样的话，如果是大根堆，就维持了动态数据流中 capacity 个较小的值，堆顶就是动态数据流中第 capacity 小的元素
            如果是小根堆，就维持了动态数据流中 capacity 个较大的值，堆顶就是动态数据流中第 capacity 大的元素
        */
        if ((_flag == HeapFlagMin && num > _heap[0]) || (_flag == HeapFlagMax && num < _heap[0]))
        {
            //替换掉堆顶元素，然后重新堆化
            _heap[0] = num;
            heapify();

            return true;
        }
    }
    else
    {
        _heap[_length] = num;
        int index = _length;
        //一直朝上，和父节点进行对比， -1/2 结果是0，所以不用担心越界
        while ((_flag == HeapFlagMin && _heap[index] < _heap[(index - 1) / 2]) || (_flag == HeapFlagMax && _heap[index] > _heap[(index - 1) / 2]))
        {

            swap(_heap[index], _heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }

        _length++;

        return true;
    }
    return false;
}

int Heap::removeHeap()
{
    if (_length <= 0)
        return -1;
    int ret = _heap[0];

    swap(_heap[0], _heap[--_length]);
    heapify();

    return ret;
}

int Heap::getHeap()
{
    if (_length <= 0)
        return -1;
    return _heap[0];
}

int Heap::getLength()
{
    return _length;
}

void Heap::heapify()
{
    int index = 0;
    int left = index * 2 + 1;
    while (left < _length)
    {
        //找到左右节点中较大或较小的值
        int largest = 0;
        if (_flag == HeapFlagMin)
            largest = left + 1 < _length && _heap[left + 1] < _heap[left] ? left + 1 : left;
        else
            largest = left + 1 < _length && _heap[left + 1] > _heap[left] ? left + 1 : left;

        //值改变以后，还是符合条件
        if ((_flag == HeapFlagMin && _heap[index] < _heap[largest]) || (_flag == HeapFlagMax && _heap[index] > _heap[largest]))
            return;

        //交换
        swap(_heap[index], _heap[largest]);
        index = largest;
        left = index * 2 + 1;
    }
}