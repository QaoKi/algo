#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
	题目：给定一个整型矩阵matrix，请按照顺时针的方式打印它
	例如：
			1	2	3	
			4	5	6
			7	8	9
			10	11	12
	打印结果为： 1	2	3	6	9	12	11	10	7	4	5	8
	【要求】 额外空间复杂度为O(1)
*/

/*
	思路：假设1号位置的下标为(a,b)，12号位置的下标为(c,d)，
	那么就是下面的情况：
				b		d
		
		a		1	2	3
				4	5	6
				7	8	9
		c		10	11	12

		打印按照从b一直加到d为止，再从a加到从c，再从d减到b，再从c减到a，这样外圈就打印完了
		注意边界情况的处理，当整个矩阵只有一行或一列，即a==c或者b==d时，
		每次打印一行或一列的时候，把最后一个留出来，等到下一行或下一列的时候打印

	当外圈打印完了，让左上角的横纵坐标分别加1，让右下角的横纵坐标分别减1，再打印第二圈
	当左上角的横坐标或纵坐标，大于右下角的横坐标或纵坐标时停止
*/

//打印一圈
void printLoop(vector<vector<int>> &vecMatrix, int leftHeng, int leftZong, int rightHeng, int rightZong)
{
	//左上角的横坐标等于右下角的横坐标，说明只有一行
	//如果不用这两个if来特殊处理 只有一行或者一列的数据，会有问题

	if (leftHeng == rightHeng)
	{
		for (int i = leftZong; i <= rightZong; i++)
			cout << vecMatrix[leftHeng][i] << "   ";
	}
	else if (leftZong == rightZong) //左上角的纵坐标等于右下角的纵坐标，说明只有一列
	{
		for (int i = leftHeng; i <= rightHeng; i++)
			cout << vecMatrix[i][leftZong] << "   ";
	}
	else
	{
		//用4个while循环，打印外圈。每一行和每一列的最后一个数，等到下一行或下一列的时候打印，所以条件是 < ，而不是 <=

		//先打印最上面的一行，横坐标不变，纵坐标从左打到右
		int i = leftZong;
		while (i < rightZong)
			cout << vecMatrix[leftHeng][i++] << "   ";

		//再打印最右边的一列，纵坐标不变，横坐标从上到下
		i = leftHeng;
		while (i < rightHeng)
			cout << vecMatrix[i++][rightZong] << "   ";

		//再打印最下面的一行，横坐标不变，纵坐标从右到左
		i = rightZong;
		while (i > leftZong)
			cout << vecMatrix[rightHeng][i--] << "   ";

		//最后打印最左边的一列，纵坐标不变，横坐标从下到上
		i = rightHeng;
		while (i > leftHeng)
			cout << vecMatrix[i--][leftZong] << "   ";
	}
}

void printMatrix(vector<vector<int>> &vecMatrix)
{
	if (vecMatrix.size() == 0) //一行也没有
		return;
	/*
		1	2	3	
		4	5	6
		7	8	9
		10	11	12
	*/

	//左上角的坐标和右下角的坐标。行号表示的是横坐标，列号表示的是纵坐标
	int leftHeng = 0;
	int leftZong = 0;
	int rightHeng = vecMatrix.size() - 1;
	int rightZong = vecMatrix[0].size() - 1;

	while (leftHeng <= rightHeng && leftZong <= rightZong)
	{
		//一圈打印完以后，左上角的行和列分别加1，右下角的行和列分别减1
		printLoop(vecMatrix, leftHeng, leftZong, rightHeng, rightZong);

		leftHeng++;
		leftZong++;
		rightHeng--;
		rightZong--;
	}
}

int main()
{
	//外面的是行，里面的是列
	vector<vector<int>> vecMatrix;
	//{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}
	//4行3列。行：row，列：column
	int row = 4;
	int column = 3;
	for (int i = 0; i < row; i++)
	{
		vector<int> vecRow;
		for (int j = 0; j < column; j++)
		{
			cout << i * column + j + 1 << "  ";
			vecRow.push_back(i * column + j + 1);
		}
		cout << endl;
		vecMatrix.push_back(vecRow);
	}

	printMatrix(vecMatrix);
	return 0;
}