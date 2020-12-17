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
/*
	变形问题1：查找第一个值等于给定值的元素
	变形问题2：查找最后一个值等于给定值的元素
	变形问题3：查找第一个大于等于给定值的元素
	变形问题4：查找最后一个小于等于给定值的元素
*/

//查找第一个值等于给定值的元素，返回下标
int find1(int array[], int len, int num)
{
	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (array[mid] > num)
			right = mid - 1;
		else if (array[mid] < num)
			left = mid + 1;
		else
		{
			//注意边界处理的值，是 left，不是 0
			if (mid == left || array[mid - 1] != num)
				return mid;
			else
				right = mid - 1;
		}
	}
	return -1;
}

//查找第一个值等于给定值的元素，返回下标。上面find1的简便写法

int find1Easy(int array[], int len, int num)
{
	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		//找到了相等的值，也不停，不去判断是否是第一个相等的元素，继续缩小范围朝前面找
		if (array[mid] >= num)
			right = mid - 1;
		else
			left = mid + 1;
	}
	/*
		这种方法下，比如我们要找的元素下标为 x ，当 mid 等于 x 时，也不停下来，让right = x - 1，
		而找到 x 以后，再也不会执行条件 if (array[mid] >= num)，
		right在之后的循环中就不会变了，也就是说，最终right的下一个元素就是我们要找的值，
		当 while 循环结束，left就等于 right + 1，也就是我们要找的 x

		这种方法运行时间要比find1长，因为每次找到相等的值，不去判断是否是 x，而是一直遍历到 left > right
	*/
	return left < len && array[left] == num ? left : -1;
}

//查找最后一个值等于给定值的元素，返回下标
int find2(int array[], int len, int num)
{
	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (array[mid] > num)
			right = mid - 1;
		else if (array[mid] < num)
			left = mid + 1;
		else
		{
			//注意边界处理的值，是 right， 不是 len - 1
			if (mid == right || array[mid + 1] != num)
				return mid;
			else
				left = mid + 1;
		}
	}
	return -1;
}

//查找最后一个值等于给定值的元素，返回下标。上面 find2的简便写法
int find2Easy(int array[], int len, int num)
{
	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (array[mid] <= num)
			left = mid + 1;
		else
			right = mid - 1;
	}

	//和find1Easy同理，while 循环结束以后，right 就是要找的 x，left等于 x + 1
	return right < len && array[right] == num ? right : -1;
}

//查找第一个大于等于给定值的元素，返回下标
int find3(int array[], int len, int num)
{
	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (array[mid] < num)
			left = mid + 1;
		else
		{
			//注意边界处理的值，是 left，不是 0
			if (mid == left || array[mid - 1] < num)
				return mid;
			else
				right = mid - 1;
		}
	}
	return -1;
}

//查找第一个大于等于给定值的元素，返回下标。find3的简便写法
int find3Easy(int array[], int len, int num)
{
	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;

		if (array[mid] >= num)
			right = mid - 1;
		else
			left = mid + 1;
	}
	//和find1同一原理
	return left < len && array[left] >= num ? left : -1;
}

//查找最后一个小于等于给定值的元素，返回下标
int find4(int array[], int len, int num)
{
	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (array[mid] > num)
			right = mid - 1;
		else
		{
			//注意边界处理的值，是 right， 不是 len - 1
			if (mid == right || array[mid - 1] > num)
				return mid;
			else
				left = mid + 1;
		}
	}
	return -1;
}

//查找最后一个小于等于给定值的元素，返回下标。find4的简便写法
int find4Easy(int array[], int len, int num)
{
	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (array[mid] <= num)
			left = mid + 1;
		else
			right = mid - 1;
	}

	//和find1Easy同理，while 循环结束以后，right 就是要找的 x，left等于 x + 1
	return right < len && array[right] == num ? right : -1;
}

int main()
{
	int len = 11;
	int arr[11] = {1, 4, 7, 10, 15, 23, 23, 23, 27, 33, 37};

	int num = 23;
	cout << "第一个值等于 " << num << " 的元素下标为 " << find1(arr, len, num) << endl;
	cout << "第一个值等于 " << num << " 的元素下标为 " << find1Easy(arr, len, num) << endl;
	cout << "最后一个值等于 " << num << " 的元素下标为 " << find2(arr, len, num) << endl;
	cout << "最后一个值等于 " << num << " 的元素下标为 " << find2Easy(arr, len, num) << endl;
	cout << "第一个大于等于 " << num << " 的元素下标为 " << find3(arr, len, num) << endl;
	cout << "第一个大于等于 " << num << " 的元素下标为 " << find3Easy(arr, len, num) << endl;
	cout << "最后一个小于等于 " << num << " 的元素下标为 " << find4(arr, len, num) << endl;
	cout << "最后一个小于等于 " << num << " 的元素下标为 " << find4Easy(arr, len, num) << endl;
	return 0;
}