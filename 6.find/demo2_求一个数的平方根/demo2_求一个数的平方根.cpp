#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/*
	给定一个数，返回这个数的平方根，比如给定9，返回3
	精确到小数点后n位
*/

/*
	采用二分法，0 <= k^2 <= num，所以下界和上界可以设置为 0 和传入的 num
	小数查找，比如小数后第一位，从x.0到(x+1).0，查找终止条件与整数一样，当前数小于，加0.1大于
*/

//只求整数部分
int find(int num)
{
	if (num == 0)
		return 0;
	//初始的左界和右界用0和num
	int left = 0;
	int right = num;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		/*
			为防止 mid*mid 产生溢出，用 if((long long) mid*mid == num) 判断
				或者用 if (mid == num / mid)，但是这种方法要注意 mid 为0 的时候会出错
			因为 mid 是整数，所以在上一步求 mid 的时候，mid会比实际的小
			比如 left + right 等于3，原本 mid应该为1.5，但是最后为1，变小了。
			所以在判断的时候要特殊处理，如果 mid*mid 小于 num，而 (mid + 1) * (mid + 1) > num，说明 mid就是要找的值
		*/
		if ((long long)mid * mid == num)
			return mid;
		else if (((long long)mid * mid < num))
		{
			if ((long long)(mid + 1) * (mid + 1) > num)
				return mid;
			//都不符合，接着找
			left = mid + 1;
		}
		else
			right = mid - 1;
	}
	return 0;
}

//精确到小数点后n位
double Sqrt(int num, int n)
{
	if (num == 0)
		return 0;
	//先找整数位
	int interval = find(num);
	/*
		再找小数位，一位一位的找，先找小数点后第一位，再找第二位。。。每一位都是独立的。和找整数的思想一样。
		比如找小数点后第一位，如果 mid * mid < num 而 (mid + 0.1) * (mid + 0.1) > num，说明 mid 就是要找的值
		精确到小数点后n位，就循环 n 次（可以多循环一次，因为要看最后一位来四舍五入）
	*/

	//interval 此时是整数位，精确的小数位处于 interval 和 interval + 1 之间
	double mid = interval;
	double pos = 1;
	for (int i = 0; i < n; i++)
	{
		double left = mid;
		double right = mid + pos; //求小数点后一位，右界在 mid 和 mid + 1之间，后两位，右界在 mid 和 mid + 0.1之间
		pos /= 10;
		//每一次 while循环结束，就说明找到了第i+1位小数，而mid就等于精确到小数点后 i+1位的值
		while (left <= right)
		{
			mid = left + (right - left) / 2;
			if (mid * mid == num)
				break;
			else if (mid * mid < num)
			{
				if ((mid + pos) * (mid + pos) > num)
					break;
				//都不符合
				left = left + pos;
			}
			else
				right = right - pos;
		}
	}
	return mid;
}

int main()
{

	int num = 8;
	// cout << fixed << setprecision(i) 是调整输出的格式，setprecision(i) 输出小数点后i位
	//多循环一次，setprecision 会处理最后一位的四舍五入
	int n = 3;
	cout << fixed << setprecision(n) << Sqrt(num, n + 1) << endl;

	return 0;
}