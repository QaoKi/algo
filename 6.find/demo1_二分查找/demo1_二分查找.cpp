#include <iostream>
#include <string>

using namespace std;

/*
	���ֲ��ҵ�������
		1�������������
		2���ܹ�ͨ���������ʣ�����һ�㶼�����飬������Ҫ�������ڴ档������������֣����ӶȻ�����
		3��������̫�٣�����ֱ�ӱ����ҡ���������̫����Ϊ����Ҫ���������ڴ�洢���Կռ�����̫��

	ʱ�临�Ӷȣ�O(logn)
*/

bool find(int array[], int len, int num)
{
	int left = 0;
	int right = len - 1;
	while (left <= right) //ע����ֹ������ left <= right�������� left < right
	{
		//Ϊ��ֹ������������������������ķ���
		//�ٽ�һ��������λ����  int mid = left + ((right - left) >> 1 );
		int mid = left + (right - left) / 2;
		if (array[mid] == num)
			return true;
		else if (array[mid] < num)
			left = mid + 1; //ע�� left �� right ֵ�ĸ��£���Ȼ���ܻ�Ϳ���һ��������ѭ��
		else
			right = mid - 1;
	}
	return false;
}

int main()
{
	int len = 9;
	int arr[9] = {1, 4, 7, 10, 15, 23, 27, 33, 37};

	int num = 23;

	if (find(arr, num, len))
		cout << "find" << endl;
	else
		cout << "not find" << endl;

	return 0;
}