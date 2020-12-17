#include <string>
#include <iostream>
#include "../heap/heap.h"

using namespace std;
/*
	�������޵�����������ͨ�������й۲�ֵ�ߵ�������ҳ����м��һ����Ϊ��λ����
	����۲�ֵ��ż������ͨ��ȡ���м��������ֵ��ƽ������Ϊ��λ����
	ע�⣬ȡƽ����ʱ�����ܳ���2��Ҫ����0.5
*/

/*
	���⣺������һ�������������ϵ��³�����Ҫ�ռ���Щ������ʱ�������³����е���λ��
	˼·��
		�öѽṹ����һ������Ѻ�һ��С���ѣ���һ�����ŵ�����ѣ�֮���³������������
		����ѵ�ͷ���С���������ѣ�����ȴ���ѵ�ͷ���󣬾���С���ѡ�
		��������нڵ����������С���ѽڵ����������1��ʱ�򣬱��������нڵ���Ϊ4��С����Ϊ2��
		��ô�ͰѴ���ѵ�ͷ�ڵ㵯�����ŵ�С���ѣ�ͬ����С�����нڵ��������
		�ʹ���ѽڵ����������1��ʱ����ô�Ͱ�С���ѵ�ͷ��㵯�����ŵ�����ѣ�
		��������λ�������ڴ���ѵ�ͷ�ڵ��С���ѵ�ͷ�ڵ�֮��
	������
		�е������������м�ֵ���ڴ���Ѻ�С���ѵ�ͷ����ϣ�������зŵ����������Ժ�ǰ�沿�ֵ���
		С���ѷŵ����������Ժ���沿�ֵ���
		�����������û���ϸ�����꣬��Ϊ����ֻ��Ҫ�����λ����Ҳ������ȫ�������Ժ���м�ֵ
		ֻ��Ҫ�ѱȵ�ǰ�м�ֵС�����ŵ�������У��ȵ�ǰ�м�ֵ������ŵ�С�����У�������Ҫ����Ѻ�С����
		�еĽڵ�������ֻ��Ҫ֪�������������ֵ��С��������С��ֵ����Ȼ��������������Ҫƽ�⣬����
		��һ��ʱ��˵���м�ֵ�ı��ˣ�����ͷ�ڵ㣬�ٴ��ҵ��м�ֵ�ŵ�ͷ�ڵ�

		Ϊʲô�öѽṹ����Ϊheapinsert������ʱ�临�Ӷ�ΪO(logN)��ÿ���³�һ���������۷ŵ��ĸ����У�
		�������һ��heapinsert�������൱�ڲ���һ���ڵ������ʱ�临�Ӷ�ΪO(logN)

*/

double GetMid(Heap &minHeap, Heap &maxHeap, int num)
{
	//�������ֵ������ѵ�ͷ�ڵ�Ƚϣ����ڵ�ʱ�򣬷ŵ�С���ѣ�����Ŵ����
	//��һ�����ŵ��������
	if (num > maxHeap.getHeap() && maxHeap.getLength() > 0)
		//����С���ѣ�С���ѵĳ��ȼ�һ,�����Ժ�����һ���������±��С����
		minHeap.heapInsert(num);
	else
		//�������ѣ�����ѵĳ��ȼ�һ,�����Ժ�����һ���������±�ɴ����
		maxHeap.heapInsert(num);

	/*
		�ټ���������еĽڵ��������˵ľ͵���ͷ�ڵ㣬�ŵ���һ�����У�
		�����ڵ�������Ȱ�ͷ�ڵ�����һ���ڵ㽻�������ȼ�һ��ִ��heapify����
		����ڵ������ֱ��ִ��heapinsert����
	*/
	if (maxHeap.getLength() - minHeap.getLength() > 1)
	{
		//��������ѵ�ͷ��㣬���뵽С������
		int n = maxHeap.removeHeap();
		minHeap.heapInsert(n);
	}

	if (minHeap.getLength() - maxHeap.getLength() > 1)
	{
		//����С���ѵ�ͷ��㣬���뵽�������
		int n = minHeap.removeHeap();
		maxHeap.heapInsert(n);
	}

	//ȡ����λ��
	double mid = 0;
	if (maxHeap.getLength() > minHeap.getLength())
	{
		mid = maxHeap.getHeap();
	}
	else if (maxHeap.getLength() < minHeap.getLength())
	{
		mid = minHeap.getHeap();
	}
	else
	{
		mid = (maxHeap.getHeap() + minHeap.getHeap()) * 0.5;
	}

	return mid;
}

double GetMidEasy(Heap &minHeap, Heap &maxHeap, int num)
{
	//����Ĵ���̫������дһ�����ģ��������ַ���û�����������ʱ���

	/*
		//ֱ�Ӱ�ֵ�ŵ��������
		maxHeap.heapInsert(num);
		//�����ƽ��
		if (maxHeap.getLength() - minHeap.getLength() > 1)
			minHeap.heapInsert(maxHeap.removeHeap());

		�����д���ǲ��Եģ���Ϊ����λ���ı����ǣ��������Ժ������м��ֵ
		���Դ�����е�ÿһ��������ҪС��С�����е�������
		����������ķ��������ܱ�֤��һ�㣬���������� 8,4,9
		����8������ѣ�8��С���ѣ���
		����4������ѣ�4��С���ѣ�8
		����9������ѣ�9, 4�� С���ѣ�8 	����������ˣ���Ϊ������е� 9 ��û��С��С�����е�������
	*/
	//�Ƚ����ݷ������ѣ����������¶ѻ�
	maxHeap.heapInsert(num);

	/*
		�ٽ�����ȡ�����ŵ�С������
		������������ݣ�����9������ѣ�9, 4�� С���ѣ�8
		�ٽ�����ѶѶ�ȡ��������С�����У�����ѣ�4�� С���ѣ�8, 9
	*/
	minHeap.heapInsert(maxHeap.removeHeap());

	/*
		ά������ƽ�⣬���С���ѵ��������ڴ���ѵ�����������С���ѵĶѶ���������
		�������ô���ѵĳ���ʼ�ձ�С�����еĳ��ȶ�1�����������
		��������ݾͱ���ˣ�����ѣ�8,4 С���ѣ�9��
		�����ͱ�֤�˴�����е�ÿһ��������С��С�����е������������ҿ��Ժܼ��ĵõ���λ��
	*/
	if (minHeap.getLength() > maxHeap.getLength())
		maxHeap.heapInsert(minHeap.removeHeap());

	//����ѵĳ���ʼ�ձ�С�����еĳ��ȶ�1�����������
	double mid = maxHeap.getLength() > minHeap.getLength() ? maxHeap.getHeap() : (maxHeap.getHeap() + minHeap.getHeap()) * 0.5;
	return mid;
}

int main()
{
	//�������������ѣ����������15����
	int capacity = 15;
	Heap minHeap(HeapFlagMin, capacity);
	Heap maxHeap(HeapFlagMax, capacity);

	//������
	int array[20] = {8, 4, 6, 0, 9, 5, 11, 15, 17, 14, 13, 19, 18, 16, 10, 12};
	int len = 20;

	double mid = 0;
	for (int i = 0; i < len; i++)
	{
		//ÿ���³�һ����,������λ��
		//mid = GetMidEasy(minHeap, maxHeap, array[i]);
		mid = GetMid(minHeap, maxHeap, array[i]);
		cout << "��λ���� " << mid << endl;
	}

	return 0;
}