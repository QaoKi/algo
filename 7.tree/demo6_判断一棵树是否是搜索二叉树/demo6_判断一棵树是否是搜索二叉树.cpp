#include <iostream>
#include <string>
#include "../Tree/Tree.h"
#include <stack>
#include <limits.h>

using namespace std;

/*
	�������������ֽ������������������߶���������
		���������κ�һ���ڵ㣬���������������н�㶼����������ҪС��
							  ���������������н�㶼����������Ҫ��

		ע���Ǹ�������������������еĽ����бȽ϶����ǽ��������Һ��ӽ����бȽ�
		�������������������һ������������ʱ����Ȼ�ǵ��������ģ�
		������������У���֮�����һ�ö�����������������õ�������������ģ�
		��ô��ö�����һ������������������˶�������������ͨ�����ǽ�����������Ĳ���
*/

/*
	˼·��
		ͨ����˵�������������������ظ��ڵ� 
		�����ϣ���ÿ���ڵ�Ϊ���ڵ�����������ڵ㶼Ҫ�����е��������ϵĽڵ�С�������е��������ϵĽڵ��
		�������������Ϊ�б�����˳���������ң������������ʱ��ֻ��Ҫ�ж�
		��ǰ�ڵ��ֵ������ǰһ�������Ľڵ��ֵ��Ϳ����ˡ�ע�⣬����Ҳ������

		�ȸķǵݹ�������ݹ�ıȽ��鷳

*/

bool not_recursion(TreeNode *root)
{
	if (root == NULL)
		return false;
	TreeNode *curr = root;
	stack<TreeNode *> stackNode;

	//��ǰ�ڵ㲻Ϊ�գ���ǰ�ڵ���ջ����ǰ�ڵ������ƶ�
	//��ǰ�ڵ�Ϊ�գ���ջ��ȡһ��������ӡ����ǰ�ڵ������ƶ�����ӡ�Ĺ��̣����ɱȽϡ�
	long preValue = (long)INT_MIN - 1; //-1; //��һ���ڵ��ֵ
	while (curr != NULL || !stackNode.empty())
	{
		if (curr != NULL)
		{
			stackNode.push(curr);
			curr = curr->left;
		}
		else
		{
			curr = stackNode.top();
			stackNode.pop();
			//��ǰһ�����Ƚϣ�����Ҳ������
			if (curr->data <= preValue)
				return false;
			else
				preValue = curr->data;

			curr = curr->right;
		}
	}
	return true;
}

//�������ʱ���жϵ�ǰ�ڵ��Ƿ�������������ǰһ���ڵ㣬������ڣ�˵�����㣬��������������ֱ�ӷ��� false��
long _preValue = (long)INT_MIN - 1;
bool isValidBST(TreeNode *node)
{
	if (node == NULL)
		return true;
	//�ж��������Ƿ����
	if (!isValidBST(node->left))
		return false;

	//��ǰ�ڵ��Ƿ����ǰһ���ڵ�
	if (node->data <= _preValue)
		return false;
	_preValue = node->data;

	//�ж��������Ƿ����
	return isValidBST(node->right);
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

	if (not_recursion(root))
		cout << "������������" << endl;
	else
		cout << "��������������" << endl;

	if (isValidBST(root))
		cout << "������������" << endl;
	else
		cout << "��������������" << endl;

	return 0;
}