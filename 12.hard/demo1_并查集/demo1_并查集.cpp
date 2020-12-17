#include <iostream>
#include <string>
#include <vector>
#include "../../Common/UnionFind/UnionFind.h"

using namespace std;

/*
	并查集的功能：
		1，非常快的检查两个元素是否在同一个集合
			isSameSet(a,b),a和b是两个元素，检查两个元素是否在同一个集合中
				
		2，合并：
			union(a,b),a和b是两个元素，如果a和b来自相同的集合，不用管
			如果来自不同的集合，a来自set1，b来自set2，那么将set1和set2全部合并到一起，组成一个set
	应用：
		网络：并查集中的元素，可能是一个计算机网络中的计算机，而连接表示计算机之间的是否可以直接通信，能够判断出
		是否需要在元素a 和元素b 之间架设一条新的连接才能进行通信

	并查集初始化的时候，必须把数据样本（元素）都给它，不能动态的改变节点，能改变的只是节点之间的连接关系
	节点和节点之间的关系，和图中节点的关系类似，都是连接的关系
	并查集初始化的时候，给定节点，比如(a,b,c,d,e,f,g,h)，此时节点之间没有连接，每个节点都在自己的集合中

	当调用 union(a,b)， a 和 b建立连接，让a和b的集合合并，可以用链表，让a指向b或者b指向a，比如让a->next = b
	当再调用 union(b,c)，合并 b和c所在的集合：找b节点所在的链表，将c挂到该链表的后面
	当调用 isSameSet(a,c)，找a所在链表的根节点，就是a，而c节点所在链表的根节点也是a，所以可以判断出 a和c在同一个集合

*/

/*
	思路：

		假设有多个集合set1 = { a1,b1,c1,d1,e1,f1,g1 },set2 = { a2,b2,c2 }
		
		在集合set1中，b1指向a1，c1指向a1,d1指向b1，e1指向c1，f1指向d1,
			a1指向自己，集合中，指向自己的元素，是这个集合的代表元素
			g1 -> f1 -> d1 -> b1 -> a1 <- c1 <- e1
				  
		同样的，set2中，a2指向自己，b2指向a2，c2指向a2，a2是set2的代表元素
					b2 -> a2 <- c2
		这样在判断 isSameSet的时候，只要判断元素A和B所在的集合中，代表元素是否相等

		set1和set2合并：集合中，元素数量较少的那个集合，合并到集合元素多的集合中
			让代表元素合并
			则set2中a2指向a1，完成合并
			g1 -> f1 -> d1 -> b1 -> a1 <- c1 <- e1
									↑
							  b2 -> a2 <- c2

		优化：在查找的时候，比如在合并完以后的集合set中查找f1是否在集合中，遍历完以后，找到代表节点为
				a1，在查找的过程中，让集合扁平化，f1的代表元素是a1，那么f1前面直到a1的元素，它们的
				代表元素都是a1，那么直接让f1指向a1，让d1指向a1，让b1指向a1,g1还是指向f1，下次
				再查找的时候，会减少遍历
			
*/

int main()
{
	Node *a = new Node(1);
	Node *b = new Node(2);
	Node *c = new Node(3);
	Node *d = new Node(4);
	Node *e = new Node(5);
	Node *f = new Node(6);
	Node *g = new Node(7);
	Node *h = new Node(8);
	Node *i = new Node(9);

	vector<Node *> vectorNode;
	vectorNode.push_back(a);
	vectorNode.push_back(b);
	vectorNode.push_back(c);
	vectorNode.push_back(d);
	vectorNode.push_back(e);
	vectorNode.push_back(f);
	vectorNode.push_back(g);
	vectorNode.push_back(h);
	vectorNode.push_back(i);

	UnionFind *unFind = new UnionFind(vectorNode);
	unFind->unionSet(a, b);
	unFind->unionSet(b, c);
	unFind->unionSet(b, d);
	unFind->unionSet(d, e);
	unFind->unionSet(f, g);
	unFind->unionSet(f, h);
	unFind->unionSet(g, i);

	cout << "is same set: " << unFind->isSameSet(a, d) << endl;
	cout << "is same set: " << unFind->isSameSet(d, f) << endl;
	cout << "is same set: " << unFind->isSameSet(c, h) << endl;

	unFind->unionSet(d, i);

	cout << "is same set: " << unFind->isSameSet(a, d) << endl;
	cout << "is same set: " << unFind->isSameSet(d, f) << endl;
	cout << "is same set: " << unFind->isSameSet(c, h) << endl;
	return 0;
}