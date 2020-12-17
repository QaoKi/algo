#include <iostream>
#include <string>

using namespace std;

/*
	归并排序思想：
	分治的思想
*/

/*
	1.在合并的过程中，如果 arr[L…mid]和 arr[mid+1…R]之间有值相同的元素，先把 arr[L…mid中的元素放入 help 数组。
		这样就保证了值相同的元素，在合并前后的先后顺序不变。所以，归并排序是一个稳定的排序算法。
	2.时间复杂度：不管是最好情况、最坏情况，还是平均情况，时间复杂度都是 O(nlogn)
	3.每次合并操作都需要申请额外的内存空间，但在合并完成之后，临时开辟的内存空间就被释放掉了。
		在任意时刻，CPU 只会有一个函数在执行，也就只会有一个临时的内存空间在使用。
		临时内存空间最大也不会超过 n 个数据的大小，所以空间复杂度是 O(n)。
*/
void merge(int arr[], int L, int mid, int R)
{
	//L和R是数组arr的第一个值下标和最后一个值下标
	int pl = L;		  //指针指向左边数组的第一个元素
	int pr = mid + 1; //指针指向右边数组的第一个元素
	int index = 0;	  //数组 help 的下标

	int *help = new int[R - L + 1]; //辅助数组，保存这两个数组排完序以后的数
	while (pl <= mid && pr <= R)	//当两个指针都在各自的数组内，比较两个数组，把小的数依次放入help中
	{
		//当pl指向的值大于pr指向的值，返回pr指向的值，否则返回pl指向的值
		help[index++] = arr[pl] <= arr[pr] ? arr[pl++] : arr[pr++];
	}

	//把数组中没有处理完的数依次放到help中
	while (pl <= mid)
	{
		help[index++] = arr[pl++];
	}

	while (pr <= R)
	{
		help[index++] = arr[pr++];
	}

	//拷贝回原来的数组，这里的处理要注意
	for (int i = 0; i < index; i++)
	{
		arr[L + i] = help[i];
	}
	delete[] help;
}
//传入数组的第一个值的下标和最后一个值的下标
void sort(int arr[], int L, int R)
{
	//终止条件
	if (L >= R)
		return;
	//求中间
	int mid = (L + R) / 2;

	//将数组分为两部分，一部分为 L到mid，一部分为 mid+1到R
	//再接着拆分，直到拆分到每一部分只剩一个数，即当L=R的时候停止
	sort(arr, L, mid);
	sort(arr, mid + 1, R);

	//把每一个子部分，两两按大小合并,一直到最后合并成总的
	merge(arr, L, mid, R);
}

int main()
{
	int array[10] = {8, 4, 6, 7, 2, 1, 3, 0, 9, 5};

	int len = 10;

	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	sort(array, 0, 9);

	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	return 0;
}
