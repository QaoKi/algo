#include <string>
#include <stdio.h>
#include <queue>

using namespace std;

/*
	�������Ƚ��ȳ���ջ���Ƚ����

	ʹ���������У�a��b��ÿ��push����Ԫ�ؼ���a,���簴����� 1,2,3,4,5,��ôa�ĶӶ���1���ӵ���5,�����ջ�Ļ���ջ��Ӧ����5��ջ����1
	pop��ʱ�򣬰�a�� 1,2,3,4 ����������b�У�ֻ����һ��Ԫ�أ������һ�������أ����൱�ڵ�����ջ��
	b��Ϊ 1��2,3,4  �´��ٵ�����ʱ�򣬰�1,2,3������a�У���b�����һ��Ԫ�� 4 ����
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

			//�ı�����
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
