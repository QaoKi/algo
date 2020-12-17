#include <iostream>
#include <string>
#include "../Tree/Tree.h"

using namespace std;

/*
	ƽ���������
		�����е��κ�һ���ڵ㣬�������������������ĸ߶Ȳ����1
		����һ��������			1
							2  		3
						 	  4	  5
		�ڵ�1���������߶�Ϊ2���������߶�Ϊ2��ƽ��
		�ڵ�2��3���������������߶ȲΪ1��ƽ��
		����һ��������			1
							2  		3
							  4   5
							6       7
		�ڵ�2���������߶�Ϊ0���������߶�Ϊ2����ƽ��
		�ڵ�3���������߶�Ϊ2���������߶�Ϊ0����ƽ��.

*/

/*
	˼·��
		�õݹ����˼�룬������Ҫƽ�⣬��ôÿ���ڵ������������Ҫƽ�⣬
		��������ƽ�����Ժ���Ҫ�����������ĸߺ��������ĸ����ж�����������������һ�����ƽ��ƽ��
		������Ҫ�����������Ƿ�ƽ�⣬�������ĸߣ��������Ƿ�ƽ�⣬�������ĸߣ���һ���ṹ�����洢
		Ҳ���Բ��ýṹ�壬����-1����ʾ������ƽ�⣬����0����ʾ��������ƽ��ģ�����>0����ʾ���ĸ߶ȣ���ƽ���

		�г������ԣ����������ֵ�����ͣ������ݹ���̰���ͬ���Ľṹ���õ���������Ϣ��������������Ϣ��
		�ӹ�������Ҫ����Ϣ�����Ϸ��أ���Ϊ�ǵݹ飬���ԽṹҪ��һ��
*/

/*
	�����������̣�n��ʾnull
				   1
			2		       3
		n		4      n	     5
			 n     n   

		��ǰ�ڵ�currָ��1����ȥ����������currָ��2������2����������currָ��2��
		������ null��currΪnull������true��0����ʾ��ƽ��ģ��߶�Ϊ0��2�Žڵ��֪������������
		��ƽ��ģ��߶�Ϊ0����ȥ�ж���������currָ��4�ţ��ٷֱ�ָ��4��������null��������Null��
		��4�Ż�õ�����true��0��4��֪������������������ƽ��ģ����ж����������ϲ��Ժ�ƽ��ƽ��
		���������߶ȶ�Ϊ0����ƽ��ģ���ʱ���������������ĸ߶ȼ�1��Ҳ����1
		currָ��2�ţ�2�Ż�õ���������true��0���õ���������true��1��2����ȥ�ж����������ϲ��Ժ�
		ƽ��ƽ�⣬���Ϊƽ�⣬��1�ŷ���true�������������߶ȼ�1��Ϊ2������2�Ÿ�1�ŷ���true��2
		ͬ��1�ŵ�������Ҳ���������Ժ��ٽ����ж����������ϲ��Ժ��Ƿ�ƽ��
*/

//���� -1����ʾ��ƽ�⣬���� >= 0 ����ʾ������ȣ�ƽ��
int depth(TreeNode *node)
{
	if (node == NULL) //����ǿ�����Ҳ��ƽ���
		return 0;

	//���ж��������Ƿ�ƽ��
	int leftHigh = depth(node->left);
	//node ����������ƽ�⣬��ô�� node Ϊ���ڵ����Ҳ��ƽ��
	if (leftHigh == -1)
		return -1;
	//��ȥ�ж��������Ƿ�ƽ��
	int rightHigh = depth(node->right);
	//ͬ��node ����������ƽ�⣬��ô�� node Ϊ���ڵ����Ҳ��ƽ��
	if (rightHigh == -1)
		return -1;

	//��ʱ�����������������Ѿ�ƽ�⣬�ж����������������ϲ�������Ƿ�ƽ��
	if (leftHigh - rightHigh > 1 || rightHigh - leftHigh > 1)
		return -1;

	//�������������������и߶ȸ�����Ǹ��߶ȼ�1
	return leftHigh > rightHigh ? leftHigh + 1 : rightHigh + 1;
}

bool isBalanced(TreeNode *root)
{
	return depth(root) != -1;
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

	if (isBalanced(root))
		cout << "��ƽ���" << endl;
	else
		cout << "����ƽ���" << endl;

	return 0;
}