#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>

using namespace std;

/*
    高位优先的字符串排序（MSD）
    不需要字符串的长度相同即可对字符串数组进行排序，从左向右对每个字符排序

    思路：MSD的核心思想是分治算法，即将大问题分为小问题来解决，其思想与快速排序类似，先对最高位的字符进行排序，
        将排序后的字符串进行分组——最高位相同的在一组；再对同一组的进行MSD排序，不过此时以第二位字符进行排序，直到排完最低位，算法结束。

    实现：一个需要注意的问题是怎么处理结尾字符的问题，因为MSD运行字符的长度不同，那么总会有字符串先结束。合理的做法是，将所有字符
        都已经检查过的字符串所在的子数组排在所有子数组的前面，比如字符串 abc和abcd，在结果集中，abc要放在abcd前面。

        设计一个charAt(string str, int d)函数来返回字符串在按照第d个字符进行排序时的count[]的索引，当字符串不含有第d个字符时返回-1，
        之所以返回-1，是要让不含有第d个字符的字符串，放到这个一组子字符串的最前面（最小的acsii码是0，让它比0还小，就放到了最前面）。
        否则返回第d个字符对应的ascii码，因为数组的下标不能为负数，所以我们将charAt的返回值加1，得到一个非负的int值并用它作为count[]的索引。
        这样我们就可以把字符串结尾的情况同其余情况一起处理，同时保证了已结尾的字符串会在未结尾的字符串之前！
        charAt()的返回值，范围在 [-1, R-1]。再加上1，就是[0, R]，一共 R+1 种可能。最大的值是R，而此时的基数，应该变为 R+1（基数应该比最大的值还大1），
        而我们申请count[]数组的大小时，会申请比基数还大1的数量，所以，应该申请 R + 2。基数变为R+1（在键索引计数法的实现中，R都变成R+1）。
        在统计频率的时候，调用count[charAt() + 2]++，count[0]仍然不被使用（还是为了让第三步好理解）。
*/

/*
    对于基于R个字符的字母表的N个以长为W的字符串为键的元素，
    时间复杂度为 O(WN)，空间复杂度为O(R + N)。R为字符串中字符种类的数量，如果全为字母，就是26，如果有别的字符，为256。
    低位优先的字符串排序是稳定的排序
*/

//让字符转成对应的ascii，成为索引编号，若超出字符串长度返回-1
int charAt(string s, int d)
{
    if (d < s.length())
        //直接让char转成int就是对应的ascii
        return s[d];
    else
        return -1;
}

//字符串中的字符，最大的字符的assic码也不会超过256（因为一个字符只有一个字节，取值范围为 0 ~ 255，R应该比最大的值还大1，所以R是256）
//在这定义，是为了使用count[R + 1]，而不用再去 new count数组
const int R = 256;

//参数分别表示字符串容器，排序字符串起始位置，排序字符串结束位置，键的位数，辅助存储容器
void sort(vector<string> &a, int lo, int hi, int d, vector<string> &aux)
{ //以第d个字符为键将a[lo]至a[hi]排序

    if (lo > hi) //注意结束标志，是 lo > hi，当 lo等于 hi也需要处理
        return;

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
    /*
        这一步有点难以理解，
        可以看下 https://www.cnblogs.com/Unicron/p/11531111.html 这个里面画的执行过程，或者算法第四版的执行过程。
        拿一个数据举例，取R为6
        假如当执行完第一步，统计完频率后，
            count[0] = 0，count[1] = 0，count[2] = 3，count[3] = 0，count[4] = 4，count[5] = 6，count[6] = 1
            表示没有字符值为0的字符串（count[0]没有使用，count[1]存放的是字符值为0的字符串，这个字符值，指的是 charAt(a[i][d]) + 1），
            字符值1的字符串有3个，字符值为2的字符串有0个，值为3的有4个，值为4的有6个，值为5的有1个
        执行完第二步，将频率转换为索引后，
            count[0] = 0, count[1] = 0, count[2] = 3, count[3] = 3, count[4] = 7, count[5] = 13, count[6] = 14
            count[i]表示当遇到下一个字符值为i的字符串应放到结果集数组 aux[count[i]] 中，
            当遇到下一个字符值为0和值为1的字符串，放到结果集的aux[0]中，
            当遇到下一个字符值为2的字符串，放到结果集的aux[3]中，
            。。。
            当遇到下一个字符值为6的字符串，放到结果集的aux[14]中（不过没有字符值为6的字符串）
        当执行完第三步，将数据写入到了辅助数组中后，count中的值为
            count[0] = 0, count[1] = 3, count[2] = 3, count[3] = 7, count[4] = 13, count[5] = 14, count[6] = 14

    重点：
        首字母排好序，接着要把首字母相同（也就是字符值相同）的字符串从大数组中切分出来形成子数组，进行单独的sort排序。
        那么如何把字符值相同的字符串切分出来？
            首先字符值相同的字符串，在结果集数组中肯定是放到一起的。那么如何求出字符值为i的字符串，在结果集数组中，下标从哪到哪？
                我们再来看执行完第三步以后的count[]，count[1] = 3，表示当遇到下一个字符值为1的字符串，放到aux[3]中，因为数据已经
                都放完了，那么可以得出结论，字符值为1的字符串，都放入结果集以后，最后一个字符串的下标为2，所以，2就是结束下标，
                count[0] = 0，说明字符值为0的字符串，都放入结果集以后，最后一个字符串的下标为-1，
                也就是说，字符值为1的字符串，是从 -1 + 1 = 0，也就是count[0]作为下标开始的（字符值为1的字符串，紧挨着值为0的字符串），
                所以，字符值为1的字符串，在结果集数组中，开始下标为count[0]，结束下标为count[1] - 1。
            同理，字符值为2的字符串，都放入结果集以后，最后一个字符串的下标为count[2] - 1，第一个字符串的下标为count[1] = 3，
            (3,2)，说明不存在字符值为2的字符串。
            所以，推出公式，字符值为 i的字符串，在结果集中，开始下标为 count[i - 1]，结束下标为 count[i] - 1;

            遍历每个字符值（charAt(a[i][d])取值范围是 0到R-1，再加1，所以字符值的取值范围是1到R），将字符值相同的切分出来进入递归，
            for (int r = 1; r <= R; r++)
                sort(a, lo + count[r - 1], lo + count[r] - 1, d + 1, aux);

            R等于6，for循环执行如下
            r = 1 时，sort(a, 0 + 0, 0 + 2, 1, aux);  //字符值相同的有3个，在a[]中，从下标0到下标2
            r = 2 时，sort(a, 0 + 3, 0 + 2, 1, aux);  //直接return
            r = 3 时，sort(a, 0 + 3, 0 + 6, 1, aux);  //字符值相同的有4个，在a[]中，从下标3到下标6
            r = 4 时，sort(a, 0 + 7, 0 + 12, 1, aux);  //字符值相同的有6个，在a[]中，从下标7到下标12  
            r = 5 时，sort(a, 0 + 13, 0 + 13, 1, aux);  //字符值相同的有1个，在a[]中，下标13 
            r = 6 时，sort(a, 0 + 14, 0 + 13, 1, aux);  //直接return
            也可以写成
            for (int r = 0; r < R; r++)
                sort(a, lo + count[r], lo + count[r + 1] - 1, d + 1, aux);
    */
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