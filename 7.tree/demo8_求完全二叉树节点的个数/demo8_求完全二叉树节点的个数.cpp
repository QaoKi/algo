#include <iostream>
#include <string>
#include "../Tree/Tree.h"
#include <math.h>

using namespace std;

/*
	��֪һ����ȫ������������ڵ�ĸ���
		Ҫ��ʱ�临�Ӷȵ���O(N)��NΪ������Ľڵ����
*/

/*
	���һ�������������߶�Ϊh����ô�ڵ����Ϊ2^h - 1
	����������ԣ�
		һ����ȫ��������currָ��root,��������ĸ߶�,h
		����curr���������ĸ߶� r,
		���r = h - 1����ô˵�����ڵ��������������߽�Ľڵ㣬�������һ��
				Ҳ����˵�������ڵ������������������
				��ͼ��					  1
									2			3
								4		5	6	
					h Ϊ3�����ڵ��������ĸ߶� r Ϊ2��������������߽�6�Žڵ㣬�������һ�㣬
					����ڵ������������������
				�������������������������ĸ߶�Ϊ h - 1�����������Ľڵ���Ϊ2^(h-1) -1 ,���ԣ�
				���������ϸ��ڵ㣬һ��2^(h-1) ���ڵ㣬����currָ����ڵ������������������Ϊ
				���ڵ㣬�ж�curr���������ĸ߶��Ƿ�ﵽ���һ�㣬���ж�curr���������Ƿ�����������
		���r != h - 1�����������ܲ������������������������϶�������������ͬ������������Ӹ��ڵ�Ľڵ���
		����currָ����ڵ�����������ݹ���

*/

int recursion(TreeNode *root, int h)
{
	//�ݹ���ֹ����
	if (root == NULL || h <= 0)
		return 0;

	int nodeNum = 0;
	//������������ĸ߶�
	int rh = 0;
	TreeNode *curr = root->right;
	while (curr != NULL)
	{
		rh++;
		curr = curr->left;
	}

	/*
		���������������ģ��������������ϸ��ڵ�Ľڵ���
		�����ڵ��������Ϊ�գ��������ڵ���Ϊ0�����ϸ��ڵ㣬�ܹ�Ϊ1��
		��2^0 ����Ϊ1�����Բ���Ҫ���⴦��
		���������⴦��

	if (rH == nH - 1)
	{
		nodeNum += pow(2,rH);
		//���Ը��ڵ��������Ϊ���ڵ㣬�ݹ���
		nodeNum += digui(root->right, nH - 1);
	}
	else if(rH != 0)		//��Ϊ2^0Ϊ1�����������
	{
		//������������

		nodeNum += pow(2, rH);
		//���Ը��ڵ��������Ϊ���ڵ㣬�ݹ���
		nodeNum += digui(root->left, nH - 1);
	}
	else
	{
		nodeNum = 1;

		//���Ը��ڵ��������Ϊ���ڵ㣬�ݹ���
		nodeNum += digui(root->left, nH - 1);
	}
	*/

	//����������
	if (rh == h - 1)
	{
		nodeNum += pow(2, rh) - 1 + 1; //���ϸ��ڵ�
		//���Ը��ڵ��������Ϊ���ڵ㣬�ݹ���
		nodeNum += recursion(root->right, h - 1);
	}
	else
	{
		//������������
		nodeNum += pow(2, rh) - 1 + 1; //���ϸ��ڵ�
		//���Ը��ڵ��������Ϊ���ڵ㣬�ݹ���
		nodeNum += recursion(root->left, h - 1);
	}

	return nodeNum;
}

int GetNodeNum(TreeNode *root)
{
	if (root == NULL)
		return 0;
	//�����ĸ߶�
	TreeNode *curr = root;
	int h = 0;
	while (curr != NULL)
	{
		h++;
		curr = curr->left;
	}

	return recursion(root, h);
}

int main()
{

	TreeNode *root = new TreeNode;
	root->data = 1;

	root->left = new TreeNode;
	root->right = new TreeNode;
	root->left->data = 2;
	root->right->data = 3;

	root->left->left = new TreeNode;
	root->left->left->data = 4;
	root->left->right = new TreeNode;
	root->left->right->data = 5;

	root->right->left = new TreeNode;
	root->right->left->data = 6;
	root->right->right = new TreeNode;
	root->right->right->data = 7;

	cout << "�ڵ�������" << GetNodeNum(root) << endl;

	return 0;
}