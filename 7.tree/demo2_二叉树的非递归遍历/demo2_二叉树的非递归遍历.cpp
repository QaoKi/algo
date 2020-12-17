#include <iostream>
#include <string>
#include "../Tree/Tree.h"
#include <stack>

using namespace std;

/*
	�ǵݹ�������ݹ�����ı�����ϵͳ�����ǽ����ݷŵ�ջ�У������Լ���һ��ջ�����ݴ�����

		����������ȱ����ڵ㣬�ٱ���������������������������ôѹջ��ʱ���Ȱ�������ѹջ��
		�ٰ�������ѹջ
*/

void preOrder(TreeNode *root)
{
	if (root == NULL)
		return;
	stack<TreeNode *> stackNode;
	stackNode.push(root);

	TreeNode *curr = root;
	while (!stackNode.empty())
	{
		curr = stackNode.top();
		stackNode.pop();
		cout << curr->data << "  ";
		//�ҽڵ�����ջ��������
		if (curr->right != NULL)
			stackNode.push(curr->right);
		//��ڵ�����ջ����ջ��ʱ����ڵ��ȳ�ջ
		if (curr->left != NULL)
			stackNode.push(curr->left);
	}
}

void inOrder(TreeNode *root)
{
	if (root == NULL)
		return;
	stack<TreeNode *> stackNode;

	TreeNode *curr = root;
	/*
		˼·��
			��ǰ�ڵ㲻Ϊ�գ���ǰ�ڵ�ѹ��ջ����ǰ�ڵ������ƶ�
			��ǰ�ڵ�Ϊ�գ���ջ����һ������ӡ����ǰ�ڵ������ƶ�
	*/
	while (curr != NULL || !stackNode.empty())
	{
		//��ǰ�ڵ㲻Ϊ�գ���ǰ�ڵ�ѹ��ջ����ǰ�ڵ������ƶ�
		//��ΪҪ�ѵ�ǰ������߽��ȶ�ѹ��ջ��
		if (curr != NULL)
		{
			stackNode.push(curr);
			curr = curr->left; //����ڵ㻹����������������������ѹջ��һֱ�ҵ���������Ľڵ�
		}
		else
		{
			//��ǰ�ڵ�Ϊ�գ���ջ����һ������ӡ����ǰ�ڵ������ƶ�
			curr = stackNode.top();
			stackNode.pop();
			cout << curr->data << "  ";
			curr = curr->right;
		}
	}
}

//����ǵݹ�ʵ��
void postOrder(TreeNode *root)
{
	if (root == NULL)
		return;

	/*
		����������������ң����Ƚ���ǰ�ڵ��ӡ���ٰ�������ѹջ���ٰ�������ѹջ�������������ͱ��������ȳ�ջ

		���������ʵ�֣������е�˳��������������������������˳�����Կ����ýڵ㣬���������˳��
			������һ��ջ stackHelp��stackHelp�ٳ�ջ���������е�˳��
			Ҫʵ�������ҵĵ�˳�򣬵�ǰ�ڵ�����ջstackHelp��Ȼ����������stackHelp,�����������stackHelp
	*/
	stack<TreeNode *> stackNode;
	stack<TreeNode *> stackHelp;

	TreeNode *curr = root;
	stackNode.push(curr);

	while (!stackNode.empty())
	{
		curr = stackNode.top();
		stackNode.pop();

		//��ǰ�ڵ�����stackHelp,����������еĴ�ӡ�����ջ
		stackHelp.push(curr);

		//����������ջ
		if (curr->left != NULL)
			stackNode.push(curr->left);

		//����������ջ
		if (curr->right != NULL)
			stackNode.push(curr->right);
	}

	//��ʱ stackHelp �У������������˳�������γ�ջ��ӡ�����������е�˳��

	while (!stackHelp.empty())
	{
		curr = stackHelp.top();
		stackHelp.pop();
		cout << curr->data << "  ";
	}
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

	//����������ȱ������ڵ㣬�ٱ�����������������������
	cout << "�������Ϊ��  ";
	preOrder(root);
	cout << endl;

	//����������ȱ������������ٱ������ڵ㣬������������
	cout << "�������Ϊ��  ";
	inOrder(root);
	cout << endl;

	//����������ȱ������������ٱ��������������������ڵ�
	cout << "�������Ϊ��  ";
	postOrder(root);
	cout << endl;

	return 0;
}