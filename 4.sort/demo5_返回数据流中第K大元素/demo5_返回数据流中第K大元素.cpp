#include <iostream>
#include <string>
#include "../heap/heap.h"

using namespace std;

/*
	有一个动态数据流，不断的产生数据出来，接收这些数据，随时返回当前数据中第K大元素
	比如数据流为 1，3，6，9，第3大元素为3，数据流为 1,3,6,9,5，第3大元素为5
	
*/

/*
	思路：
	第一种，维护一个数组，长度为K，存放最大的值到第K大的值，有新的数据进来，如果比第K大的数
	要小，不管，如果比第K大的数要大，保留，扔掉原来的第K大元素，插入排序，把数组重新排序
	数组的最后一个元素，就是第K大元素

	第二种，用一个小根堆，根头节点为堆中最小的数，保持根堆的数量为K个，那么根头就是第K大元素
	每次进来一个新的数据，如果比根头小，不管，如果比根头大，扔掉根头，重新把根堆排成小根堆


*/

int GetK(Heap &minHeap, int num)
{
	minHeap.heapInsert(num);
	return minHeap.getHeap();
}

int main()
{

	//数据流
	int array[20] = {8, 4, 6, 7, 2, 1, 3, 0, 9, 5, 11, 15, 17, 14, 13, 19, 18, 16, 10, 12};

	int k = 1;
	//申请一个小根堆
	Heap minHeap(HeapFlagMin, k);

	for (int i = 0; i < 20; i++)
	{
		//每次产生一个数，放入到数据流中
		int num = GetK(minHeap, array[i]);
		cout << "第" << k << "大元素：  " << num << "  值 " << array[i] << " 进" << endl;
	}

	return 0;
}