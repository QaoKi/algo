#include <iostream>
#include <string>
#include <time.h>

using namespace std;

/*
	O(n) 时间复杂度内求无序数组中的第 K 大元素。比如：4, 2, 5 , 12, 3, 1, 6 这样一组数据，第 3 大元素就是4

	思路：
		选择数组的最后一个元素，即下标n-1作为num，对数组中的数据进行排序，小于num的放到num的右面，大于num的
		放到num的左面，完成一个倒序，假设排完序以后，num的下标为p，则0~p-1为大于num的值的下标，p+1~n-1为小于num的值的下标
		如果p = k-1,那么值num就是要求的值，如果 p>k-1，说明要解的值在0~p-1的区间中，如果p<k-1，说明要解的值在
		p+1~n-1的区间中，再把解所在的区间进行排序
*/

int sort(int arr[], int L, int R, int K)
{
	if (L >= R)
		return arr[L];
	int index = rand() % (R - L + 1) + L;
	int num = arr[index];
	int pl = L - 1; //大于区域的初始下标
	int pr = R + 1; //小于区域的初始下标
	int curr = L;	//当前值的下标
	while (curr < pr)
	{
		if (arr[curr] > num)
		{
			swap(arr[curr++], arr[++pl]);
		}
		else if (arr[curr] == num)
		{
			curr++;
		}
		else
		{
			swap(arr[curr], arr[--pr]);
		}
	}

	/*
	到这时，L-pl的数据是大于num的数，pl+1 是等于 num 的值（num是从数组中取的，所以必存在），pr到R是小于num的数
	小区间 （L,pl) 和 (pr,R)中数据是不保证有序的，有保证的是 num 在（L,pl) 和 (pr,R)之间，
	num 的下标是 pl+1，也就是说 num 是数组中的第 pl+2 大的值
	*/
	if (pl + 2 == K)
	{
		return arr[pl + 1];
	}
	else if (pl + 2 > K)
	{
		return sort(arr, L, pl, K);
	}
	else
	{
		/*
		注意的点：
			1，第2个参数要传入 pl+2,把 num 这个值这次排序以后就摘出去了，不再参与下一次排序
				如果传入 pl+1，num参与下一次排序，会出现死循环的情况，
				比如数组为[1,1],K=2，第一次调用为 sort(arr,0,1,2),
				这种情况下，pl为 -1，经过了while循环以后，pl值没变，还是-1，
				那么如果传入pl+1，函数调用就为 sort(arr,-1 + 1,1,2),陷入死循环
			2，第4个参数依然传入K，之前想的是传入 K - (pl + 1)，因为觉得前 pl+1大的数已经确定了
				但是其实不用，因为是用下标进行比较的
		*/
		return sort(arr, pl + 2, R, K);
	}
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
	srand(time(0));
	int num = sort(array, 0, len - 1, k); //传入左右下标和要求的第 K 大元素

	cout << "第" << k << "大的元素值为：" << num << endl;

	return 0;
}
