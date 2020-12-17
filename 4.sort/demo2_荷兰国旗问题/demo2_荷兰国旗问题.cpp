#include <iostream>
#include <string>

using namespace std;

/*
	给定一个数组arr，和一个数num，请把小于num的数放在数组的左边，等于num的数放在数组的中间，大于num的数放在数组的右边。
	要求额外空间复杂度O(1)，时间复杂度O(N)
	荷兰国旗问题：荷兰国旗是由红、白、蓝三色组成的，现在有若干个红、白、蓝三种颜色的球随机排列成一条直线。
					现在我们的任务是把这些球按照红、白、蓝排序。
*/

int main()
{

	int array[22] = {1, 5, 8, 2, 7, 3, 3, 9, 5, 2, 1, 5, 6, 4, 7, 2, 7, 8, 5, 6, 9, 8};

	int len = 22;

	for (int i = 0; i < len; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	//指定一个数：num = 5
	int num = 5;
	/*
	假设给定数组的第一个元素下标为0，0的左边有一个小于区域，元素都是小于num，那么小于区域的最后一个元素下标为-1
	最后一个元素下标为 len-1,len-1的右边有一个大于区域，元素都是大于num,那么大于区域的第一个元素下标为len
	刚开始让下标pl指向-1的元素，pr指向len的元素,遍历数组，当curr指向的元素等于num时，不用管
	当curr指向的元素小于num时，让curr指向的元素和pl指向的元素的下一个元素交换,并让pl++,即让小于区域向右增加一个
	如果curr指向0时就小于num,自己和自己交换，然后pl++
	如果curr指向的元素等于num时，不用管
	如果curr指向的元素大于num时，让curr指向的元素和pr指向的元素的上一个元素交换，
	并让pr--，即让大于区域向左增加一个，此时先不让curr++，先判断此时交换过来的值的大小
	当curr和pr相碰时停止
	*/

	int pl = -1;
	int pr = len;
	int curr = 0;
	while (curr < pr)
	{
		if (array[curr] < num)
		{
			swap(array[curr++], array[++pl]);
		}
		else if (array[curr] == num)
		{
			curr++;
		}
		else
		{
			swap(array[curr], array[--pr]);
		}
	}

	for (int i = 0; i < len; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	return 0;
}
