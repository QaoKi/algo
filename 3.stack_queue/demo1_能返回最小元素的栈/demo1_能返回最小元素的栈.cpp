#include <stdio.h>
#include <stack>

using namespace std;
/*
	实现一个特殊的栈，在实现栈的基本功能的基础上，再实现返
	回栈中最小元素的操作

	【要求】1．pop、push、getMin操作的时间复杂度都是O(1)。
			2．设计的栈类型可以使用现成的栈结构。
*/

/*
	思路，getMin的时间复杂度要求是O(1)，那就不能每次调用的时候再去遍历寻找最小值
			构建两个栈，一个是数据栈，一个存放最小值栈，每次压栈的时候，把此时栈中的的最小值压到最小值栈中，
            每次出栈的时候，把数据栈的栈顶和最小值的栈顶都弹出
			调用getMin方法时，返回最小值栈的栈顶元素
*/

class Stack
{
public:
    Stack(){};
    ~Stack(){};

    void push(int num)
    {
        m_normalStack.push(num);
        if (m_minStack.empty())
            m_minStack.push(num);
        else
        {
            int minNum = num < m_minStack.top() ? num : m_minStack.top();
            m_minStack.push(minNum);
        }
    }

    void pop()
    {
        if (m_normalStack.empty() || m_normalStack.empty())
            return;
        m_normalStack.pop();
        m_minStack.pop();
    }

    int getMin()
    {
        if (m_normalStack.empty())
            return 0;
        return m_minStack.top();
    }

private:
    stack<int> m_normalStack;
    stack<int> m_minStack;
};

int main()
{

    Stack sta;
    // sta.push(1);
    sta.push(8);
    sta.push(15);
    //sta.push(2);
    sta.push(9);
    sta.push(5);

    printf("min: %d\n", sta.getMin());

    sta.pop();
    printf("min: %d\n", sta.getMin());
    return 0;
}