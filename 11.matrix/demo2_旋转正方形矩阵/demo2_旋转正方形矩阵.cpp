#include <iostream>
#include <string>

using namespace std;

/*
	题目：给定一个整型正方形矩阵matrix，请把该矩阵调整成顺时针旋转90度的样子。
	例如：	
			1	2	3	4
			5	6	7	8
			9	10	11	12
			13	14	15	16
	旋转以后变为：
			13	9	5	1
			14	10	6	2
			15	11	7	3
			16	12	8	4
	【要求】 额外空间复杂度为O(1)
*/

/*
	思路：假设1号位置的下标为(a,b)，12号位置的下标为(c,d)，
	那么就是下面的情况：
				b			d

		a		1	2	3	4
				5	6	7	8
				9	10	11	12
		c		13	14	15	16

	旋转以后变为：
				b			d
		 a		13	9	5	1
				14	10	6	2
				15	11	7	3
		 c		16	12	8	4

		先打印外圈的正方形，再打印内圈的正方形，
		1号位置调到4号位置，4号到16号，16到13，13到1
		2号到8号，8到15，15到9，9到2
		3号到12号，12到14，14到5，5到3
*/

void printEdge(int arr[4][4], int lH, int lL, int rH, int rL)
{
	int times = rL - lL; //每一行每一列要处理多少个数，也就是每一行的长度减一，和转圈打印一样，每一行的最后一个数，留给下一次处理，这样容易处理边界问题

	int tmp = 0;
	for (int i = 0; i != times; i++)
	{
		//每次要让4条边中的4个数交换完成
		//第一次处理每条边的第一个数，第二次处理每条边的第二个数，第三次处理每条边的第三个数
		tmp = arr[lH][lL + i];			   //先保存第一条边的数
		arr[lH][lL + i] = arr[rH - i][lL]; //把第四条边的数移动到第一条
		arr[rH - i][lL] = arr[rH][rL - i]; //把第三条边的数移动到第四条
		arr[rH][rL - i] = arr[lH + i][rL];
		arr[lH + i][rL] = tmp;
	}
}

int main()
{

	int arr[4][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

	int lH = 0; //左上角的行
	int lL = 0; //左上角的列
	int rH = 3; //右下角的行
	int rL = 3; //右下角的列

	while (lH < rH && lL < rL)
	{
		printEdge(arr, lH++, lL++, rH--, rL--);
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << arr[i][j] << "  " << endl;
		}
	}

	return 0;
}