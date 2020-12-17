#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/*
	����һ�����������������ƽ�������������9������3
	��ȷ��С�����nλ
*/

/*
	���ö��ַ���0 <= k^2 <= num�������½���Ͻ��������Ϊ 0 �ʹ���� num
	С�����ң�����С�����һλ����x.0��(x+1).0��������ֹ����������һ������ǰ��С�ڣ���0.1����
*/

//ֻ����������
int find(int num)
{
	if (num == 0)
		return 0;
	//��ʼ�������ҽ���0��num
	int left = 0;
	int right = num;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		/*
			Ϊ��ֹ mid*mid ����������� if((long long) mid*mid == num) �ж�
				������ if (mid == num / mid)���������ַ���Ҫע�� mid Ϊ0 ��ʱ������
			��Ϊ mid ����������������һ���� mid ��ʱ��mid���ʵ�ʵ�С
			���� left + right ����3��ԭ�� midӦ��Ϊ1.5���������Ϊ1����С�ˡ�
			�������жϵ�ʱ��Ҫ���⴦����� mid*mid С�� num���� (mid + 1) * (mid + 1) > num��˵�� mid����Ҫ�ҵ�ֵ
		*/
		if ((long long)mid * mid == num)
			return mid;
		else if (((long long)mid * mid < num))
		{
			if ((long long)(mid + 1) * (mid + 1) > num)
				return mid;
			//�������ϣ�������
			left = mid + 1;
		}
		else
			right = mid - 1;
	}
	return 0;
}

//��ȷ��С�����nλ
double Sqrt(int num, int n)
{
	if (num == 0)
		return 0;
	//��������λ
	int interval = find(num);
	/*
		����С��λ��һλһλ���ң�����С������һλ�����ҵڶ�λ������ÿһλ���Ƕ����ġ�����������˼��һ����
		������С������һλ����� mid * mid < num �� (mid + 0.1) * (mid + 0.1) > num��˵�� mid ����Ҫ�ҵ�ֵ
		��ȷ��С�����nλ����ѭ�� n �Σ����Զ�ѭ��һ�Σ���ΪҪ�����һλ���������룩
	*/

	//interval ��ʱ������λ����ȷ��С��λ���� interval �� interval + 1 ֮��
	double mid = interval;
	double pos = 1;
	for (int i = 0; i < n; i++)
	{
		double left = mid;
		double right = mid + pos; //��С�����һλ���ҽ��� mid �� mid + 1֮�䣬����λ���ҽ��� mid �� mid + 0.1֮��
		pos /= 10;
		//ÿһ�� whileѭ����������˵���ҵ��˵�i+1λС������mid�͵��ھ�ȷ��С����� i+1λ��ֵ
		while (left <= right)
		{
			mid = left + (right - left) / 2;
			if (mid * mid == num)
				break;
			else if (mid * mid < num)
			{
				if ((mid + pos) * (mid + pos) > num)
					break;
				//��������
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
	// cout << fixed << setprecision(i) �ǵ�������ĸ�ʽ��setprecision(i) ���С�����iλ
	//��ѭ��һ�Σ�setprecision �ᴦ�����һλ����������
	int n = 3;
	cout << fixed << setprecision(n) << Sqrt(num, n + 1) << endl;

	return 0;
}