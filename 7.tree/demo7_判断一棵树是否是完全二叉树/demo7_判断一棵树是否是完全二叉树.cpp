#include <iostream>
#include <string>
#include "../Tree/Tree.h"
#include <queue>

using namespace std;

/*
	��ȫ��������
		�Ѿ���һ����ȫ�������������������ʾ	
*/

/*
	˼·��
	���������
		1.һ���ڵ㣬���Һ��ӣ�����û�����ӣ��϶�������ȫ������ 
		2����һ���ڵ㣬������û���Һ��ӣ��������Һ��Ӷ�û��ʱ������ڵ�������еĽڵ㣬
			��������Ҷ�ڵ㣨û�����Һ��ӣ�
	���磺
								  1
							2			3
						4		5	6		7
					 8	   9 10

		���ڵ������5�ţ����ϵ�2���������ô5֮��Ľڵ㣬������û�����Һ���
		Ҫ����һ�����أ����ؿ���֮��֮��Ľڵ㶼����û�����Һ���

	��Ҫ���а����������ȱ���������ÿ���ڵ���з���
		��һ������ʵ�ְ������
*/
bool check(TreeNode *root)
{
	TreeNode *curr = root;
	queue<TreeNode *> queueNode;
	queueNode.push(curr);

	//����һ�����������ӵ�û���Һ��ӣ����ߵ�һ���������Һ��Ӷ�û�е�ʱ����֮��Ľڵ㶼����û�����Һ���
	bool bLock = false;

	//һ���ڵ�һ���ڵ��ȥ�ж�
	while (!queueNode.empty())
	{
		curr = queueNode.front();
		queueNode.pop();

		//��һ�������ֱ�ӷ���false
		if (curr->left == NULL && curr->right != NULL)
			return false;

		//��һ�����������ӵ�û���Һ��ӣ����ߵ�һ���������Һ��Ӷ�û�е�ʱ��
		//ע�⣬������ if ���ܺϲ���һ��
		if (!bLock)
		{
			//��ʱֻҪ�ж�û���Һ��Ӽ���
			if (curr->right == NULL)
				bLock = true;
		}
		else
		{
			//������ؿ����ˣ��ڵ㻹�����ӻ����Һ��ӣ�����false
			if (curr->left != NULL || curr->right != NULL)
				return false;
		}

		if (curr->left != NULL)
			queueNode.push(curr->left); //�Ƚ����Ӽ��������

		if (curr->right != NULL)
			queueNode.push(curr->right); //�ٽ��Һ��Ӽ��������
	}

	return true;
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

	//����Ƿ�����ȫ������
	if (check(root))
		cout << "����ȫ������" << endl;
	else
		cout << "������ȫ������" << endl;

	return 0;
}