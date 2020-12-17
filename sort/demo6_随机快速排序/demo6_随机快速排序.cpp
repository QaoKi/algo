#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

/*
	���������������⣺
		������Ϊ  1,2,3,4,5,6  ���������״��ʱ�� ÿ��ѡ�����һ������Ϊnum����ô����num�������û����
		ÿ��һ��ֻ�ܸ㶨һ������ʱ�临�Ӷȱ�ΪO(n^2)
		������ţ�
		ÿ���������������ѡ��һ��ֵ�ŵ�����������Ϊnum�������漰�����ʣ�����������ʱ�临�Ӷȣ�O(n*logn)��

	��������ǹ�������õģ���Ϊʱ�临�Ӷȵĳ�����ȹ鲢������
*/

void rand_quick_sort(int arr[], int L, int R)
{
	if (L >= R)
		return;

	//���ݵ�����״���ǲ��ɿصģ����ǿ��Բ��÷��������ҹ̶�������״��
	//1.����������������ȡֵ��������״���޹�
	//2.��ϣ
	//�����������������ȡһ��ֵ�ŵ���������

	int index = rand() % (R - L + 1) + L;
	int num = arr[index];
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
		else if (arr[curr] > num)
		{
			swap(arr[curr], arr[--pr]); //curr�Ȳ���1�����жϻ��������������ֵ
		}
		else
		{
			curr++;
		}
	}

	//����ʱ�������L-pl��������С��num������pr-R�Ǵ���num��ֵ
	//�ټ�����֣�ֱ��ʣһ����
	rand_quick_sort(arr, L, pl);
	rand_quick_sort(arr, pr, R);
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

	srand(time(0));
	rand_quick_sort(array, 0, 9); //���������±�

	for (int i = 0; i < len; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	return 0;
}
