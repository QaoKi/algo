#include <string>
#include <stack>
#include <map>
using namespace std;

/*
	给定一个表达式，如 34+13*9+44-12/3，用计算机的计算方式求值
*/

/*
	计算机不会分配律，只能按顺序计算，直接按顺序算肯定是不对的
    用两个栈。其中一个保存操作数的栈，另一个是保存运算符的栈。
    从左向右遍历表达式，当遇到数字，直接压入操作数栈；
    当遇到运算符，就与运算符栈的栈顶元素进行比较。
        如果比运算符栈顶元素的优先级高，就将当前运算符压入栈；
        如果比运算符栈顶元素的优先级低或者相同，从运算符栈中取栈顶运算符，从操作数栈的栈顶取 2 个操作数，
            然后进行计算，再把计算完的结果压入操作数栈，继续比较。
*/

int calculate(string str)
{
    //用map计算优先级
    map<char, int> mapPriority;
    mapPriority['+'] = 1;
    mapPriority['-'] = 1;
    mapPriority['*'] = 1;
    mapPriority['/'] = 1;
}

int main()
{
    string str = "34+13*9+44-12/3";
    calculate(str);
    return 0;
}