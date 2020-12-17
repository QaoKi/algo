#include <iostream>
#include <string>

using namespace std;

/*
	假设按照升序排序的数组在预先未知的某个点上进行了旋转
	例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2]
	搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回-1。
	假设数组中不存在重复的元素。时间复杂度要求O(logn)。
*/

/*
	时间复杂度为 O(logn)的方法
	int mid = left + (right - left) / 2;
	求出一个下标的中间值 mid，数组分成两部分，[left, mid] 和 [mid + 1, right]
	这两部分肯定有一部分是有序的，另一部分可能是有序的，也可能仍然是一个循环有序数据
	比如 [4,5,6,7,8,9,0,1,2]，mid = 7,
	分成 [4,5,6,7,8] 和 [9,0,1,2]，前半部分是有序的，后半部分是仍是一个循环有序数组
	判断这两部分，哪部分是有序的，再判断 num 是否在有序的部分中，
	如果不再有序的部分，重复上面的步骤，继续拆分循环有序数组
*/
int findOlogN(int array[], int len, int num)
{

	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (array[mid] == num)
			return mid;

		//如果前半部分是有序的
		if (array[left] <= array[mid])
		{
			//num是否在前半部分中
			if (array[left] <= num && num < array[mid])
				//在前半部分中
				right = mid - 1;
			else
				//不在前半部分，继续去拆分后半部分
				left = mid + 1;
		}
		else
		{
			//前半部分不是有序的，后半部分肯定是有序的
			//num是否在后半部分中
			if (array[mid] < num && num <= array[right])
				//在后半部分中
				left = mid + 1;
			else
				//不在后半部分，继续去拆分前半部分
				right = mid - 1;
		}
	}

	return -1;
}

int main()
{
	int len = 9;
	int arr[9] = {4, 5, 6, 7, 8, 9, 0, 1, 2};
	int num = 1;

	cout << "值 " << num << " 的下标为： " << findOlogN(arr, len, num) << endl;

	return 0;
}