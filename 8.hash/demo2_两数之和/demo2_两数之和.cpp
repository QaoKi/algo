#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/*
	����һ�����飬�������ó�������������ܷ���ڸ�����num,����ܣ��ҳ����п��е����,
	��ӡ�����������е��±�
*/

/*
	˼·��
		����1������ѭ��������ÿ�������ʱ�临�Ӷȷֱ�ΪO(n^2)

		����2�� 
			�������ֱ�Ϊx��y�������������е����ȷŵ�unordered_map�У�ֵ��Ϊkey���±���Ϊvalue,
			����һ��x��ÿ��ȥunordered_map�в鿴�Ƿ���num-x��ֵ
*/

//����ѭ��
void twoSum(int arr[], int len, int num)
{
	//�Ƚ���������ŵ� unordered_map �У�ֵΪkey,�±�Ϊvalue
	unordered_map<int, int> mapInt;
	for (int i = 0; i < len; i++)
	{
		mapInt[arr[i]] = i;
	}

	//ÿ��ָ��һ����ǰֵ x ��ȥ���Ƿ��� num-x ��ֵ�����Ҳ���Ϊ x ����
	for (int i = 0; i < len; i++)
	{
		/*
			ѭ��һ��ʼ�Ͱ�unordered_map��xɾ����������������Ŀ�ģ�
			һ������x������������ƥ�䣬��һ���Ƿ�ֹx��ǰ���Ѿ���������ֵ�����ظ�ƥ��
			��������������Ϊ 1	3  4  6  7��numΪ8��
			xΪ1ʱ��ƥ�䵽7����xΪ7ʱ�����1����unordered_map�У��ͻ�����ظ�ƥ��
		*/
		mapInt.erase(arr[i]); //�еİ汾��earse()ʱ��������Ҫ�ǵ�����
		if (mapInt.find(num - arr[i]) != mapInt.end())
		{
			cout << i << "  " << mapInt[num - arr[i]] << endl;
		}
	}
}

//һ��ѭ��
void twoSum1(int arr[], int len, int num)
{
	unordered_map<int, int> mapInt; //ֵ��key���±�Ϊvalue
	for (int i = 0; i < len; i++)
	{
		//ֱ��ȥunordered_map�����Ƿ���ֵ num-x����ʱ��ǰֵx ��û�з���unordered_map�У����Բ��������ƥ��
		//ֻ����������±��Ƿ����
		if (mapInt.find(num - arr[i]) != mapInt.end())
		{
			cout << i << "  " << mapInt[num - arr[i]] << endl;
		}

		//�ٰ�x���뵽unordered_map��
		mapInt[arr[i]] = i;
	}
}

bool isAnagram(string s, string t)
{
	unordered_map<char, int> mapS;
	for (auto ch : s)
	{
		mapS[ch]++;
	}

	for (auto ch : t)
	{
		mapS[ch]--;
	}

	for (auto it : mapS)
	{
		if (it.second > 0)
			return false;
	}
	return true;
}

int main()
{
	int arr[5] = {1, 2, 4, 6, 7};
	int num = 8;

	twoSum(arr, 5, num);
	twoSum1(arr, 5, num);

	if (isAnagram("anagram", "nagaam"))
		cout << "���" << endl;
	else
		cout << "�����" << endl;
	return 0;
}