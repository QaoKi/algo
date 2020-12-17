#include <iostream>
#include <string>

using namespace std;

/*
	一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围0～n-1之内。
	在范围0～n-1内的n个数字中有且只有一个数字不在该数组中，请找出这个数字

	示例 1:
		输入: [0,1,3]
		输出: 2

	示例 2:
		输入: [0,1,2,3,4,5,6,7,9]
		输出: 8
*/

/*
	所要找的，是第一个值大于其下标的数字，比如 [0,1,2,3,4,6,7,8]，数字4的下标为4，
	但是数字6的下标为5,并且之后的每一个数字，都大于其下标，而我们要找的就是第一个这样的数字6，其下标，就是缺失的数字5

	这道题，其实和 查找有序数组中第一个等于给定值的下标，写代码的思路是一样的，让left和right不断的靠近要找的值
*/
int missingNumber(int array[], int len)
{

	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (array[mid] == mid)
			left = mid + 1;
		else
			//不去判断此时的 nums[mid]是否是第一个值大于下标的数字。继续缩小范围朝前面找
			right = mid - 1;
	}

	/*
		假设我们要找的数字为 x，那么array[x] 就等于 x + 1
		整个while循环的过程，是 left 和 right 不断向 x 靠近的过程
		当 mid等于x时，仍然符合 else的条件，所以 right最终等于 x - 1
		而 left 等于 x - 1时，仍然符合 if(array[mid] == mid)的条件，
		所以 left最终等于我们要找的 x，当 left 等于 x，并且 right等于x-1时，循环结束
	*/
	return left;
}

int main()
{
	int len = 8;
	int arr[8] = {0, 1, 2, 3, 4, 6, 7, 8};

	cout << "缺少值： " << missingNumber(arr, len) << endl;

	return 0;
}