#include <iostream>
#include <string>

using namespace std;

/*
	���谴�����������������Ԥ��δ֪��ĳ�����Ͻ�������ת
	���磬���� [0,1,2,4,5,6,7] ���ܱ�Ϊ [4,5,6,7,0,1,2]
	����һ��������Ŀ��ֵ����������д������Ŀ��ֵ���򷵻��������������򷵻�-1��
	���������в������ظ���Ԫ�ء�ʱ�临�Ӷ�Ҫ��O(logn)��
*/

/*
	ʱ�临�Ӷ�Ϊ O(logn)�ķ���
	int mid = left + (right - left) / 2;
	���һ���±���м�ֵ mid������ֳ������֣�[left, mid] �� [mid + 1, right]
	�������ֿ϶���һ����������ģ���һ���ֿ���������ģ�Ҳ������Ȼ��һ��ѭ����������
	���� [4,5,6,7,8,9,0,1,2]��mid = 7,
	�ֳ� [4,5,6,7,8] �� [9,0,1,2]��ǰ�벿��������ģ���벿��������һ��ѭ����������
	�ж��������֣��Ĳ���������ģ����ж� num �Ƿ�������Ĳ����У�
	�����������Ĳ��֣��ظ�����Ĳ��裬�������ѭ����������
*/
int findOlogN(int array[], int len, int num)
{

	int left = 0;
	int right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (array[mid] == num)
			return mid;

		//���ǰ�벿���������
		if (array[left] <= array[mid])
		{
			//num�Ƿ���ǰ�벿����
			if (array[left] <= num && num < array[mid])
				//��ǰ�벿����
				right = mid - 1;
			else
				//����ǰ�벿�֣�����ȥ��ֺ�벿��
				left = mid + 1;
		}
		else
		{
			//ǰ�벿�ֲ�������ģ���벿�ֿ϶��������
			//num�Ƿ��ں�벿����
			if (array[mid] < num && num <= array[right])
				//�ں�벿����
				left = mid + 1;
			else
				//���ں�벿�֣�����ȥ���ǰ�벿��
				right = mid - 1;
		}
	}

	return -1;
}

int main()
{
	int len = 9;
	int arr[9] = {4, 5, 6, 7, 8, 9, 0, 1, 2};
	int num = 1;

	cout << "ֵ " << num << " ���±�Ϊ�� " << findOlogN(arr, len, num) << endl;

	return 0;
}