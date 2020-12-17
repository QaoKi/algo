#include <iostream>
#include <string>
#include "TireTree.h"
#include <vector>
#include <set>

using namespace std;

/*
	������������
		words = [ "oath","pea","eat","rain" ]

	����һ����ά����
		Board = [	o	a	a	n
					e	t	a	e
					i	h	k	r
					i	f	l	v	]

	�Ӷ�ά�����(0,0)λ�ÿ�ʼ��ÿ��ֻ�������߻��������ߣ��Ƿ����ܺ͸�������ƥ���
*/

/*
	˼·��
		���ֵ��������ø����ĵ��ʽ���һ���ֵ�����Ȼ��Զ�ά������б�����ö��ÿ������������ϵĻ���

*/

//currnNode��ʾ��ǰ�������ֵ������ĸ��ڵ�,i��j��ʾ��ǰ�ַ��ڶ�ά�����е�����
//currStr��ʾ��ǰ�ַ��������
void digui(set<string> &result, char arr[4][4], int i,int j,Node* currNode,TireTree* my,string currStr)
{
	//����ܴ��ֵ�����ͷ�ڵ㣬һֱ���ߵ�ĳһ��·��Ҷ�ӽڵ㣬˵������ַ������ڶ�ά���������
	//�����ǰ�ڵ���Ҷ�ӽڵ㣬�ѽ���ŵ������
	if (my->nextNumber(currNode) == 0){
		result.insert(currStr);
		return;
	}

	//����Ҷ�ӽڵ㣬����������
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
	//������������set��Ϊ�˷�ֹ�ظ�
	set<string> result;

	//
	for (int i = 0;i < 4;i++){

		for (int j = 0;j < 4;j++){
			
			//������ά�����е�ÿһ���ַ�����ÿһ���ַ�Ϊ��ͷȥ�ֵ����д�ͷ�ڵ㿪ʼ����
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