#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

/*
	给定一个数组，从里面拿出三个数，相加能否等于给定的num,如果能，找出所有可行的组合,
	打印他们在数组中的下标。

	这题分多种情况，
		如果要找到x,y,z的下标，并且给定的数组中有重复的数，那么只能用方法1
			比如，数组为 -4, -1, -1, -1, 2, 2, 3，num = 0，
			当 x 的下标为 1时，值为-1，如果用第二种方法，下标 2,3,4,5 中可匹配的项有 (2,4),(2,5),(3,4),(3,5)
			可匹配的项太多，只能双重循环才能找全
	
		而如果是只找到x,y,z的值，并且答案中不可以包含重复的 x,y,z，那么不管数组中有没有重复的数，都可以用方法2
		比如，数组为 -4, -1, -1, -1, 2, 2, 3，num = 0，
		当 x 为第一个-1时，y 和 z 的下标 分别为(2,4)时符合，那么x,y,z的值就为 -1,-1,2,
		当 y和 z的下标为(2,5)时，x,y,z的值为 -1,-1,2，虽然也符合，但是和上面的重复了

*/

/*
	思路：
		1，三个数分别为x、y和z,把数组中所有的数先放到unordered_map中，值作为key，下标作为value,
		遍历两次，先遍历出每种x+y的情况，再去unordered_map中查找是否有num-(x+y)，这样时间复杂度为O(n^2)
		因为要用unordered_map存储每个数，所以空间复杂度为O(n)

		2，排序加双指针，先把数组排好序，第一层遍历，把x选好，然后让两个指针next和max分别指向x的下一个值和
		数组的最后一个值，数组的最后一个值是数组的最大值，让next和max相加，如果得到的值比num-x小，那就让
		next向后移动，如果比next+max 比num-x大，就让max向前移动
		没有用到额外的空间，排序的时间复杂度为O(N*logN)，查找的时间复杂度为O(n^2)，所以总体的时间
		复杂度为O(n^2)，但是排序会改变原来数组的数据的顺序
*/

//返回x,y,z的下标
vector<vector<int>> threeSumWay1(int arr[], int len, int num)
{
	vector<vector<int>> ret;
	//先把数组中所有数都放到unordered_map中
	unordered_map<int, int> mapInt;
	for (int i = 0; i < len; i++)
	{
		mapInt[arr[i]] = i;
	}

	//两层循环，遍历出所有x+y的情况
	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			//在unordered_map中寻找是否有 complement
			int complement = num - arr[i] - arr[j];
			/*
				如果找到了 complement ，要排除这个值不是arr[i]和arr[j]
				complement 值的下标肯定是要大于 i 和 j的，而同时j又是大于i的，所以让 complement的下标大于 j就可以了
				让complement大于j是防止重复数据的出现,并且还能保证不是arr[i]和arr[j]
				比如 1	3	4	6	7  num = 8
				i = 0,j = 1的时候，能匹配到4，打印 0 1 2
				i = 0,j = 2的时候，能匹配到3，但是是重复的数据，所以要向前找
			
			*/
			if (mapInt.find(complement) != mapInt.end() && mapInt[complement] > j)
			{
				cout << i << "  " << j << "  " << mapInt[complement] << endl;
				ret.push_back(vector<int>{i, j, mapInt[complement]});
			}
		}
	}
	return ret;
}

//使用双指针，只输出 x,y,z的值
vector<vector<int>> threeSumWay2(int arr[], int len, int num)
{
	vector<vector<int>> ret;
	//对数组排序
	std::sort(arr, arr + len);

	for (int i = 0; i < len; i++)
	{
		//数组中可能有重复的值，当前值x去重，防止重复计算
		if (i > 0 && arr[i] == arr[i - 1])
			continue;
		int left = i + 1;			   //当前值的下一个值的下标
		int right = len - 1;		   //数组最后一个值的下标
		int complement = num - arr[i]; //x确定了，去数组中找 y 和 z
		while (left < right)
		{
			if (arr[left] + arr[right] > complement)
				right--;
			else if (arr[left] + arr[right] < complement)
				left++;
			else
			{
				cout << i << "  " << left << "  " << right << endl;
				ret.push_back(vector<int>{arr[i], arr[left], arr[right]});
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

	return ret;
}

int main()
{
	int arr[6] = {-1, 0, 1, 2, -1, -4};
	int num = 0;

	threeSumWay1(arr, 6, num);
	threeSumWay2(arr, 6, num);

	return 0;
}