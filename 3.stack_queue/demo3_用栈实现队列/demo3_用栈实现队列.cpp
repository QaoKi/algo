#include <string>
#include <stdio.h>
#include <stack>

using namespace std;

/*
	队列是先进先出，栈是先进后出

	使用两个栈，push和pop，每次push，把元素加入push,比如按序加入 1,2,3,4,5,那么push的栈顶是5，栈底是1,
	如果是队列的话，队顶应该是1，队底是5
	把push栈中的所有数据，导入pop栈中，那么pop栈中数据栈顶为1，栈底为5，
	push的时候，就把数据加到push栈中，pop的时候，就把pop栈中的数据弹出，
	当pop栈中还有数据时，不能将push栈中的数据拷贝到pop中，只有当pop栈中为空时，才能把push栈中的数据赋值到pop栈中
*/

class Queue
{

public:
    void push(int num)
    {
        //入队列的时候，只将数据放到 stackPush 中
        stackPush.push(num);
    }

    int pop()
    {
        //如果 stackPop 没有数据，将 stackPush 中的数据依次取出放到 stackPop中
        int ret = 0;
        if (stackPop.empty())
        {
            while (!stackPush.empty())
            {
                int temp = stackPush.top();
                stackPush.pop();
                stackPop.push(temp);
            }
        }

        if (!stackPop.empty())
        {
            ret = stackPop.top();
            stackPop.pop();
        }

        return ret;
    }

private:
    stack<int> stackPush;
    stack<int> stackPop;
};
int main()
{
    Queue que;
    que.push(1);
    que.push(2);
    que.push(3);
    que.push(4);
    que.push(5);

    printf("pop: %d\n", que.pop());
    printf("pop: %d\n", que.pop());
    que.push(6);
    que.push(7);
    printf("pop: %d\n", que.pop());
    que.push(8);
    que.push(9);

    printf("pop: %d\n", que.pop());
    printf("pop: %d\n", que.pop());
    printf("pop: %d\n", que.pop());
    printf("pop: %d\n", que.pop());
    printf("pop: %d\n", que.pop());
    printf("pop: %d\n", que.pop());
    printf("pop: %d\n", que.pop());

    return 0;
}