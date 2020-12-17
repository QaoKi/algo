#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <string>

using namespace std;
enum HeapFlag
{
    HeapFlagMin = 0,
    HeapFlagMax
};

class Heap
{

public:
    Heap(HeapFlag flag, int capacity);
    ~Heap();

    bool heapInsert(int num);
    int removeHeap();
    int getHeap();
    int getLength();

private:
    //堆顶元素改变以后，重新堆化
    void heapify();

private:
    int *_heap;
    int _capacity;
    int _length;
    HeapFlag _flag;
};

#endif