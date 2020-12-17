#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>

using namespace std;

/*
    高位优先的字符串排序（MSD）需要注意的几个点：
    1，小型子数组   
        在demo3举的例子中发现，最后在切分子数组的时候，如果子数组中只有一个字符串（字符值为5的字符串），也会进入递归中，
        如果对数百万个不同的字符串进行排序，每个字符串会产生一个只含有它自己的子数组，每次都需要将count[]的258个元素
        初始化为0，并将频率转换为索引（需要循环R次），在使用unicode时（R = 65536）会更慢。
        优化：设定一个阈值M，当子数组中的字符串的数量，少于M的时候，
            让子数组进入插入排序中去进行最后几个几个字符的处理（直接调用库函数的字符串比较函数），这种方法虽然能缓解一些性能，
            但是也依赖库函数的比较函数的性能
    2，等值键
        对于含有大量等值键（比如子数组中含有大量完全相同的字符串）的子数组排序会很慢，如果相同的子字符串出现的太多，一直比阈值M高，
        那么就不会切换排序算法。因此，高位优先的字符串排序的最坏情况就是所有的键均相同，大量含有相同前缀的键也会产生这个问题。
    3，额外的空间，辅助数组aux是在递归函数sort()外申请的，所以不用担心，主要是count[]，每次递归的时候都需要创建
*/

/*
    总结：
        1，高位优先字符串排序是稳定排序
        2，高位优先字符串排序一般用于随机字符串排序，在有大量重复字符串时效率低下（此时需要三向字符串快速排序来救场）
        3，低位优先字符串排序适合定长较短字符串排序，相比于高位优先字符串排序，优势在于编写简单，否则MSD完全可以替代LSD
        4，时间复杂度为O(N + R)~O(wN + wR)，w为字符串平均长度。
            最好情况下，遍历一遍数据一轮就可以，
            最坏情况下，当所有的字符串都相等，处理一个键复杂度为(N + R)，
                如果字符串长度为W，需要处理W个键，总的时间复杂度为O(WN + WR)，性能和低位优先类似
        5，最坏情况下，空间复杂度为O(N + WR)，W为最大长度，O(N)为辅助数组aux占用的空间，O(WR)是W次递归中count[R+2]数组占用的空间

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

//字符串中的字符，最大的字符的assic码也不会超过256（因为一个字符只有一个字节，取值范围为 0 ~ 255，R应该比最大的值还大1，所以R是256）
//在这定义，是为了使用count[R + 1]，而不用再去 new count数组
const int R = 256;
//有数据表明，设为10 到 15最好
const int M = 10;

//切换到插入排序
void insertSort(vector<string> &a, int lo, int hi, int d)
{
    //a[lo]至a[hi]这个子数组中的所有字符串，前d个字符全都相等，那么从d到字符串结尾的那些剩下的字符，就在插入排序中处理了
    for (int i = lo + 1; i <= hi; i++)
    {
        //截取从d到结尾的字符串，直接调用库函数比较
        for (int j = i - 1; j >= lo && a[j].substr(d).compare(a[j + 1].substr(d)) > 0; j--)
        {
            swap(a[j], a[j + 1]);
        }
    }
}

//参数分别表示字符串容器，排序字符串起始位置，排序字符串结束位置，键的位数，辅助存储容器
void sort(vector<string> &a, int lo, int hi, int d, vector<string> &aux)
{ //以第d个字符为键将a[lo]至a[hi]排序

    //如果a[lo]至a[hi]这个子数组中含有的字符串的数量，少于M个，直接切换排序算法
    if (lo + M >= hi)
    {
        insertSort(a, lo, hi, d);
        return;
    }

    //根据第d个字符用键索引计数法，count[]数据申请R+2大小的内存
    int count[R + 2] = {0};

    //计算出现的频率，只排序下标lo到hi的字符串
    for (int i = lo; i <= hi; i++)
    {
        //让字符转成对应的ascii
        int index = charAt(a[i], d);
        //加1是让返回值转为非负整数，再加1是保持之前键索引计数法的用法
        count[index + 1 + 1]++;
    }

    //将频率转换为索引
    for (int r = 0; r < R + 1; r++)
    {
        count[r + 1] += count[r];
    }

    //将数据排好序放入辅助数组
    for (int i = lo; i <= hi; i++)
    {
        int index = charAt(a[i], d);
        //同样，加1是让返回值转为非负整数
        aux[count[index + 1]++] = a[i];
    }

    //回写
    for (int i = lo; i <= hi; i++)
    {
        a[i] = aux[i - lo]; //注意aux下标
    }

    //以从左到右的每个字符为键进行排序
    for (int r = 0; r < R; r++)
        sort(a, lo + count[r], lo + count[r + 1] - 1, d + 1, aux);
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
    vector<string> aux(N);
    //对 vecStr[]，从下标0到N-1，总共N个字符串进行排序，从左到右开始
    sort(vecStr, 0, N - 1, 0, aux);

    for (int i = 0; i < vecStr.size(); i++)
    {
        cout << vecStr[i] << endl;
    }
    return 0;
}