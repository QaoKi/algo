#include <iostream>
#include <string>
#include <time.h>
#include "../heap/heap.h"

using namespace std;

/*
	���������ݹ�����һ������ѣ��Ѷ�Ԫ��������������ֵ���Ƴ��Ѷ�Ԫ�أ����� heapify������
	����Ժ󣬶Ѷ�Ԫ��������ڶ���Ԫ�أ��ظ� k-1 �Σ���������ǰ k-1 ��������Ƴ����ѣ�
	��ô�Ѷ���Ԫ�ؾ��������е� k ���Ԫ��

	ʱ�临�Ӷȣ�O(nlogn)
*/

//�����ѣ�ʱ�临�Ӷ�O(n)
void buildHeap(int array[], int len)
{
	/*
		�����������飬��0λ�ÿ�ʼ����ÿ��Ԫ��ȥ�����ĸ��ڵ�Ƚϣ�
		ΪʲôҪ��0λ�ÿ�ʼ����Ϊ���統������������м�Ԫ�أ���ͷ��ʼ�Ļ�����ô���Ԫ��ǰ�������Ԫ�أ��Ѿ�����˴����
		ֻ��Ҫ������ڵ�ȥ�����ĸ��ڵ�Ƚ�
	*/

	for (int i = 0; i < len; i++)
	{
		int index = i;
		//ֻҪ����ڵ�����ĸ��ڵ�󣬾ͺ͸��ڵ㽻�������ᷢ��Խ�磬��Ϊ����index����0λ�ã�(0-1)/2 ����0
		while (array[index] > array[(index - 1) / 2])
		{
			swap(array[index], array[(index - 1) / 2]);
			index = (index - 1) / 2; //��ʱ����ڵ���±��Ѿ�����,���ԭ���ĸ��ڵ���±꣬������һ���µĸ��ڵ㣬�ٺ��µĸ��ڵ�Ƚ�
		}
	}
}

void heapify(int array[], int len, int index) //index ��ֵ�ı�Ľڵ���±�
{
	int left = 2 * index + 1; //���ӵ��±�
	while (left < len)
	{
		//���Һ��Ӳ�Խ�磬���ұ����ӵ�ֵ��ʱ��largest Ϊ�Һ����±꣬���� largest Ϊ�����±�
		int largest = array[left] < array[left + 1] && left + 1 < len ? left + 1 : left;
		//�����Һ����нϴ��ֵ������ı���ֵ�Ƚ�
		if (array[index] >= array[largest]) //�ı���ֵ���Ǳ����Һ��Ӵ󣬾Ͳ��ö�
			break;

		//���ı���ֵû�����Һ��Ӵ�
		swap(array[index], array[largest]);

		//�������Ժ󣬰��±껻������Ҫ�ٽ��űȽϽ������Ժ�����Һ��Ӵ�С
		index = largest;
		left = 2 * index + 1;
	}
}

int sort(int array[], int len, int k)
{
	//����һ�������
	buildHeap(array, len);
	//ִ�� k-1 ���Ƴ��Ѷ�Ԫ��ִ�� heapify����
	int length = len;
	for (int i = 0; i < k - 1; i++)
	{
		swap(array[0], array[--length]);
		heapify(array, length, 0);
	}

	return array[0];
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

	Heap minHeap(HeapFlagMin, k);
	for (int i = 0; i < len; i++)
	{
		minHeap.heapInsert(array[i]);
	}

	cout << "��" << k << "���Ԫ��ֵΪ��" << minHeap.getHeap() << endl;

	int num = sort(array, len, k);
	cout << "��" << k << "���Ԫ��ֵΪ��" << num << endl;

	return 0;
}
