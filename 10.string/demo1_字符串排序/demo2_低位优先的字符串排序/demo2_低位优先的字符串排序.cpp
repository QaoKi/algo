#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>

using namespace std;

/*
    基于键索引记数法来实现

    低位优先的字符串排序（LSD）能够稳定地将 定长 字符串进行排序
    生活中很多情况需要将定长字符串排序，比如车牌号、身份证号、卡号、学号......
    通过键索引记数法来实现---- 从右至左 以每个位置的字符作为键，用键索引记数法将字符串排序W遍（W为字符串的长度）

    总结：其实就是基数排序。
        这个思路，和极客11上订单金额和下单时间排序原理类似。
        题目是：按照订单金额排序，订单金额相同的按照下单时间排序。对所有订单的处理，订单金额是第一优先级，下单时间是第二优先级。
            如果先对所有订单按照订单金额排序，然后对订单金额相同的小区间再单独排序，代码实现很麻烦。解决方法是，使用稳定的
            排序算法，先按照下单时间排序，再按照订单金额排序。
            而对于两个字符串的比较，如果高位字符已经比较出大小，那么低位就没有比较的必要了，所以，高位字符是第一优先级，
            低位字符是第二优先级，用稳定的排序算法，先对低优先级的排序，再对高优先级的排序。
*/

/*
    对于基于R个字符的字母表的N个以长为W的字符串为键的元素，
    时间复杂度为 O(WN + WR)，空间复杂度为O(R + N)。R为基数，比最大的取值大1。如果全为字母，设取值为 0~25，那么R就是26，如果有别的字符，可以设为256。
    低位优先的字符串排序是稳定的排序
*/

//让字符转成对应的ascii，成为索引编号
int charAt(char ch)
{
    //直接让char转成int就是对应的ascii，如果只有字母的话，可以让a转为0，b转成1。。。
    return ch;
}

//基数R：字符串中的字符，最大的字符的assic码也不会超过256（因为一个字符只有一个字节，取值范围为 0 ~ 255，R应该比最大的值还大1，所以R是256）
//在这定义，是为了使用count[R + 1]，而不用再去 new count数组
const int R = 256;

//要排序的数据，长度都是相同的，vector中的字符串，长度都是相等的
void sort(vector<string> &a)
{
    if (a.empty())
        return;
    //多少个数据
    int N = a.size();

    //每个字符串的长度
    int W = a[0].length();

    //辅助数组，存放排好序后的数据，初始化内存为N个，使用vector，也省去了new操作
    vector<string> aux(N);

    //从右往左排序，从低位开始排序
    for (int d = W - 1; d >= 0; d--)
    {
        //根据第d个字符用键索引计数法

        //计算出现的频率
        int count[R + 1] = {0};
        for (int i = 0; i < N; i++)
        {
            //让字符转成对应的ascii
            int index = charAt(a[i][d]);
            count[index + 1]++;
        }

        //将频率转换为索引
        for (int r = 0; r < R; r++)
        {
            count[r + 1] += count[r];
        }

        //将数据排好序放入辅助数组
        for (int i = 0; i < N; i++)
        {
            int index = charAt(a[i][d]);
            aux[count[index]++] = a[i];
        }

        //回写
        for (int i = 0; i < N; i++)
        {
            a[i] = aux[i];
        }
    }
}

int main()
{
    vector<string> vecStr;
    vecStr.push_back("4PGC938");
    vecStr.push_back("2IYE230");
    vecStr.push_back("3CIO720");
    vecStr.push_back("1ICK750");
    vecStr.push_back("1OHV845");
    vecStr.push_back("4JZY524");
    vecStr.push_back("1ICK750");
    vecStr.push_back("3CIO720");
    vecStr.push_back("1OHV845");
    vecStr.push_back("1OHV845");
    vecStr.push_back("2RLA629");
    vecStr.push_back("2RLA629");
    vecStr.push_back("3ATW723");

    sort(vecStr);

    for (int i = 0; i < vecStr.size(); i++)
    {
        cout << vecStr[i] << endl;
    }
    return 0;
}