#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

/*
	����һ������ n ������������ nums ��һ��Ŀ��ֵ target��
	�ж� nums ���Ƿ�����ĸ�Ԫ�� a��b��c �� d��
	ʹ��a + b + c + d��ֵ�� target ��ȣ��ҳ��������������Ҳ��ظ�����Ԫ�顣
	
	���в����԰����ظ�����Ԫ�顣
*/

//ʹ��˫ָ�룬���� a,b,c,d ��ֵ���������ظ��� a,b,c,d
vector<vector<int>> fourSum(int arr[], int len, int num)
{
	vector<vector<int>> ret;
	//����������
	std::sort(arr, arr + len);

	//��ȷ��һ��ֵ a
	for (int i = 0; i < len; i++)
	{
		//�����п������ظ���ֵ����ǰֵ a ȥ�أ���ֹ�ظ�����
		if (i > 0 && arr[i] == arr[i - 1])
			continue;

		//��ȷ��һ��ֵ b
		for (int j = i + 1; j < len; j++)
		{
			//�ٶ� b ȥ�أ�ע�������� j > i + 1��
			if (j > i + 1 && arr[j] == arr[j - 1])
				continue;

			int left = j + 1;						//��ǰֵ����һ��ֵ���±�
			int right = len - 1;					//�������һ��ֵ���±�
			int complement = num - arr[i] - arr[j]; //a �� b ȷ���ˣ�ȥ�������� c �� d

			while (left < right)
			{
				if (arr[left] + arr[right] > complement)
					right--;
				else if (arr[left] + arr[right] < complement)
					left++;
				else
				{
					ret.push_back(vector<int>{arr[i], arr[j], arr[left], arr[right]});
					//�����п������ظ���ֵ��ȥ���ظ�
					while (left < right && arr[left] == arr[left + 1])
						left++;
					while (left < right && arr[right] == arr[right - 1])
						right--;
					right--;
					left++;
				}
			}
		}
	}

	return ret;
}

int main()
{
	int arr[6] = {-1, 0, 1, 2, -1, -4};
	int num = 0;

	fourSum(arr, 6, num);

	return 0;
}