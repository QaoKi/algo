#include <iostream>
#include <string>

using namespace std;

/*
	�鲢����˼�룺
	���ε�˼��
*/

/*
	1.�ںϲ��Ĺ����У���� arr[L��mid]�� arr[mid+1��R]֮����ֵ��ͬ��Ԫ�أ��Ȱ� arr[L��mid�е�Ԫ�ط��� help ���顣
		�����ͱ�֤��ֵ��ͬ��Ԫ�أ��ںϲ�ǰ����Ⱥ�˳�򲻱䡣���ԣ��鲢������һ���ȶ��������㷨��
	2.ʱ�临�Ӷȣ�������������������������ƽ�������ʱ�临�Ӷȶ��� O(nlogn)
	3.ÿ�κϲ���������Ҫ���������ڴ�ռ䣬���ںϲ����֮����ʱ���ٵ��ڴ�ռ�ͱ��ͷŵ��ˡ�
		������ʱ�̣�CPU ֻ����һ��������ִ�У�Ҳ��ֻ����һ����ʱ���ڴ�ռ���ʹ�á�
		��ʱ�ڴ�ռ����Ҳ���ᳬ�� n �����ݵĴ�С�����Կռ临�Ӷ��� O(n)��
*/
void merge(int arr[], int L, int mid, int R)
{
	//L��R������arr�ĵ�һ��ֵ�±�����һ��ֵ�±�
	int pl = L;		  //ָ��ָ���������ĵ�һ��Ԫ��
	int pr = mid + 1; //ָ��ָ���ұ�����ĵ�һ��Ԫ��
	int index = 0;	  //���� help ���±�

	int *help = new int[R - L + 1]; //�������飬���������������������Ժ����
	while (pl <= mid && pr <= R)	//������ָ�붼�ڸ��Ե������ڣ��Ƚ��������飬��С�������η���help��
	{
		//��plָ���ֵ����prָ���ֵ������prָ���ֵ�����򷵻�plָ���ֵ
		help[index++] = arr[pl] <= arr[pr] ? arr[pl++] : arr[pr++];
	}

	//��������û�д�����������ηŵ�help��
	while (pl <= mid)
	{
		help[index++] = arr[pl++];
	}

	while (pr <= R)
	{
		help[index++] = arr[pr++];
	}

	//������ԭ�������飬����Ĵ���Ҫע��
	for (int i = 0; i < index; i++)
	{
		arr[L + i] = help[i];
	}
	delete[] help;
}
//��������ĵ�һ��ֵ���±�����һ��ֵ���±�
void sort(int arr[], int L, int R)
{
	//��ֹ����
	if (L >= R)
		return;
	//���м�
	int mid = (L + R) / 2;

	//�������Ϊ�����֣�һ����Ϊ L��mid��һ����Ϊ mid+1��R
	//�ٽ��Ų�֣�ֱ����ֵ�ÿһ����ֻʣһ����������L=R��ʱ��ֹͣ
	sort(arr, L, mid);
	sort(arr, mid + 1, R);

	//��ÿһ���Ӳ��֣���������С�ϲ�,һֱ�����ϲ����ܵ�
	merge(arr, L, mid, R);
}

int main()
{
	int array[10] = {8, 4, 6, 7, 2, 1, 3, 0, 9, 5};

	int len = 10;

	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	sort(array, 0, 9);

	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	return 0;
}
