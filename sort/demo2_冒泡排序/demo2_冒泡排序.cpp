#include <iostream>
#include <string>

using namespace std;

/*
冒泡排序思想：
	假如我们现在按身高升序排队，一种排队的方法是：
		从第一名开始，让两人相互比身高，若前者高则交换位置，更高的那个在与剩下的人比，
		这样一趟下来之后最高的人就站到了队尾。接着重复以上过程，直到最矮的人站在了队列首部。
		我们把队头看作水底，队尾看作水面，那么第一趟比较下来，最高的人就像泡泡一样从水底”冒“到水面，
		第二趟比较则是第二高的人……排队的过程即为对数据对象进行排序的过程（这里我们排序的”指标“是身高），
		上述过程即描述了冒泡排序的思想
*/

/*
	1.冒泡排序的空间复杂度为 O(1)
	2.当有相邻的两个元素大小相等的时候，不做交换，相同大小的数据在排序前后不会改变顺序，所以冒泡排序是稳定的排序算法。
	3.冒泡排序的时间复杂度为 O(n^2)
	
*/
int main()
{

	int array[10] = {8, 4, 6, 7, 2, 1, 3, 0, 9, 5};

	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	int len = 10;

	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (array[j] > array[j + 1])
			{
				int tem = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tem;
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}