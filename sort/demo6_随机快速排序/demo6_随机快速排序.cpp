#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

/*
	经典快速排序的问题：
		当数组为  1,2,3,4,5,6  有序的数据状况时， 每次选定最后一个数作为num，那么大于num的区域就没有了
		每次一趟只能搞定一个数，时间复杂度变为O(n^2)
		随机快排：
		每次随机的在数组中选定一个值放到数组的最后作为num，这样涉及到概率，长期期望的时间复杂度：O(n*logn)，

	随机快排是工程中最常用的，因为时间复杂度的常数项比归并排序少
*/

void rand_quick_sort(int arr[], int L, int R)
{
	if (L >= R)
		return;

	//数据的数据状况是不可控的，但是可以采用方法，打乱固定的数据状况
	//1.随机，从数组中随机取值，和数据状况无关
	//2.哈希
	//在这里随机从数组中取一个值放到数组的最后

	int index = rand() % (R - L + 1) + L;
	int num = arr[index];
	int pl = L - 1; //指向小于num值区域的最后一个值
	int pr = R + 1; //指向大于num值区域的第一个值
	int curr = L;	//当前值的下标，遍历的指针

	//遍历所有的数，小于num的放到小于区域，大于的放到大于区域，等于放到中间
	while (curr < pr)
	{
		if (arr[curr] < num)
		{
			swap(arr[curr++], arr[++pl]);
		}
		else if (arr[curr] > num)
		{
			swap(arr[curr], arr[--pr]); //curr先不加1，再判断换过来的这个数的值
		}
		else
		{
			curr++;
		}
	}

	//到这时，数组从L-pl的数据是小于num的数，pr-R是大于num的值
	//再继续拆分，直到剩一个数
	rand_quick_sort(arr, L, pl);
	rand_quick_sort(arr, pr, R);
}

int main()
{

	int array[10] = {5, 9, 4, 7, 2, 0, 6, 8, 1, 3};

	int len = 10;

	for (int i = 0; i < len; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	srand(time(0));
	rand_quick_sort(array, 0, 9); //传入左右下标

	for (int i = 0; i < len; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	return 0;
}
