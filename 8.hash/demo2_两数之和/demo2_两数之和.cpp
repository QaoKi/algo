#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/*
	给定一个数组，从里面拿出两个数，相加能否等于给定的num,如果能，找出所有可行的组合,
	打印他们在数组中的下标
*/

/*
	思路：
		方法1：暴力循环，遍历每种情况，时间复杂度分别为O(n^2)

		方法2： 
			两个数分别为x和y，把数组中所有的数先放到unordered_map中，值作为key，下标作为value,
			遍历一次x，每次去unordered_map中查看是否有num-x的值
*/

//两次循环
void twoSum(int arr[], int len, int num)
{
	//先将所有数存放到 unordered_map 中，值为key,下标为value
	unordered_map<int, int> mapInt;
	for (int i = 0; i < len; i++)
	{
		mapInt[arr[i]] = i;
	}

	//每次指定一个当前值 x ，去找是否有 num-x 的值，并且不能为 x 本身
	for (int i = 0; i < len; i++)
	{
		/*
			循环一开始就把unordered_map中x删除，这样做有两个目的，
			一个是让x不会和自身进行匹配，另一个是防止x和前面已经遍历过的值进行重复匹配
			比如数组中数据为 1	3  4  6  7，num为8，
			x为1时，匹配到7。当x为7时，如果1仍在unordered_map中，就会造成重复匹配
		*/
		mapInt.erase(arr[i]); //有的版本，earse()时，参数需要是迭代器
		if (mapInt.find(num - arr[i]) != mapInt.end())
		{
			cout << i << "  " << mapInt[num - arr[i]] << endl;
		}
	}
}

//一次循环
void twoSum1(int arr[], int len, int num)
{
	unordered_map<int, int> mapInt; //值做key，下标为value
	for (int i = 0; i < len; i++)
	{
		//直接去unordered_map中找是否有值 num-x，此时当前值x 还没有放入unordered_map中，所以不会和自身匹配
		//只不过输出的下标是反序的
		if (mapInt.find(num - arr[i]) != mapInt.end())
		{
			cout << i << "  " << mapInt[num - arr[i]] << endl;
		}

		//再把x放入到unordered_map中
		mapInt[arr[i]] = i;
	}
}

bool isAnagram(string s, string t)
{
	unordered_map<char, int> mapS;
	for (auto ch : s)
	{
		mapS[ch]++;
	}

	for (auto ch : t)
	{
		mapS[ch]--;
	}

	for (auto it : mapS)
	{
		if (it.second > 0)
			return false;
	}
	return true;
}

int main()
{
	int arr[5] = {1, 2, 4, 6, 7};
	int num = 8;

	twoSum(arr, 5, num);
	twoSum1(arr, 5, num);

	if (isAnagram("anagram", "nagaam"))
		cout << "相等" << endl;
	else
		cout << "不相等" << endl;
	return 0;
}