#include <string>
#include <iostream>
#include "../heap/heap.h"

using namespace std;
/*
	对于有限的数集，可以通过把所有观察值高低排序后找出正中间的一个作为中位数。
	如果观察值有偶数个，通常取最中间的两个数值的平均数作为中位数。
	注意，取平均数时，不能除以2，要乘以0.5
*/

/*
	问题：假设有一个吐数器，不断的吐出数，要收集这些数，随时给出已吐出数中的中位数
	思路：
		用堆结构，设一个大根堆和一个小根堆，第一个数放到大根堆，之后吐出的数，如果比
		大根堆的头结点小，就入大根堆，如果比大根堆的头结点大，就入小根堆。
		当大根堆中节点的数量，和小根堆节点的数量相差超过1的时候，比如大根堆中节点数为4，小根堆为2，
		那么就把大根堆的头节点弹出，放到小根堆，同理，当小根堆中节点的数量，
		和大根堆节点的数量相差超过1的时候，那么就把小根堆的头结点弹出，放到大根堆，
		这样，中位数，就在大根堆的头节点和小根堆的头节点之间
	分析：
		有点类似于排序，中间值放在大根堆和小根堆的头结点上，大根堆中放的是排完序以后前面部分的数
		小根堆放的是排完序以后后面部分的数
		但是这个排序没有严格的排完，因为现在只需要求出中位数，也就是完全排完序以后的中间值
		只需要把比当前中间值小的数放到大根堆中，比当前中间值大的数放到小根堆中，并不需要大根堆和小根堆
		中的节点再排序，只需要知道大根堆中最大的值和小根堆中最小的值，当然当两个树的数量要平衡，数量
		不一样时，说明中间值改变了，弹出头节点，再次找到中间值放到头节点

		为什么用堆结构，因为heapinsert操作，时间复杂度为O(logN)，每次吐出一个数，无论放到哪个树中，
		都会进行一次heapinsert操作，相当于插入一个节点进树，时间复杂度为O(logN)

*/

double GetMid(Heap &minHeap, Heap &maxHeap, int num)
{
	//先让这个值跟大根堆的头节点比较，大于的时候，放到小根堆，否则放大根堆
	//第一个数放到大根堆中
	if (num > maxHeap.getHeap() && maxHeap.getLength() > 0)
		//插入小根堆，小根堆的长度加一,插入以后，整理一下树，重新变成小根堆
		minHeap.heapInsert(num);
	else
		//插入大根堆，大根堆的长度加一,插入以后，整理一下树，重新变成大根堆
		maxHeap.heapInsert(num);

	/*
		再检查两颗树中的节点数，多了的就弹出头节点，放到另一个树中，
		弹出节点的树，先把头节点和最后一个节点交换，长度减一，执行heapify操作
		插入节点的树，直接执行heapinsert操作
	*/
	if (maxHeap.getLength() - minHeap.getLength() > 1)
	{
		//弹出大根堆的头结点，插入到小根堆中
		int n = maxHeap.removeHeap();
		minHeap.heapInsert(n);
	}

	if (minHeap.getLength() - maxHeap.getLength() > 1)
	{
		//弹出小根堆的头结点，插入到大根堆中
		int n = minHeap.removeHeap();
		maxHeap.heapInsert(n);
	}

	//取出中位数
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
	//上面的代码太繁琐，写一个简便的，但是这种方法没有上面的运行时间短

	/*
		//直接把值放到大根堆中
		maxHeap.heapInsert(num);
		//如果不平衡
		if (maxHeap.getLength() - minHeap.getLength() > 1)
			minHeap.heapInsert(maxHeap.removeHeap());

		上面的写法是不对的，因为求中位数的本质是，排完序以后再找中间的值
		所以大根堆中的每一个数，都要小于小根堆中的所有数
		而按照上面的方法，不能保证这一点，比如数据是 8,4,9
		插入8，大根堆：8，小根堆：无
		插入4，大根堆：4，小根堆：8
		插入9，大根堆，9, 4， 小根堆：8 	到这儿出错了，因为大根堆中的 9 并没有小于小根堆中的所有数
	*/
	//先将数据放入大根堆，让数据重新堆化
	maxHeap.heapInsert(num);

	/*
		再将数据取出来放到小根堆中
		比如上面的数据，插入9，大根堆：9, 4， 小根堆：8
		再将大根堆堆顶取出来放入小根堆中，大根堆：4， 小根堆：8, 9
	*/
	minHeap.heapInsert(maxHeap.removeHeap());

	/*
		维持数量平衡，如果小根堆的数量多于大根堆的数量，就让小根堆的堆顶进入大根堆
		这样就让大根堆的长度始终比小根堆中的长度多1个，或者相等
		上面的数据就变成了，大根堆：8,4 小根堆：9。
		这样就保证了大根堆中的每一个数，都小于小根堆中的所有数。并且可以很简便的得到中位数
	*/
	if (minHeap.getLength() > maxHeap.getLength())
		maxHeap.heapInsert(minHeap.removeHeap());

	//大根堆的长度始终比小根堆中的长度多1个，或者相等
	double mid = maxHeap.getLength() > minHeap.getLength() ? maxHeap.getHeap() : (maxHeap.getHeap() + minHeap.getHeap()) * 0.5;
	return mid;
}

int main()
{
	//先声明两个根堆，假设最多存放15个数
	int capacity = 15;
	Heap minHeap(HeapFlagMin, capacity);
	Heap maxHeap(HeapFlagMax, capacity);

	//吐数器
	int array[20] = {8, 4, 6, 0, 9, 5, 11, 15, 17, 14, 13, 19, 18, 16, 10, 12};
	int len = 20;

	double mid = 0;
	for (int i = 0; i < len; i++)
	{
		//每次吐出一个数,返回中位数
		//mid = GetMidEasy(minHeap, maxHeap, array[i]);
		mid = GetMid(minHeap, maxHeap, array[i]);
		cout << "中位数： " << mid << endl;
	}

	return 0;
}