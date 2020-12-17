#include <iostream>
#include <string>

using namespace std;

/*
	�����������˼�룺
		�տ�ʼѡ������β����Ԫ�� x����С��x��Ԫ�طŵ���ߣ�����x��Ԫ�طŵ������ұߣ����鱻��Ϊ�����֣�
		�ٷֱ�ѡ�����������β��Ԫ�أ���С�ڵķŵ���ߣ����ڵķŵ��ұߣ�����˼��
*/

int sort(int arr[], int L, int R)
{

	if (L >= R) //�ս�����
		return 0;

	//ÿ��ȡ���һ��ֵ��Ϊnumֵ
	int num = arr[R];
	int pl = L - 1; //ָ��С��numֵ��������һ��ֵ
	int pr = R + 1; //ָ�����numֵ����ĵ�һ��ֵ
	int curr = L;	//��ǰֵ���±꣬������ָ��

	//�������е�����С��num�ķŵ�С�����򣬴��ڵķŵ��������򣬵��ڷŵ��м�
	while (curr < pr)
	{
		if (arr[curr] < num)
		{
			swap(arr[curr++], arr[++pl]);
		}
		else if (arr[curr] == num)
		{
			curr++;
		}
		else
		{
			//curr�Ȳ���1�����жϻ��������������ֵ
			swap(arr[curr], arr[--pr]);
		}
	}
	//����ʱ�������L-pl��������С��num������pr-R�Ǵ���num��ֵ
	//�ټ�����֣�ֱ��ʣһ����
	sort(arr, L, pl);
	sort(arr, pr, R);

	return 0;
}

//����һ��д�����о�����д���������
int sort1(int arr[], int L, int R)
{

	if (L >= R) //�ս�����
		return 0;

	//ÿ��ȡ��һ��ֵ��Ϊnumֵ
	int num = arr[L];
	int pl = L;		  //ָ�����numֵ����ĵ�һ��ֵ
	int pr = R;		  //ָ�����numֵ��������һ��ֵ
	int curr = L + 1; //��ǰֵ���±꣬������ָ��

	//�������е�����С��num�ķŵ�С�����򣬴��ڵķŵ��������򣬵��ڷŵ��м�
	while (curr <= pr)
	{
		if (arr[curr] < num)
		{
			swap(arr[curr++], arr[pl++]);
		}
		else if (arr[curr] == num)
		{
			curr++;
		}
		else
		{
			//curr�Ȳ���1�����жϻ��������������ֵ
			swap(arr[curr], arr[pr--]);
		}
	}
	//����ʱ�������L��pl - 1��������С��num������pr + 1��R�Ǵ���num��ֵ
	//�ټ�����֣�ֱ��ʣһ����
	sort(arr, L, pl - 1);
	sort(arr, pr + 1, R);

	return 0;
}

int main()
{

	int array[10] = {5, 9, 4, 7, 2, 0, 6, 8, 1, 3};

	int len = 10;

	for (int i = 0; i < len; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	sort(array, 0, 9); //���������±�

	for (int i = 0; i < len; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}
