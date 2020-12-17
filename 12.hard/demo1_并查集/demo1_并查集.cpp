#include <iostream>
#include <string>
#include <vector>
#include "../../Common/UnionFind/UnionFind.h"

using namespace std;

/*
	���鼯�Ĺ��ܣ�
		1���ǳ���ļ������Ԫ���Ƿ���ͬһ������
			isSameSet(a,b),a��b������Ԫ�أ��������Ԫ���Ƿ���ͬһ��������
				
		2���ϲ���
			union(a,b),a��b������Ԫ�أ����a��b������ͬ�ļ��ϣ����ù�
			������Բ�ͬ�ļ��ϣ�a����set1��b����set2����ô��set1��set2ȫ���ϲ���һ�����һ��set
	Ӧ�ã�
		���磺���鼯�е�Ԫ�أ�������һ������������еļ�����������ӱ�ʾ�����֮����Ƿ����ֱ��ͨ�ţ��ܹ��жϳ�
		�Ƿ���Ҫ��Ԫ��a ��Ԫ��b ֮�����һ���µ����Ӳ��ܽ���ͨ��

	���鼯��ʼ����ʱ�򣬱��������������Ԫ�أ������������ܶ�̬�ĸı�ڵ㣬�ܸı��ֻ�ǽڵ�֮������ӹ�ϵ
	�ڵ�ͽڵ�֮��Ĺ�ϵ����ͼ�нڵ�Ĺ�ϵ���ƣ��������ӵĹ�ϵ
	���鼯��ʼ����ʱ�򣬸����ڵ㣬����(a,b,c,d,e,f,g,h)����ʱ�ڵ�֮��û�����ӣ�ÿ���ڵ㶼���Լ��ļ�����

	������ union(a,b)�� a �� b�������ӣ���a��b�ļ��Ϻϲ���������������aָ��b����bָ��a��������a->next = b
	���ٵ��� union(b,c)���ϲ� b��c���ڵļ��ϣ���b�ڵ����ڵ�������c�ҵ�������ĺ���
	������ isSameSet(a,c)����a��������ĸ��ڵ㣬����a����c�ڵ���������ĸ��ڵ�Ҳ��a�����Կ����жϳ� a��c��ͬһ������

*/

/*
	˼·��

		�����ж������set1 = { a1,b1,c1,d1,e1,f1,g1 },set2 = { a2,b2,c2 }
		
		�ڼ���set1�У�b1ָ��a1��c1ָ��a1,d1ָ��b1��e1ָ��c1��f1ָ��d1,
			a1ָ���Լ��������У�ָ���Լ���Ԫ�أ���������ϵĴ���Ԫ��
			g1 -> f1 -> d1 -> b1 -> a1 <- c1 <- e1
				  
		ͬ���ģ�set2�У�a2ָ���Լ���b2ָ��a2��c2ָ��a2��a2��set2�Ĵ���Ԫ��
					b2 -> a2 <- c2
		�������ж� isSameSet��ʱ��ֻҪ�ж�Ԫ��A��B���ڵļ����У�����Ԫ���Ƿ����

		set1��set2�ϲ��������У�Ԫ���������ٵ��Ǹ����ϣ��ϲ�������Ԫ�ض�ļ�����
			�ô���Ԫ�غϲ�
			��set2��a2ָ��a1����ɺϲ�
			g1 -> f1 -> d1 -> b1 -> a1 <- c1 <- e1
									��
							  b2 -> a2 <- c2

		�Ż����ڲ��ҵ�ʱ�򣬱����ںϲ����Ժ�ļ���set�в���f1�Ƿ��ڼ����У��������Ժ��ҵ�����ڵ�Ϊ
				a1���ڲ��ҵĹ����У��ü��ϱ�ƽ����f1�Ĵ���Ԫ����a1����ôf1ǰ��ֱ��a1��Ԫ�أ����ǵ�
				����Ԫ�ض���a1����ôֱ����f1ָ��a1����d1ָ��a1����b1ָ��a1,g1����ָ��f1���´�
				�ٲ��ҵ�ʱ�򣬻���ٱ���
			
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