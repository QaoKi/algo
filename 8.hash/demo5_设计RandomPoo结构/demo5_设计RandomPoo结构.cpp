#include <iostream>
#include <string>
#include "../RandomMap/RandomMap.h"

using namespace std;

/*
	【题目】 设计一种结构，在该结构中有如下三个功能：
				insert(string)：将某个string加入到该结构，做到不重复加入。
				delete(string)：将原本在结构中的某个string移除。
				getRandom()：等概率随机返回结构中的任何一个string。

	【要求】 insert、delete和getRandom方法的时间复杂度都是O(1)
*/

/*
	思路：
		能做到delete删除，加入并且不重复，复杂度为O(1)的只有 unordered_map（底层是哈希表，map的底层是红黑树，查找的时间复杂度为O(logn)）
		只把string当做key加入map中,不需要对应的value，要做到等概率随机返回结构
		中的任何一个key，可以用一个变量size保存此时有多少个key，
		getRandom()的时候，根据size的大小随机产生一个数，用size给每个string编号
		可以把string加入的时候，size作为key，value作为string保存，这样getRandom()的时候，
		随机产生一个数以后，直接根据这个数能O(1)的复杂度找到对应的string
		但是如果删除的时候，就不能实现O(1)了，因为要遍历一遍才能知道这个string在哪
		
		所以可以使用两个map，map1中key为string,value为map的size,map2中，key为map的size，value为
		string

		加入的时候，两个map都加入，getRandom()的时候，根据size随机产生一个数，返回map2中key为
		这个数的value，能做到O(1)
		但是在删除的时候会遇到问题：
			删除中间某一个string的时候，数据中间会产生一个洞
			比如已经加入100个string，编号分别为0~99，如果删除了9号和19号，map1和map2都删除的话，
			下次getRandom()随机产生一个数如果为9或者19的话，9或者19作为key去map2中查找，是不存在的，
			并且此时size已经变了，变为98，再随机出来的数，不会出现99和100，所以98号数据和99号数据
			不会被等概率的查到
			解决办法：
				每次删除的时候，比如删除了9号，就把最大号那条记录删除，把最大号的value放到9号
				因为有size，所以也很快能知道最大号是几号，这样的话，只删除了9号的string，但是没有
				删除9号这个序号

				因为编号只是为了能等概率的返回一个string，所以顺序是没有用处的
*/

int main()
{
    srand(time(NULL));
    RandomMap *ran = new RandomMap;
    ran->insert("a");
    ran->insert("b");
    ran->insert("c");
    ran->insert("c");
    ran->insert("e");
    ran->insert("f");

    cout << ran->getRandom() << endl;
    ran->del("d");
    cout << ran->getRandom() << endl;
    ran->del("b");
    cout << ran->getRandom() << endl;
    ran->del("f");
    cout << ran->getRandom() << endl;
    ran->del("a");
    cout << ran->getRandom() << endl;
    ran->del("c");
    cout << ran->getRandom() << endl;
    return 0;
}