#include <stdio.h>
#include <memory.h>

/*
    想写出没有 bug 的循环队列的实现代码，关键是，确定好队空和队满的判定条件。

    先用数组实现一个普通的队列。
        tail指向的是下一个可以存储的位置，tail指向的位置是不含有数据的
        所以当tail等于len的时候，说明tail的值超过了数据的长度，队列满了
        head是第一个有数据的数组下标，所以当head == tail时，说明队列空了
*/
class Queue
{
public:
    Queue()
    {
        len = 10;
        memset(m_value, 0, sizeof(m_value[0]) * len);
        head = 0;
        tail = 0;
    }

    void push(int num)
    {
        if (tail == len)
            //满了
            return;
        m_value[tail++] = num;
    }

    int pop()
    {
        if (head == tail)
            //空的
            return 0;
        return m_value[head++];
    }

private:
    int m_value[10];
    int len;
    int head;
    int tail;
};

/*
    循环队列判断空的情况仍然是 head == tail
    判断满的情况，会牺牲一个存储空间
        (tail + 1) % len == head 时判断为满

        在 head 和 tail 之间有一个空间没有存放数据，所以会牺牲一个存储空间
*/

class CyclicQueue
{
    CyclicQueue()
    {
        len = 10;
        memset(m_value, 0, sizeof(m_value[0]) * len);
        head = 0;
        tail = 0;
    }

    void push(int num)
    {
        if ((tail + 1) % len == head)
            //满了
            return;
        //放到尾节点
        m_value[tail] = num;
        //更新tail值
        tail = (tail + 1) % len;
    }

    int pop()
    {
        if (head == tail)
            //空的
            return 0;
        int ret = m_value[head];
        head = (head + 1) % len;
        return ret;
    }

private:
    int m_value[10];
    int len;
    int head;
    int tail;
};

int main()
{

    return 0;
}