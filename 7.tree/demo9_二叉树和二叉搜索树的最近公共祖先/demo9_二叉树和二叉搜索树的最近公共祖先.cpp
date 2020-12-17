#include <iostream>
#include <string>
#include "../Tree/Tree.h"

using namespace std;

/*
	����һ�����������߶��������������������ڵ�p��q
	�ҵ�p��q������Ĺ�������
*/

/*
	����Ķ�������
		������� DFS��
		�Ӹ��ڵ�root��ʼ���������p��q�е���һ����rootƥ�䣬��ôroot������͹������ȡ� 
		�������ƥ�䣬��ֱ�ݹ����������������һ���ڵ��������������
		������һ���ڵ����������������root������͹�������.  
		��������ڵ㶼����������������˵����͹����������������У��������������� 

	������������
		����������������ģ�
		�������q�ڵ��ֵ����root������p�ڵ��ֵ����root����ô������������������
		���q�ڵ��ֵС��root��p�ڵ��ֵС��root����ô������������������
		����Ļ��������ڵ�ֱ��������������������������Ⱦ���root
*/

//���������
TreeNode *AnyTree(TreeNode *root, TreeNode *q, TreeNode *p)
{
	//��ֹ���������p��q�е���һ����rootƥ�䣬��ôroot���������������
	if (root == NULL || root->data == q->data || root->data == p->data)
		return root;
	//�鿴���������Ƿ���Ŀ���㣬û��Ϊnull
	TreeNode *left = AnyTree(root->left, q, p);
	TreeNode *right = AnyTree(root->right, q, p);

	if (left == NULL)
		//��������û���κ�һ��Ŀ��ڵ㣬��ô������������������
		return right;
	if (right == NULL)
		//��������û���κ�һ��Ŀ��ڵ㣬��ô������������������
		return left;

	//����Ϊ�գ�˵��������������Ŀ���㣬�򹫹����Ⱦ��Ǳ���
	return root;
}

//����������
TreeNode *BSTree(TreeNode *root, TreeNode *q, TreeNode *p)
{
	//�����ڵ��ֵ���� rootС��˵������������ root ��������
	if (root->data > q->data && root->data > p->data)
	{
		return BSTree(root->left, q, p);
	}
	else if (root->data < q->data && root->data < p->data)
	{
		return BSTree(root->right, q, p);
	}
	else
	{
		return root;
	}
}

int main()
{
	TreeNode *root = new TreeNode;
	root->data = 4;

	root->left = new TreeNode;
	root->right = new TreeNode;
	root->left->data = 2;
	root->right->data = 6;

	root->left->left = new TreeNode;
	root->left->left->data = 1;
	root->left->right = new TreeNode;
	root->left->right->data = 3;

	root->right->left = new TreeNode;
	root->right->left->data = 5;
	root->right->right = new TreeNode;
	root->right->right->data = 7;

	TreeNode *res = AnyTree(root, root->left->left, root->left->right);
	cout << "�������ȣ�" << res->data << endl;

	return 0;
}