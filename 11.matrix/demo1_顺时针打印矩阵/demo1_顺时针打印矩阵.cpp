#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
	��Ŀ������һ�����;���matrix���밴��˳ʱ��ķ�ʽ��ӡ��
	���磺
			1	2	3	
			4	5	6
			7	8	9
			10	11	12
	��ӡ���Ϊ�� 1	2	3	6	9	12	11	10	7	4	5	8
	��Ҫ�� ����ռ临�Ӷ�ΪO(1)
*/

/*
	˼·������1��λ�õ��±�Ϊ(a,b)��12��λ�õ��±�Ϊ(c,d)��
	��ô��������������
				b		d
		
		a		1	2	3
				4	5	6
				7	8	9
		c		10	11	12

		��ӡ���մ�bһֱ�ӵ�dΪֹ���ٴ�a�ӵ���c���ٴ�d����b���ٴ�c����a��������Ȧ�ʹ�ӡ����
		ע��߽�����Ĵ�������������ֻ��һ�л�һ�У���a==c����b==dʱ��
		ÿ�δ�ӡһ�л�һ�е�ʱ�򣬰����һ�����������ȵ���һ�л���һ�е�ʱ���ӡ

	����Ȧ��ӡ���ˣ������Ͻǵĺ�������ֱ��1�������½ǵĺ�������ֱ��1���ٴ�ӡ�ڶ�Ȧ
	�����Ͻǵĺ�����������꣬�������½ǵĺ������������ʱֹͣ
*/

//��ӡһȦ
void printLoop(vector<vector<int>> &vecMatrix, int leftHeng, int leftZong, int rightHeng, int rightZong)
{
	//���Ͻǵĺ�����������½ǵĺ����꣬˵��ֻ��һ��
	//�������������if�����⴦�� ֻ��һ�л���һ�е����ݣ���������

	if (leftHeng == rightHeng)
	{
		for (int i = leftZong; i <= rightZong; i++)
			cout << vecMatrix[leftHeng][i] << "   ";
	}
	else if (leftZong == rightZong) //���Ͻǵ�������������½ǵ������꣬˵��ֻ��һ��
	{
		for (int i = leftHeng; i <= rightHeng; i++)
			cout << vecMatrix[i][leftZong] << "   ";
	}
	else
	{
		//��4��whileѭ������ӡ��Ȧ��ÿһ�к�ÿһ�е����һ�������ȵ���һ�л���һ�е�ʱ���ӡ������������ < �������� <=

		//�ȴ�ӡ�������һ�У������겻�䣬������������
		int i = leftZong;
		while (i < rightZong)
			cout << vecMatrix[leftHeng][i++] << "   ";

		//�ٴ�ӡ���ұߵ�һ�У������겻�䣬��������ϵ���
		i = leftHeng;
		while (i < rightHeng)
			cout << vecMatrix[i++][rightZong] << "   ";

		//�ٴ�ӡ�������һ�У������겻�䣬��������ҵ���
		i = rightZong;
		while (i > leftZong)
			cout << vecMatrix[rightHeng][i--] << "   ";

		//����ӡ����ߵ�һ�У������겻�䣬��������µ���
		i = rightHeng;
		while (i > leftHeng)
			cout << vecMatrix[i--][leftZong] << "   ";
	}
}

void printMatrix(vector<vector<int>> &vecMatrix)
{
	if (vecMatrix.size() == 0) //һ��Ҳû��
		return;
	/*
		1	2	3	
		4	5	6
		7	8	9
		10	11	12
	*/

	//���Ͻǵ���������½ǵ����ꡣ�кű�ʾ���Ǻ����꣬�кű�ʾ����������
	int leftHeng = 0;
	int leftZong = 0;
	int rightHeng = vecMatrix.size() - 1;
	int rightZong = vecMatrix[0].size() - 1;

	while (leftHeng <= rightHeng && leftZong <= rightZong)
	{
		//һȦ��ӡ���Ժ����Ͻǵ��к��зֱ��1�����½ǵ��к��зֱ��1
		printLoop(vecMatrix, leftHeng, leftZong, rightHeng, rightZong);

		leftHeng++;
		leftZong++;
		rightHeng--;
		rightZong--;
	}
}

int main()
{
	//��������У����������
	vector<vector<int>> vecMatrix;
	//{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}
	//4��3�С��У�row���У�column
	int row = 4;
	int column = 3;
	for (int i = 0; i < row; i++)
	{
		vector<int> vecRow;
		for (int j = 0; j < column; j++)
		{
			cout << i * column + j + 1 << "  ";
			vecRow.push_back(i * column + j + 1);
		}
		cout << endl;
		vecMatrix.push_back(vecRow);
	}

	printMatrix(vecMatrix);
	return 0;
}