#include <iostream>
#include <string>
#include "TireTree.h"
#include <vector>
#include <set>

using namespace std;

/*
	给定几个单词
		words = [ "oath","pea","eat","rain" ]

	给定一个二维数组
		Board = [	o	a	a	n
					e	t	a	e
					i	h	k	r
					i	f	l	v	]

	从二维数组的(0,0)位置开始，每次只能向右走或者向下走，是否有能和给定单词匹配的
*/

/*
	思路：
		用字典树，先用给定的单词建好一个字典树，然后对二维数组进行遍历，枚举每种情况，不符合的回溯

*/

//currnNode表示当前遍历到字典树的哪个节点,i和j表示当前字符在二维数组中的坐标
//currStr表示当前字符串的组成
void digui(set<string> &result, char arr[4][4], int i,int j,Node* currNode,TireTree* my,string currStr)
{
	//如果能从字典树的头节点，一直能走到某一条路的叶子节点，说明这个字符串能在二维数组中组成
	//如果当前节点是叶子节点，把结果放到结果集
	if (my->nextNumber(currNode) == 0){
		result.insert(currStr);
		return;
	}

	//不是叶子节点，继续向下找
	char temp = arr[i][j];
	if (currNode->nexts.find(temp) != currNode->nexts.end()){

		currStr += temp;

		if (i < 4) {
			digui(result, arr, i + 1, j, currNode->nexts[temp], my, currStr);
		}

		if (j < 4) {
			digui(result, arr, i, j + 1, currNode->nexts[temp], my, currStr);
		}
	}
	else {
		return;
	}
}

void process(char arr[4][4], TireTree* my)
{
	//保存结果集，用set是为了防止重复
	set<string> result;

	//
	for (int i = 0;i < 4;i++){

		for (int j = 0;j < 4;j++){
			
			//遍历二维数组中的每一个字符，以每一个字符为开头去字典树中从头节点开始查找
			digui(result, arr, i, j, my->m_head, my, "");
		}

	}

	for (set<string>::iterator it = result.begin();it != result.end();it++) {
		cout << *it << endl;
	}

}

int main()
{

	char arr[4][4] = {'o','a','a','n','e','t','a','e','i','h','k','r','i','f','l','v'};

	char chIn[10] = "oath";
	char chIn1[10] = "pea";
	char chIn2[10] = "eat";
	char chIn3[10] = "rain";
	char chIn4[10] = "aer";

	TireTree* my = new TireTree;
	my->insert(chIn);
	my->insert(chIn1);
	my->insert(chIn2);
	my->insert(chIn3);
	my->insert(chIn4);

	process(arr, my);


	system("pause");
	return 0;
}