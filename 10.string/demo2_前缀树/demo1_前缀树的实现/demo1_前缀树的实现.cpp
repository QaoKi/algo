#include <iostream>
#include <string>
#include "../TireTree/TireTree.h"

using namespace std;

/*
	前缀树（trie树、字典树）：
		一个字符串添加到树中的过程，总是从头节点开始，依次检查是否有沿途的路，
		如果有，复用，如果没有，新建出来
		
		比如有一个字符串 "abc"，设一个头节点，开始时为空，从头节点到第一个字符"a"没有路，
		新建一个节点，节点用O表示，把"a"放到路上，而不是放到节点上，再看"b"，从"a"开始，沿途的路
		中没有"b",建一个节点，把b放到路上，同理，从"b"到"c"也建一条路

		下一个字符串 "bde",从头节点到"b"没有沿途的路，建一个节点，把"b"放到路上,从"b"到"d"没有沿途的路，所以在b
		上建一个节点，路上加上d。。。
				e	   d	  b		 a		b	   c
		    O <--- O <--- O <--- 头 ---> O ---> O ---> O

		下一个字符串，"bfg",从头节点到b，有沿途的路，复用，从b到f没有路，新建节点，从f到g没有路，新建

				e	   d	  b		 a		b	   c
			O <--- O <--- O <--- 头 ---> O ---> O ---> O
						  |	f
						  ↓
						  O
						  |	g
						  ↓
						  O

	前缀树的作用：
		1，字符串的快速检索：比如，给了n个字符串建好前缀树以后，检查是否含有以"be"开头的字符串
		2，词频统计，给定一个字符串，检查该字符串插入树中多少次
		3，字符串排序：Trie树可以对大量字符串按字典序进行排序
		4，前缀匹配
		5、作为其他数据结构和算法的辅助结构，如后缀树，AC自动机等。
					
	实现上面的功能：
		1，给定字符串 "be"，检查有多少个以"be"为前缀的字符串。
			在Node中加一个字段 path，表示通过这个节点多少次，
			比如先加了"abc"，再加"abd",最后加了"abe",
			那么"a","b","c"指向的节点(因为"a","b","c"是存在路径上，不是存在节点上)，path加1，
			再让"a","b","d"指向的节点path加1，最后让"a","b","e"指向的节点path加1，
			最后"a"的path为3，表示以"a"为前缀的字符串有3个，"b"为3，表示以"ab"为前缀的字符串有3个，"c","d","e"各有1个
		2，给了n个字符串建好前缀树以后，给定字符串 "be"，检查n个字符串中是否含有"be"，或者含有多少个"be"。
			因为n个字符串中可能含有"befg"这种以"be"为前缀的，所以只判断树中有"be"会出问题，
			在节点中加一个字段 end，表示以当前节点为结尾的字符串的数量。
			比如先加了"abc"，再加"bde",最后加了"bfg"，那么"c"指向的节点end加一，"e"指向的节点end加1，"g"指向的节点end加1，
			检查是否含有"bd"：沿着头节点找到b,再找到d，d为0，说明不含有"bd"
		3，遍历一次所有关键字，将它们全部插入trie树，树的每个结点的所有儿子很显然地按照字母表排序，然后先序遍历输出Trie树中所有关键字即可。

*/

/*
	时间复杂度：
		插入和查询的销量为 O(N)，N为待插入/查询的字符串长度
	空间复杂度：保存所有的字符串
*/

int main()
{

	TireTree *my = new TireTree;
	my->insert("abc");
	my->insert("abd");
	my->insert("cbc");
	my->insert("csd");
	my->insert("bac");
	my->insert("bac");

	cout << "bac   exit: " << my->search("bac") << endl;
	cout << "abd   exit: " << my->search("abd") << endl;
	my->deleteStr("bac");
	my->deleteStr("abd");
	cout << "bac   exit: " << my->search("bac") << endl;
	cout << "abd   exit: " << my->search("abd") << endl;

	cout << "c  prefix: " << my->prefixNumber("c") << endl;

	return 0;
}