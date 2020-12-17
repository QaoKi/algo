#include <iostream>
#include <string>

using namespace std;

/*
	����Ŀ�� ����һ����N*M�����;���matrix��һ������num��matrix��ÿһ�к�ÿһ�ж����ź���ġ�
			ʵ��һ���������ж�num�Ƿ���matrix�С�
			���磺

				0	1	2	5
				2	3	4	7
				4	4	4	8
				5	7	7	9
			���numΪ7������true�����numΪ6������false��

	��Ҫ�� ʱ�临�Ӷ�ΪO(N+M)����ռ临�Ӷ�ΪO(1)
*/

/*
	˼·��
		���ַ�����һ���Ǵ����Ͻǿ�ʼ�ң�һ���Ǵ����½ǿ�ʼ��
		�����Ͻǿ�ʼ�ң�
			���Ͻǵ�һ����curr��num�Աȣ������num��˵��curr�����е����治����num����Ϊcurr��
			���У�curr����С�ģ���ʱcurr�����ƶ�һλ�����curr��numС��˵��curr�����е�ǰ�����������
			num����Ϊcurr�������У�curr�����ģ���ʱcurr�����ƶ���һֱ������л��ж����껹û�У���û��
		�����½ǿ�ʼ��ͬ��
*/

bool get(int arr[4][4], int num)
{
	bool bRet = false;
	int cH = 0;
	int cL = 3;		//currֵ��ָ�룬��ʼֵָ�����Ͻǵĵ�һ����
	while (cH <= 3 && cL >= 0)		//��curr��ָ�������
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
		cout << "��" << endl;
	}
	else
	{
		cout << "û��" << endl;
	}

	system("pause");
	return 0;
}