#include <iostream>
#include <string>
#include <time.h>
#include "../heap/heap.h"

using namespace std;

/*
	将给定数据构建成一个大根堆，堆顶元素是数组中最大的值，移除堆顶元素，进行 heapify操作，
	完成以后，堆顶元素是数组第二个元素，重复 k-1 次，将数组中前 k-1 大的数都移除出堆，
	那么堆顶的元素就是数组中第 k 大的元素

	时间复杂度：O(nlogn)
*/

//构建堆，时间复杂度O(n)
void buildHeap(int array[], int len)
{
	/*
		遍历整个数组，从0位置开始，让每个元素去和它的父节点比较，
		为什么要从0位置开始，因为比如当遍历到数组的中间元素，从头开始的话，那么这个元素前面的所有元素，已经组成了大根堆
		只需要用这个节点去和它的父节点比较
	*/

	for (int i = 0; i < len; i++)
	{
		int index = i;
		//只要这个节点比它的父节点大，就和父节点交换，不会发生越界，因为就算index跳到0位置，(0-1)/2 还是0
		while (array[index] > array[(index - 1) / 2])
		{
			swap(array[index], array[(index - 1) / 2]);
			index = (index - 1) / 2; //此时这个节点的下标已经变了,变成原来的父节点的下标，它会有一个新的父节点，再和新的父节点比较
		}
	}
}

void heapify(int array[], int len, int index) //index 是值改变的节点的下标
{
	int left = 2 * index + 1; //左孩子的下标
	while (left < len)
	{
		//当右孩子不越界，并且比左孩子的值大时，largest 为右孩子下标，否则 largest 为左孩子下标
		int largest = array[left] < array[left + 1] && left + 1 < len ? left + 1 : left;
		//把左右孩子中较大的值，再与改变后的值比较
		if (array[index] >= array[largest]) //改变后的值还是比左右孩子大，就不用动
			break;

		//当改变后的值没有左右孩子大
		swap(array[index], array[largest]);

		//交换完以后，把下标换换，还要再接着比较交换完以后的左右孩子大小
		index = largest;
		left = 2 * index + 1;
	}
}

int sort(int array[], int len, int k)
{
	//构建一个大根堆
	buildHeap(array, len);
	//执行 k-1 次移除堆顶元素执行 heapify操作
	int length = len;
	for (int i = 0; i < k - 1; i++)
	{
		swap(array[0], array[--length]);
		heapify(array, length, 0);
	}

	return array[0];
}

int main()
{

	// int array[9] = {3, 2, 3, 1, 2, 4, 5, 5, 6};

	// int len = 9;

	// int k = 4;
	int array[2] = {-1, -1};

	int len = 2;

	int k = 2;

	for (int i = 0; i < len; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	Heap minHeap(HeapFlagMin, k);
	for (int i = 0; i < len; i++)
	{
		minHeap.heapInsert(array[i]);
	}

	cout << "第" << k << "大的元素值为：" << minHeap.getHeap() << endl;

	int num = sort(array, len, k);
	cout << "第" << k << "大的元素值为：" << num << endl;

	return 0;
}
