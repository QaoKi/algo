#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>

using namespace std;

/*
    采用快递排序的思想对字符串排序。
    可以采用随机快排，随机在数组中选一个字符串，和数组尾部的字符串互换，打乱数据，可以预防数据已经有序或接近有序的最坏情况
    思路：和高位优先排序算法思想基本一样，以第d个字符对字符串排序，排序之后切分出子数组递归排序，但是它解决了高位优先排序的
        几大问题，不需要额外的空间，对于存在大量相同前缀的字符串数组，它也能很好得处理
*/

/*
    总结：
        1，三向字符串快速排序是不稳定排序
        2，原地排序
        3，三向字符串快速排序适合大量重复键的字符排序
        4，时间复杂度：O(NlogN)
        5，空间复杂度 0(W+logN) ??? 这个不懂
*/

//让字符转成对应的ascii，成为索引编号，若超出字符串长度返回-1
int charAt(string s, int index)
{
    if (index < s.length())
        //直接让char转成int就是对应的ascii
        return s[index];
    else
        return -1;
}

//参数分别表示字符串容器，排序字符串起始位置，排序字符串结束位置，键的位数
void sort(vector<string> &a, int lo, int hi, int d)
{
    if (lo >= hi) //终止条件
        return;
    //取子数组最后一个字符串作为基准
    int num = charAt(a[hi], d);
    int pl = lo - 1; //指向小于num值区域的最后一个值
    int pr = hi + 1; //指向大于num值区域的第一个值
    int curr = lo;   //当前值的下标，遍历的指针

    while (curr < pr)
    {
        int t = charAt(a[curr], d);
        if (t < num) //小于
            swap(a[++pl], a[curr++]);
        else if (t > num)
            //curr先不加1，再判断换过来的这个数的值
            swap(a[curr], a[--pr]);
        else
            curr++;
    }

    //lo到pl，是小于num值区域
    sort(a, lo, pl, d);
    if (num >= 0)
        //pl+1 到 pr-1是等于num值区域
        sort(a, pl + 1, pr - 1, d + 1);
    //pr到hi，是大于num值区域
    sort(a, pr, hi, d);
}

int main()
{
    vector<string> vecStr;
    vecStr.push_back("she");
    vecStr.push_back("sells");
    vecStr.push_back("seashells");
    vecStr.push_back("by");
    vecStr.push_back("the");
    vecStr.push_back("sea");
    vecStr.push_back("shore");
    vecStr.push_back("the");
    vecStr.push_back("shells");
    vecStr.push_back("she");
    vecStr.push_back("sells");
    vecStr.push_back("are");
    vecStr.push_back("surely");
    vecStr.push_back("seashells");

    int N = vecStr.size();
    //对 vecStr[]，从下标0到N-1，总共N个字符串进行排序，从左到右开始
    sort(vecStr, 0, N - 1, 0);

    for (int i = 0; i < vecStr.size(); i++)
    {
        cout << vecStr[i] << endl;
    }
    return 0;
}