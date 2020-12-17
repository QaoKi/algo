#include <iostream>
#include <string>

using namespace std;

/*
	经典快速排序思想：
		刚开始选定数组尾部的元素 x，将小于x的元素放到左边，大于x的元素放到数组右边，数组被分为两部分，
		再分别选定左右数组的尾部元素，将小于的放到左边，大于的放到右边，分治思想
*/

int sort(int arr[], int L, int R)
{

	if (L >= R) //终结条件
		return 0;

	//每次取最后一个值作为num值
	int num = arr[R];
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
		else if (arr[curr] == num)
		{
			curr++;
		}
		else
		{
			//curr先不加1，再判断换过来的这个数的值
			swap(arr[curr], arr[--pr]);
		}
	}
	//到这时，数组从L-pl的数据是小于num的数，pr-R是大于num的值
	//再继续拆分，直到剩一个数
	sort(arr, L, pl);
	sort(arr, pr, R);

	return 0;
}

//还有一种写法，感觉这种写法更好理解
int sort1(int arr[], int L, int R)
{

	if (L >= R) //终结条件
		return 0;

	//每次取第一个值作为num值
	int num = arr[L];
	int pl = L;		  //指向等于num值区域的第一个值
	int pr = R;		  //指向等于num值区域的最后一个值
	int curr = L + 1; //当前值的下标，遍历的指针

	//遍历所有的数，小于num的放到小于区域，大于的放到大于区域，等于放到中间
	while (curr <= pr)
	{
		if (arr[curr] < num)
		{
			swap(arr[curr++], arr[pl++]);
		}
		else if (arr[curr] == num)
		{
			curr++;
		}
		else
		{
			//curr先不加1，再判断换过来的这个数的值
			swap(arr[curr], arr[pr--]);
		}
	}
	//到这时，数组从L到pl - 1的数据是小于num的数，pr + 1到R是大于num的值
	//再继续拆分，直到剩一个数
	sort(arr, L, pl - 1);
	sort(arr, pr + 1, R);

	return 0;
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

	sort(array, 0, 9); //传入左右下标

	for (int i = 0; i < len; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}
