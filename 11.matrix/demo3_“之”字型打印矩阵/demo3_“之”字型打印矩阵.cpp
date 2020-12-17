#include <iostream>
#include <string>

using namespace std;
/*
	题目：给定一个整型矩阵matrix

	例如：	1	2	3	4
			5	6	7	8
			9	10	11	12

	按照“之”字形的方式打印这个矩阵,结果为：1，2，5，9，6，3，4，7，10，11，8，12
	也就是每次都斜着打印
	【要求】 额外空间复杂度为O(1)
*/

/*
	思路：这道题目，数值的下标移动没有规律可找
		  采用两个辅助指针，两个点a和b，初始下标都为(0,0)，
				a

			b	1	2	3	4
				5	6	7	8
				9	10	11	12
		  a向右走，每次走一步，当向右走到头时，向下走，一直到走到最右下角
		  b向下走，每次走一步，当向下走到头时，向右走，一直到走到最右下角
					a

				1	2	3	4
			b	5	6	7	8
				9	10	11	12

			a和b之间就构成了一条斜线，比如，从a打印到b，让a的列号--，行号++，一直打印到b
			从b打印到a，让b的列号++，行号--,一直打印到a

*/

void printLevel(int arr[3][4], int aH, int aL, int bH, int bL,bool fromUp)
{
	if (fromUp)
	{
		while (aH <= bH)
		{
			cout << arr[aH++][aL--]<<"  ";
		}
	}
	else
	{
		while (bH >= aH)
		{
			cout << arr[bH--][bL++]<<"  ";
		}
	}
}

void printZhi(int arr[3][4])
{
	int aH = 0;	//辅助点a的行号
	int aL = 0; //辅助点a的列号
	int bH = 0;	//辅助点b的行号
	int bL = 0;	//辅助点b的列号

	int endH = 2;	//最后一个数的行号
	int endL = 3;	//最后一个数的列号

	bool fromUp = false;	//true为从a打印到b，false为从b打印到a

	while (aH <= endH)	//只有当a点走到最后一个点的时候，a的行号才会等于最后一个点的行号
	{
		printLevel(arr,aH,aL,bH,bL,fromUp);//打印当前a和b组成的斜线上的数

		//让a和b每次移动一个位置

		//如果a的列号等于最后一个数的列号，说明a向右走到了头，让a向下移动，行号加1,否则行号不变，列号加1
		aH = aL == endL ? aH + 1 : aH;
		aL = aL == endL ? aL : aL + 1;

		//如果b的行号等于最后一个数的行号，说明b向下走到了头，让b向右移动，列号加1,否则列号不变，行号加1
		//要主要改变行号和列号的顺序，因为判断的标准是b的行号和最后一个数的行号比较，
		//不能把b的行号改变了以后，还拿着去和最后一个数的行号比较，这样列号就不准了
		//下面是错误的
		//bH = bH == endH ? bH : bH + 1;
		//bL = bH == endH ? bL + 1 : bL;
		//正确的
		bL = bH == endH ? bL + 1 : bL;
		bH = bH == endH ? bH : bH + 1;
		fromUp = !fromUp;
	}
}

int main()
{

	int arr[3][4] = { 1,2,3,4,5,6,7,8,9,10,11,12 };

	printZhi(arr);

	system("pause");
	return 0;
}