#include <string>
#include <map>
#include <stack>
using namespace std;

/*
	给定一个字符串，比如为"( ) { ( ) ( [ ] ) }"
	判断左右括号是否匹配正确
*/

/*
	题目本身比较简单，用栈实现，如果遇到左括号，就入栈，如果遇到右括号，
	把栈顶的元素和右括号进行匹配，如果匹配上，就弹出栈顶元素，继续运行，
	如果不成功，直接返回false
	但是怎么样对字符进行匹配，写出简洁的代码：用map
*/

bool IsSymmetry(string str)
{
    stack<char> stackChar;
    map<char, char> mapChar;
    //将括号的对应原则加入到map中
    mapChar['}'] = '{';
    mapChar[']'] = '[';
    mapChar[')'] = '(';

    for (int i = 0; i < str.length(); i++)
    {
        //如果是左括号，就入栈
        if (mapChar.find(str[i]) == mapChar.end())
            stackChar.push(str[i]);
        //如果是右括号，那么栈中必定有元素，并且栈顶的元素与右括号匹配
        else if (stackChar.empty() || stackChar.top() != mapChar[str[i]])
        {
            printf("no\n");
            return false;
        }
        else
            //这个字符匹配上了，弹出栈顶元素
            stackChar.pop();
    }

    //最后要判断栈中是否有数据，如果有数据，则错误
    if (!stackChar.empty())
    {
        printf("no\n");
        return false;
    }

    printf("yes\n");
    return true;
}

int main()
{
    string str = "(){()([])}";
    IsSymmetry(str);
    return 0;
}