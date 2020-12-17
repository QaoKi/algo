#include <iostream>
#include <string>
#include <time.h>

using namespace std;

/*
	O(n) ʱ�临�Ӷ��������������еĵ� K ��Ԫ�ء����磺4, 2, 5 , 12, 3, 1, 6 ����һ�����ݣ��� 3 ��Ԫ�ؾ���4

	˼·��
		ѡ����������һ��Ԫ�أ����±�n-1��Ϊnum���������е����ݽ�������С��num�ķŵ�num�����棬����num��
		�ŵ�num�����棬���һ�����򣬼����������Ժ�num���±�Ϊp����0~p-1Ϊ����num��ֵ���±꣬p+1~n-1ΪС��num��ֵ���±�
		���p = k-1,��ôֵnum����Ҫ���ֵ����� p>k-1��˵��Ҫ���ֵ��0~p-1�������У����p<k-1��˵��Ҫ���ֵ��
		p+1~n-1�������У��ٰѽ����ڵ������������
*/

int sort(int arr[], int L, int R, int K)
{
	if (L >= R)
		return arr[L];
	int index = rand() % (R - L + 1) + L;
	int num = arr[index];
	int pl = L - 1; //��������ĳ�ʼ�±�
	int pr = R + 1; //С������ĳ�ʼ�±�
	int curr = L;	//��ǰֵ���±�
	while (curr < pr)
	{
		if (arr[curr] > num)
		{
			swap(arr[curr++], arr[++pl]);
		}
		else if (arr[curr] == num)
		{
			curr++;
		}
		else
		{
			swap(arr[curr], arr[--pr]);
		}
	}

	/*
	����ʱ��L-pl�������Ǵ���num������pl+1 �ǵ��� num ��ֵ��num�Ǵ�������ȡ�ģ����Աش��ڣ���pr��R��С��num����
	С���� ��L,pl) �� (pr,R)�������ǲ���֤����ģ��б�֤���� num �ڣ�L,pl) �� (pr,R)֮�䣬
	num ���±��� pl+1��Ҳ����˵ num �������еĵ� pl+2 ���ֵ
	*/
	if (pl + 2 == K)
	{
		return arr[pl + 1];
	}
	else if (pl + 2 > K)
	{
		return sort(arr, L, pl, K);
	}
	else
	{
		/*
		ע��ĵ㣺
			1����2������Ҫ���� pl+2,�� num ���ֵ��������Ժ��ժ��ȥ�ˣ����ٲ�����һ������
				������� pl+1��num������һ�����򣬻������ѭ���������
				��������Ϊ[1,1],K=2����һ�ε���Ϊ sort(arr,0,1,2),
				��������£�plΪ -1��������whileѭ���Ժ�plֵû�䣬����-1��
				��ô�������pl+1���������þ�Ϊ sort(arr,-1 + 1,1,2),������ѭ��
			2����4��������Ȼ����K��֮ǰ����Ǵ��� K - (pl + 1)����Ϊ����ǰ pl+1������Ѿ�ȷ����
				������ʵ���ã���Ϊ�����±���бȽϵ�
		*/
		return sort(arr, pl + 2, R, K);
	}
}

int main()
{

	// int array[9] = {3, 2, 3, 1, 2, 4, 5, 5, 6};

	// int len = 9;

	// int k = 4;
	int array[2] = {-1, -1};

	int len = 2;

	int k = 2;

	for (int i = 0; i < len; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	srand(time(0));
	int num = sort(array, 0, len - 1, k); //���������±��Ҫ��ĵ� K ��Ԫ��

	cout << "��" << k << "���Ԫ��ֵΪ��" << num << endl;

	return 0;
}
