#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

/*
	����һ�����飬�������ó�������������ܷ���ڸ�����num,����ܣ��ҳ����п��е����,
	��ӡ�����������е��±ꡣ

	����ֶ��������
		���Ҫ�ҵ�x,y,z���±꣬���Ҹ��������������ظ���������ôֻ���÷���1
			���磬����Ϊ -4, -1, -1, -1, 2, 2, 3��num = 0��
			�� x ���±�Ϊ 1ʱ��ֵΪ-1������õڶ��ַ������±� 2,3,4,5 �п�ƥ������� (2,4),(2,5),(3,4),(3,5)
			��ƥ�����̫�ֻ࣬��˫��ѭ��������ȫ
	
		�������ֻ�ҵ�x,y,z��ֵ�����Ҵ��в����԰����ظ��� x,y,z����ô������������û���ظ��������������÷���2
		���磬����Ϊ -4, -1, -1, -1, 2, 2, 3��num = 0��
		�� x Ϊ��һ��-1ʱ��y �� z ���±� �ֱ�Ϊ(2,4)ʱ���ϣ���ôx,y,z��ֵ��Ϊ -1,-1,2,
		�� y�� z���±�Ϊ(2,5)ʱ��x,y,z��ֵΪ -1,-1,2����ȻҲ���ϣ����Ǻ�������ظ���

*/

/*
	˼·��
		1���������ֱ�Ϊx��y��z,�����������е����ȷŵ�unordered_map�У�ֵ��Ϊkey���±���Ϊvalue,
		�������Σ��ȱ�����ÿ��x+y���������ȥunordered_map�в����Ƿ���num-(x+y)������ʱ�临�Ӷ�ΪO(n^2)
		��ΪҪ��unordered_map�洢ÿ���������Կռ临�Ӷ�ΪO(n)

		2�������˫ָ�룬�Ȱ������ź��򣬵�һ���������xѡ�ã�Ȼ��������ָ��next��max�ֱ�ָ��x����һ��ֵ��
		��������һ��ֵ����������һ��ֵ����������ֵ����next��max��ӣ�����õ���ֵ��num-xС���Ǿ���
		next����ƶ��������next+max ��num-x�󣬾���max��ǰ�ƶ�
		û���õ�����Ŀռ䣬�����ʱ�临�Ӷ�ΪO(N*logN)�����ҵ�ʱ�临�Ӷ�ΪO(n^2)�����������ʱ��
		���Ӷ�ΪO(n^2)�����������ı�ԭ����������ݵ�˳��
*/

//����x,y,z���±�
vector<vector<int>> threeSumWay1(int arr[], int len, int num)
{
	vector<vector<int>> ret;
	//�Ȱ����������������ŵ�unordered_map��
	unordered_map<int, int> mapInt;
	for (int i = 0; i < len; i++)
	{
		mapInt[arr[i]] = i;
	}

	//����ѭ��������������x+y�����
	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			//��unordered_map��Ѱ���Ƿ��� complement
			int complement = num - arr[i] - arr[j];
			/*
				����ҵ��� complement ��Ҫ�ų����ֵ����arr[i]��arr[j]
				complement ֵ���±�϶���Ҫ���� i �� j�ģ���ͬʱj���Ǵ���i�ģ������� complement���±���� j�Ϳ�����
				��complement����j�Ƿ�ֹ�ظ����ݵĳ���,���һ��ܱ�֤����arr[i]��arr[j]
				���� 1	3	4	6	7  num = 8
				i = 0,j = 1��ʱ����ƥ�䵽4����ӡ 0 1 2
				i = 0,j = 2��ʱ����ƥ�䵽3���������ظ������ݣ�����Ҫ��ǰ��
			
			*/
			if (mapInt.find(complement) != mapInt.end() && mapInt[complement] > j)
			{
				cout << i << "  " << j << "  " << mapInt[complement] << endl;
				ret.push_back(vector<int>{i, j, mapInt[complement]});
			}
		}
	}
	return ret;
}

//ʹ��˫ָ�룬ֻ��� x,y,z��ֵ
vector<vector<int>> threeSumWay2(int arr[], int len, int num)
{
	vector<vector<int>> ret;
	//����������
	std::sort(arr, arr + len);

	for (int i = 0; i < len; i++)
	{
		//�����п������ظ���ֵ����ǰֵxȥ�أ���ֹ�ظ�����
		if (i > 0 && arr[i] == arr[i - 1])
			continue;
		int left = i + 1;			   //��ǰֵ����һ��ֵ���±�
		int right = len - 1;		   //�������һ��ֵ���±�
		int complement = num - arr[i]; //xȷ���ˣ�ȥ�������� y �� z
		while (left < right)
		{
			if (arr[left] + arr[right] > complement)
				right--;
			else if (arr[left] + arr[right] < complement)
				left++;
			else
			{
				cout << i << "  " << left << "  " << right << endl;
				ret.push_back(vector<int>{arr[i], arr[left], arr[right]});
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

	return ret;
}

int main()
{
	int arr[6] = {-1, 0, 1, 2, -1, -4};
	int num = 0;

	threeSumWay1(arr, 6, num);
	threeSumWay2(arr, 6, num);

	return 0;
}