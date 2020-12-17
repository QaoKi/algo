#include <iostream>
#include <string>

using namespace std;

/*
	【题目】 给定一个有N*M的整型矩阵matrix和一个整数num，matrix的每一行和每一列都是排好序的。
			实现一个函数，判断num是否在matrix中。
			例如：

				0	1	2	5
				2	3	4	7
				4	4	4	8
				5	7	7	9
			如果num为7，返回true；如果num为6，返回false。

	【要求】 时间复杂度为O(N+M)额外空间复杂度为O(1)
*/

/*
	思路：
		两种方法，一个是从右上角开始找，一种是从左下角开始找
		从右上角开始找：
			右上角第一个数curr和num对比，如果比num大，说明curr所在列的下面不会有num，因为curr所
			在行，curr是最小的，此时curr向左移动一位，如果curr比num小，说明curr所在行的前面的数不会有
			num，因为curr所在行中，curr是最大的，此时curr向下移动，一直到如果行或列都找完还没有，就没有
		从左下角开始找同理
*/

bool get(int arr[4][4], int num)
{
	bool bRet = false;
	int cH = 0;
	int cL = 3;		//curr值的指针，初始值指向右上角的第一个数
	while (cH <= 3 && cL >= 0)		//当curr还指向矩阵中
	{
		if (arr[cH][cL] == num)
		{
			bRet = true;
			break;
		}
		else if(arr[cH][cL] > num)
		{
			cL--;
		}
		else
		{
			cH++;
		}
	}
	return bRet;
}

int main()
{

	int arr[4][4] = { {0,1,2,5},{2,3,4,7},{4,4,4,8},{5,7,7,9} };

	int num = 6;
	if (get(arr,num))
	{
		cout << "有" << endl;
	}
	else
	{
		cout << "没有" << endl;
	}

	system("pause");
	return 0;
}