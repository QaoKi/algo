#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "../UnionFind/UnionFind.h"
using namespace std;

/*
https://www.cnblogs.com/SkyeAngel/p/8953007.html

	岛问题：
		一个矩阵中只有0和1两种值，每个位置都可以和自己的上、下、左、右
		四个位置相连，如果有一片1连在一起，这个部分叫做一个岛，求一个
		矩阵中有多少个岛？

		举例：
			0 1 1 0 1 0
			1 1 1 0 1 0
			1 0 0 1 0 0
			0 0 0 0 0 0

		这个矩阵中有三个岛。
*/

/*
	DFS:
		两层循环，遍历每个节点，只要节点的值为1，就进入感染函数 infect(),infect()递归把这个节点
		包括它周围的1都变成2，同时岛的数量加1，如上面的例子中，第一次遍历到(0,1)坐标的1时，进入
		infect()，把周围的都变成2，岛的数量加1，直到遍历结束
					0 2 2 0 1 0
					2 2 2 0 1 0
					2 0 0 1 0 0
					0 0 0 0 0 0
		时间复杂度:最坏情况，所有的数据都是1，那么对所有的数据要遍历两遍，复杂度为O(2*N*M)
		所以时间复杂度为O(N*M)

	扩展：假如我们现在这个岛很大，那么有没有什么方法快速求解
		分治：
			将一个大矩阵化成多个小矩阵，最后将不同的矩阵合并，
			合并的时候借助并查集处理边界问题，将边界上连成一片的1合并
					0 1 1  1 1 0
					1 1 1  1 1 0
					1 0 0  1 0 0
					0 0 1  1 0 1
		把整个矩阵分成两块，分别计算岛数量，左边的岛2个，右边的岛2个，
		运用并查集结构，第一次查看到1的位置在(0,1)位置，把这个点，作为这个岛的代表节点，假设
		记为A，则(0,2)(1,0)(1,1)(1,2)(2,0)位置都属于这个岛，代表节点都为A，右下角的岛的代表节点为B

		同理，右边矩阵中，第一个岛的代表节点为C，右下角岛的代表节点为D

		现在开始合并，两个小矩阵一共得到4个岛，4个代表节点
		只需要处理边界上的节点，在(0,2)位置和(0,3)位置，两个1合并，左边的代表节点为A，右边的
		代表节点为C，不一样，那么岛的数量减1，让A和C合并
		在(1,2)位置和(1,3)位置，两个1合并，左边代表节点为A，右边也为A，不用管
		在(2,2)位置为0，(2,3)位置为1，不用管
		在(3,2)位置和(3,3)位置，两个1合并，左边的代表节点为B，右边的
		代表节点为A，不一样，那么岛的数量减1，让A和B合并

		最后得到岛的数量为2
*/

//简单版：用DFS
void infect(vector<vector<int>> &vectorArray, int i, int j)
{
	//当节点越界，或节点的值不为1，结束递归
	if (i < 0 || i >= vectorArray.size() || j < 0 || j >= vectorArray[i].size() || vectorArray[i][j] != 1)
		return;

	vectorArray[i][j] = 2; //将值改为2或者0
	//递归让节点的上下左右中的1都变成2，如果上下左右的节点中有节点为1，那么再检查该节点的上下左右
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
			//遍历每个点
			if (vectorArray[i][j] == 1)
			{
				ret++;
				infect(vectorArray, i, j);
			}
		}
	}

	return ret;
}

//扩展：
int UseUnionFind(vector<vector<int>> grid)
{
	int nr = grid.size();
	if (!nr)
		return 0;
	int nc = grid[0].size();

	//如果某坐标的值为1，就把该坐标作为一个独立集合放入并查集
	//不用把所有的点都放入并查集，我们只需要处理值为1的点，所以只把值为1的点放入并查集
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

	//此时并查集中集合的数量，就是grid中值为1的点的个数
	UnionFind unionFind(vectorCoord);

	int num_islands = 0;
	for (int r = 0; r < nr; ++r)
	{
		for (int c = 0; c < nc; ++c)
		{
			if (grid[r][c] == 1)
			{
				//将值变为2
				grid[r][c] = 2;
				//检查该点的上下左右
				if (r - 1 >= 0 && grid[r - 1][c] == 1)
					//两个集合合并
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
	cout << "岛的数量 DFS：" << DFS(vectorArray) << endl;
	cout << "岛的数量 并查集：" << UseUnionFind(vectorArray) << endl;
	return 0;
}