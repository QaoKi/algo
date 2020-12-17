#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

/*
	给定一个包含 n 个整数的数组 nums 和一个目标值 target，
	判断 nums 中是否存在四个元素 a，b，c 和 d，
	使得a + b + c + d的值与 target 相等？找出所有满足条件且不重复的四元组。
	
	答案中不可以包含重复的四元组。
*/

//使用双指针，返回 a,b,c,d 的值，不包含重复的 a,b,c,d
vector<vector<int>> fourSum(int arr[], int len, int num)
{
	vector<vector<int>> ret;
	//对数组排序
	std::sort(arr, arr + len);

	//先确定一个值 a
	for (int i = 0; i < len; i++)
	{
		//数组中可能有重复的值，当前值 a 去重，防止重复计算
		if (i > 0 && arr[i] == arr[i - 1])
			continue;

		//再确定一个值 b
		for (int j = i + 1; j < len; j++)
		{
			//再对 b 去重，注意条件是 j > i + 1，
			if (j > i + 1 && arr[j] == arr[j - 1])
				continue;

			int left = j + 1;						//当前值的下一个值的下标
			int right = len - 1;					//数组最后一个值的下标
			int complement = num - arr[i] - arr[j]; //a 和 b 确定了，去数组中找 c 和 d

			while (left < right)
			{
				if (arr[left] + arr[right] > complement)
					right--;
				else if (arr[left] + arr[right] < complement)
					left++;
				else
				{
					ret.push_back(vector<int>{arr[i], arr[j], arr[left], arr[right]});
					//数组中可能有重复的值，去除重复
					while (left < right && arr[left] == arr[left + 1])
						left++;
					while (left < right && arr[right] == arr[right - 1])
						right--;
					right--;
					left++;
				}
			}
		}
	}

	return ret;
}

int main()
{
	int arr[6] = {-1, 0, 1, 2, -1, -4};
	int num = 0;

	fourSum(arr, 6, num);

	return 0;
}