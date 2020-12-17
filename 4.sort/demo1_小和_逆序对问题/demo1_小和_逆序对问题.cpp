#include <iostream>
#include <string>

using namespace std;

/*
	小和问题：
	在一个数组中，每一个数左边比当前数小的数累加起来，叫做这个数组的小和。求一个数组
	的小和。
	例子：
	[1,3,4,2,5]
	1左边比1小的数，没有；
	3左边比3小的数，1；
	4左边比4小的数，1、3；
	2左边比2小的数，1；
	5左边比5小的数，1、3、4、2；
	所以小和为1+1+3+1+1+3+4+2=16


	数组[4,2,5,1,7,3,6]  小和为 36
*/

/*
	逆序对问题
	在一个数组中，左边的数如果比右边的数大，则折两个数构成一个逆序对，请打印所有逆序对
*/
/*
	用归并排序解决
	在左边数组和右边数组合并的时候，左边数组下标指针pl,右边数组下标指针pr
	当pl指向的元素小于pr指向的元素，统计一下右边的数组中pr指向的元素后面还有几个元素，这些元素，都是pl的小和 num +=个数*pl
	当pl指向的元素大于等于pr指向的元素，不用管，正常的按归并排序操作
	当两个数组小和归并完成，小和求完以后，组成新的数组，新的数组中内部的小和已经被求完，就不用再管了，只需要看下次合并的两个数组，
	左数组中有多少右数组的小和
*/
void merge(int arr[], int L, int mid, int R, int &num)
{
	//L和R是数组arr的左边下标和右边下标
	int pl = L;		  //指针指向左边数组的第一个元素
	int pr = mid + 1; //指针指向右边数组的第一个元素
	int index = 0;

	int *help = new int[R - L + 1]; //辅助数组

	while (pl <= mid && pr <= R) //比较两个数组，把小的数依次放入 help 中
	{

		num += arr[pl] < arr[pr] ? arr[pl] * (R - pr + 1) : 0;
		/*
			输出逆序对，注意，当两个数组合并的时候，如果左边的数组pl的元素大于右边数组pr的元素，那么左数组pl后面的元素也都大于
			pr指向元素和pr后面的所有元素
			比如有 7 8 9  2 3 4，pl指向7，pr指向2，此时pl和pl后面的所有元素都和pr组成逆序对，如果此时不打印(8,2)和(9,2)
				那么下一次pr的指向后移，就错过了2
		*/
		if (arr[pl] > arr[pr])
		{
			for (int i = pl; i <= mid; i++)
			{
				cout << "(" << arr[i] << "," << arr[pr] << ")  ";
			}
			cout << endl;
		}

		help[index++] = arr[pl] <= arr[pr] ? arr[pl++] : arr[pr++];
	}

	while (pl <= mid)
	{
		help[index++] = arr[pl++];
	}
	while (pr <= R)
	{
		help[index++] = arr[pr++];
	}

	for (int i = 0; i < index; i++)
	{
		arr[L + i] = help[i];
	}
	delete[] help;
}

void sort(int arr[], int L, int R, int &num)
{
	if (L >= R) //终止条件
		return;

	int mid = (L + R) / 2; //求中间

	/*
	小技巧，防止溢出：mid = L + (R-L)/2
	a/2 == a >> 1  a除以2，等于a右移一位
	所以  mid = L + (R-L) >> 1
	位运算比算数运算快很多
	
	*/

	sort(arr, L, mid, num);
	sort(arr, mid + 1, R, num);

	merge(arr, L, mid, R, num); //数组合并

	return;
}

int main()
{
	int array[8] = {4, 2, 5, 1, 7, 3, 6, 8};

	int len = 8;

	for (int i = 0; i < len; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	int num = 0; //小和

	sort(array, 0, len - 1, num);

	for (int i = 0; i < len; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	cout << "小和：   " << num << endl;

	return 0;
}
