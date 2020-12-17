#include <stdio.h>

using namespace std;
/*
	给定一个数n，打印出所有排列情况
	比如给定3，打印出
		1, 2, 3
		1, 3, 2
		2, 1, 3
		2, 3, 1
		3, 1, 2
		3, 2, 1
*/

/*
	思路:
		1.如果能提前知道 n 的大小，采用n重循环能够实现，时间复杂度太高，O(n^n)
		2.递归
			如果确定了最后一位数据，那就变成了求解剩下 n−1 个数据的排列问题。而最后一位数据可以是 n 个数据中的任意一个，
			因此它的取值就有 n 种情况，所以，n 个数据的排列 问题，就可以分解成 n 个 n−1 个数据的排列的子问题

			同理，如果确定了第一位的数据，同样变成求解剩下 n-1 个数据的排列问题
*/

//从前往后确定
//k表示已经确定了几个数

void array_recursion(int array[], int len, int k)
{
	//每个位置都选定完了，输出这种情况
	if (k == len)
	{
		for (int i = 0; i < len; i++)
		{
			printf("%d ", array[i]);
		}
		printf("\n");
		return;
	}

	//每次确定第一位数据
	for (int i = k; i < len; i++)
	{
		int temp = array[i];
		array[i] = array[k];
		array[k] = temp;

		array_recursion(array, len, k + 1);

		//换回来
		temp = array[i];
		array[i] = array[k];
		array[k] = temp;
	}
}

int main()
{
	int array[3] = {1, 2, 3};
	array_recursion(array, 3, 0);
}