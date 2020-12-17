#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "../UnionFind/UnionFind.h"
using namespace std;

/*
https://www.cnblogs.com/SkyeAngel/p/8953007.html

	�����⣺
		һ��������ֻ��0��1����ֵ��ÿ��λ�ö����Ժ��Լ����ϡ��¡�����
		�ĸ�λ�������������һƬ1����һ��������ֽ���һ��������һ��
		�������ж��ٸ�����

		������
			0 1 1 0 1 0
			1 1 1 0 1 0
			1 0 0 1 0 0
			0 0 0 0 0 0

		�������������������
*/

/*
	DFS:
		����ѭ��������ÿ���ڵ㣬ֻҪ�ڵ��ֵΪ1���ͽ����Ⱦ���� infect(),infect()�ݹ������ڵ�
		��������Χ��1�����2��ͬʱ����������1��������������У���һ�α�����(0,1)�����1ʱ������
		infect()������Χ�Ķ����2������������1��ֱ����������
					0 2 2 0 1 0
					2 2 2 0 1 0
					2 0 0 1 0 0
					0 0 0 0 0 0
		ʱ�临�Ӷ�:���������е����ݶ���1����ô�����е�����Ҫ�������飬���Ӷ�ΪO(2*N*M)
		����ʱ�临�Ӷ�ΪO(N*M)

	��չ��������������������ܴ���ô��û��ʲô�����������
		���Σ�
			��һ������󻯳ɶ��С������󽫲�ͬ�ľ���ϲ���
			�ϲ���ʱ��������鼯����߽����⣬���߽�������һƬ��1�ϲ�
					0 1 1  1 1 0
					1 1 1  1 1 0
					1 0 0  1 0 0
					0 0 1  1 0 1
		����������ֳ����飬�ֱ���㵺��������ߵĵ�2�����ұߵĵ�2����
		���ò��鼯�ṹ����һ�β鿴��1��λ����(0,1)λ�ã�������㣬��Ϊ������Ĵ���ڵ㣬����
		��ΪA����(0,2)(1,0)(1,1)(1,2)(2,0)λ�ö����������������ڵ㶼ΪA�����½ǵĵ��Ĵ���ڵ�ΪB

		ͬ���ұ߾����У���һ�����Ĵ���ڵ�ΪC�����½ǵ��Ĵ���ڵ�ΪD

		���ڿ�ʼ�ϲ�������С����һ���õ�4������4������ڵ�
		ֻ��Ҫ����߽��ϵĽڵ㣬��(0,2)λ�ú�(0,3)λ�ã�����1�ϲ�����ߵĴ���ڵ�ΪA���ұߵ�
		����ڵ�ΪC����һ������ô����������1����A��C�ϲ�
		��(1,2)λ�ú�(1,3)λ�ã�����1�ϲ�����ߴ���ڵ�ΪA���ұ�ҲΪA�����ù�
		��(2,2)λ��Ϊ0��(2,3)λ��Ϊ1�����ù�
		��(3,2)λ�ú�(3,3)λ�ã�����1�ϲ�����ߵĴ���ڵ�ΪB���ұߵ�
		����ڵ�ΪA����һ������ô����������1����A��B�ϲ�

		���õ���������Ϊ2
*/

//�򵥰棺��DFS
void infect(vector<vector<int>> &vectorArray, int i, int j)
{
	//���ڵ�Խ�磬��ڵ��ֵ��Ϊ1�������ݹ�
	if (i < 0 || i >= vectorArray.size() || j < 0 || j >= vectorArray[i].size() || vectorArray[i][j] != 1)
		return;

	vectorArray[i][j] = 2; //��ֵ��Ϊ2����0
	//�ݹ��ýڵ�����������е�1�����2������������ҵĽڵ����нڵ�Ϊ1����ô�ټ��ýڵ����������
	infect(vectorArray, i + 1, j);
	infect(vectorArray, i - 1, j);
	infect(vectorArray, i, j + 1);
	infect(vectorArray, i, j - 1);
}

int DFS(vector<vector<int>> vectorArray)
{
	int ret = 0;
	for (int i = 0; i < vectorArray.size(); i++)
	{
		for (int j = 0; j < vectorArray[i].size(); j++)
		{
			//����ÿ����
			if (vectorArray[i][j] == 1)
			{
				ret++;
				infect(vectorArray, i, j);
			}
		}
	}

	return ret;
}

//��չ��
int UseUnionFind(vector<vector<int>> grid)
{
	int nr = grid.size();
	if (!nr)
		return 0;
	int nc = grid[0].size();

	//���ĳ�����ֵΪ1���ͰѸ�������Ϊһ���������Ϸ��벢�鼯
	//���ð����еĵ㶼���벢�鼯������ֻ��Ҫ����ֵΪ1�ĵ㣬����ֻ��ֵΪ1�ĵ���벢�鼯
	vector<coord> vectorCoord;
	for (int r = 0; r < nr; ++r)
	{
		for (int c = 0; c < nc; ++c)
		{
			if (grid[r][c] == 1)
			{
				vectorCoord.push_back(make_pair(r, c));
			}
		}
	}

	//��ʱ���鼯�м��ϵ�����������grid��ֵΪ1�ĵ�ĸ���
	UnionFind unionFind(vectorCoord);

	int num_islands = 0;
	for (int r = 0; r < nr; ++r)
	{
		for (int c = 0; c < nc; ++c)
		{
			if (grid[r][c] == 1)
			{
				//��ֵ��Ϊ2
				grid[r][c] = 2;
				//���õ����������
				if (r - 1 >= 0 && grid[r - 1][c] == 1)
					//�������Ϻϲ�
					unionFind.unionSet(make_pair(r, c), make_pair(r - 1, c));
				if (r + 1 < nr && grid[r + 1][c] == 1)
					unionFind.unionSet(make_pair(r, c), make_pair(r + 1, c));
				if (c - 1 >= 0 && grid[r][c - 1] == 1)
					unionFind.unionSet(make_pair(r, c), make_pair(r, c - 1));
				if (c + 1 < nc && grid[r][c + 1] == 1)
					unionFind.unionSet(make_pair(r, c), make_pair(r, c + 1));
			}
		}
	}

	return unionFind.GetSetSize();
}

int main()
{
	/*
		0 1 1 0 1 0
		1 1 1 0 1 0
		1 0 0 1 0 0
		0 0 0 0 0 0
	*/

	vector<vector<int>> vectorArray;
	vectorArray.push_back(vector<int>{0, 1, 1, 0, 1, 0});
	vectorArray.push_back(vector<int>{1, 1, 1, 0, 1, 0});
	vectorArray.push_back(vector<int>{1, 0, 0, 1, 0, 0});
	vectorArray.push_back(vector<int>{0, 0, 0, 0, 0, 0});
	cout << "�������� DFS��" << DFS(vectorArray) << endl;
	cout << "�������� ���鼯��" << UseUnionFind(vectorArray) << endl;
	return 0;
}