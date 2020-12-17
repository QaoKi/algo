#include <string>
#include <stdio.h>
#include <queue>

using namespace std;

/*
	队列是先进先出，栈是先进后出

	使用两个队列，a和b，每次push，把元素加入a,比如按序加入 1,2,3,4,5,那么a的队顶是1，队底是5,如果是栈的话，栈顶应该是5，栈底是1
	pop的时候，把a中 1,2,3,4 弹出拷贝到b中，只留下一个元素，把最后一个数返回，就相当于弹出了栈顶
	b中为 1，2,3,4  下次再弹数的时候，把1,2,3拷贝到a中，把b的最后一个元素 4 弹出
*/

class Stack
{

public:
	void push(int num)
	{
		queueData.push(num);
	}

	int pop()
	{
		int ret = 0;
		while (queueData.size() > 1)
		{
			int temp = queueData.front();
			queueData.pop();
			queueHelp.push(temp);
		}

		if (!queueData.empty())
		{
			ret = queueData.front();
			queueData.pop();

			//改变引用
			auto temp = queueData;
			queueData = queueHelp;
			queueHelp = temp;
		}
		return ret;
	}

private:
	queue<int> queueData;
	queue<int> queueHelp;
};

int main()
{

	Stack sta;
	sta.push(1);
	sta.push(2);
	sta.push(3);
	sta.push(4);
	sta.push(5);

	printf("pop: %d\n", sta.pop());
	printf("pop: %d\n", sta.pop());
	printf("pop: %d\n", sta.pop());
	printf("pop: %d\n", sta.pop());
	printf("pop: %d\n", sta.pop());
	printf("pop: %d\n", sta.pop());

	return 0;
}
