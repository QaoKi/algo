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
/*
	��������1�����ҵ�һ��ֵ���ڸ���ֵ��Ԫ��
	��������2���������һ��ֵ���ڸ���ֵ��Ԫ��
	��������3�����ҵ�һ�����ڵ��ڸ���ֵ��Ԫ��
	��������4���������һ��С�ڵ��ڸ���ֵ��Ԫ��
*/

//���ҵ�һ��ֵ���ڸ���ֵ��Ԫ�أ������±�
int find1(int array[], int len, int num)
{
	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (array[mid] > num)
			right = mid - 1;
		else if (array[mid] < num)
			left = mid + 1;
		else
		{
			//ע��߽紦���ֵ���� left������ 0
			if (mid == left || array[mid - 1] != num)
				return mid;
			else
				right = mid - 1;
		}
	}
	return -1;
}

//���ҵ�һ��ֵ���ڸ���ֵ��Ԫ�أ������±ꡣ����find1�ļ��д��

int find1Easy(int array[], int len, int num)
{
	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		//�ҵ�����ȵ�ֵ��Ҳ��ͣ����ȥ�ж��Ƿ��ǵ�һ����ȵ�Ԫ�أ�������С��Χ��ǰ����
		if (array[mid] >= num)
			right = mid - 1;
		else
			left = mid + 1;
	}
	/*
		���ַ����£���������Ҫ�ҵ�Ԫ���±�Ϊ x ���� mid ���� x ʱ��Ҳ��ͣ��������right = x - 1��
		���ҵ� x �Ժ���Ҳ����ִ������ if (array[mid] >= num)��
		right��֮���ѭ���оͲ�����ˣ�Ҳ����˵������right����һ��Ԫ�ؾ�������Ҫ�ҵ�ֵ��
		�� while ѭ��������left�͵��� right + 1��Ҳ��������Ҫ�ҵ� x

		���ַ�������ʱ��Ҫ��find1������Ϊÿ���ҵ���ȵ�ֵ����ȥ�ж��Ƿ��� x������һֱ������ left > right
	*/
	return left < len && array[left] == num ? left : -1;
}

//�������һ��ֵ���ڸ���ֵ��Ԫ�أ������±�
int find2(int array[], int len, int num)
{
	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (array[mid] > num)
			right = mid - 1;
		else if (array[mid] < num)
			left = mid + 1;
		else
		{
			//ע��߽紦���ֵ���� right�� ���� len - 1
			if (mid == right || array[mid + 1] != num)
				return mid;
			else
				left = mid + 1;
		}
	}
	return -1;
}

//�������һ��ֵ���ڸ���ֵ��Ԫ�أ������±ꡣ���� find2�ļ��д��
int find2Easy(int array[], int len, int num)
{
	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (array[mid] <= num)
			left = mid + 1;
		else
			right = mid - 1;
	}

	//��find1Easyͬ��while ѭ�������Ժ�right ����Ҫ�ҵ� x��left���� x + 1
	return right < len && array[right] == num ? right : -1;
}

//���ҵ�һ�����ڵ��ڸ���ֵ��Ԫ�أ������±�
int find3(int array[], int len, int num)
{
	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (array[mid] < num)
			left = mid + 1;
		else
		{
			//ע��߽紦���ֵ���� left������ 0
			if (mid == left || array[mid - 1] < num)
				return mid;
			else
				right = mid - 1;
		}
	}
	return -1;
}

//���ҵ�һ�����ڵ��ڸ���ֵ��Ԫ�أ������±ꡣfind3�ļ��д��
int find3Easy(int array[], int len, int num)
{
	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;

		if (array[mid] >= num)
			right = mid - 1;
		else
			left = mid + 1;
	}
	//��find1ͬһԭ��
	return left < len && array[left] >= num ? left : -1;
}

//�������һ��С�ڵ��ڸ���ֵ��Ԫ�أ������±�
int find4(int array[], int len, int num)
{
	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (array[mid] > num)
			right = mid - 1;
		else
		{
			//ע��߽紦���ֵ���� right�� ���� len - 1
			if (mid == right || array[mid - 1] > num)
				return mid;
			else
				left = mid + 1;
		}
	}
	return -1;
}

//�������һ��С�ڵ��ڸ���ֵ��Ԫ�أ������±ꡣfind4�ļ��д��
int find4Easy(int array[], int len, int num)
{
	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (array[mid] <= num)
			left = mid + 1;
		else
			right = mid - 1;
	}

	//��find1Easyͬ��while ѭ�������Ժ�right ����Ҫ�ҵ� x��left���� x + 1
	return right < len && array[right] == num ? right : -1;
}

int main()
{
	int len = 11;
	int arr[11] = {1, 4, 7, 10, 15, 23, 23, 23, 27, 33, 37};

	int num = 23;
	cout << "��һ��ֵ���� " << num << " ��Ԫ���±�Ϊ " << find1(arr, len, num) << endl;
	cout << "��һ��ֵ���� " << num << " ��Ԫ���±�Ϊ " << find1Easy(arr, len, num) << endl;
	cout << "���һ��ֵ���� " << num << " ��Ԫ���±�Ϊ " << find2(arr, len, num) << endl;
	cout << "���һ��ֵ���� " << num << " ��Ԫ���±�Ϊ " << find2Easy(arr, len, num) << endl;
	cout << "��һ�����ڵ��� " << num << " ��Ԫ���±�Ϊ " << find3(arr, len, num) << endl;
	cout << "��һ�����ڵ��� " << num << " ��Ԫ���±�Ϊ " << find3Easy(arr, len, num) << endl;
	cout << "���һ��С�ڵ��� " << num << " ��Ԫ���±�Ϊ " << find4(arr, len, num) << endl;
	cout << "���һ��С�ڵ��� " << num << " ��Ԫ���±�Ϊ " << find4Easy(arr, len, num) << endl;
	return 0;
}