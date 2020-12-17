#include <iostream>
#include <string>

using namespace std;

/*
	二分查找的条件：
		1，必须是有序的
		2，能够通过索引访问，所以一般都是数组，所以需要连续的内存。如果是链表这种，复杂度会增高
		3，数据量太少，不如直接遍历找。而数据量太大，因为数据要用连续的内存存储，对空间消耗太大

	时间复杂度：O(logn)
*/

bool find(int array[], int len, int num)
{
	int left = 0;
	int right = len - 1;
	while (left <= right) //注意终止条件是 left <= right，而不是 left < right
	{
		//为防止两数相加溢出，采用两数相减的方法
		//再进一步就是用位运算  int mid = left + ((right - left) >> 1 );
		int mid = left + (right - left) / 2;
		if (array[mid] == num)
			return true;
		else if (array[mid] < num)
			left = mid + 1; //注意 left 和 right 值的更新，不然可能会和快排一样出现死循环
		else
			right = mid - 1;
	}
	return false;
}

int main()
{
	int len = 9;
	int arr[9] = {1, 4, 7, 10, 15, 23, 27, 33, 37};

	int num = 23;

	if (find(arr, num, len))
		cout << "find" << endl;
	else
		cout << "not find" << endl;

	return 0;
}