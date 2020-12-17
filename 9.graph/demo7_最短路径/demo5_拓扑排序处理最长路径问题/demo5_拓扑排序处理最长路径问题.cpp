#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include "../../Edge.h"
#include "../../OrientedWeightedGraph/OrientedWeightedGraph.h"

using namespace std;

/*
	�޻�����ͼ�еĵ����·��������һ���޻���Ȩ����ͼ���ߵ�Ȩ�ؿ���Ϊ��������һ�����s���ҵ���s�������ɴﶥ���
	�·����

	ʵ�֣�
		��demo4�����·�����⣬��Ϊ����⣬��relax()������ �� < ��Ϊ >
	�ܽ᣺
		��һ��ļ�Ȩ����ͼ���ߵ�Ȩ�ؿ���Ϊ������Ѱ���·������֪����㷨�������������ʱ����ָ�������
*/

/*
	���ܽ��ƽ������������⣬�㷨���İ棨p430��
*/

/*
	ʱ�临�Ӷȣ���������ʱ�临�Ӷ�Ϊ O(E + V)���ٱ���һ�����еĶ��㣬ÿ���߶�ֻ�ᱻ�ɳ�һ��
		�����ܵ�ʱ�临�Ӷ�Ϊ O(E + V)
*/

void relax(OrientedWeightedGraph &weightedGraph, Node *node, map<Node *, int> &distTo, map<Node *, Node *> &edgeTo)
{

	/*
		����Ƿ���distTo[node]�����û�У�˵��distTo[node]������󣬴Ӷ���s���ܴﵽnode����ônode�Ͳ���������
		��Ϊ����Ҫ��ģ��Ǵ�s�������ɴﵽ�Ķ�������·���������ڳ�ʼ����ʱ��ֻ��ʼ���� distTo[s] = 0;
		ֻ��nodeΪs��ʱ�򣬲ŻῪʼ�ɳڲ���
	*/
	if (distTo.find(node) == distTo.end())
		return;
	for (auto it = weightedGraph._mapOrientedWeightedGraph[node].begin(); it != weightedGraph._mapOrientedWeightedGraph[node].end(); it++)
	{
		//��ɱߣ�����Ҳ�У�ֻ��Ϊ�˴����������
		Edge edge(node, it->first, it->second);
		//�����ɳڲ���
		if (distTo.find(edge._to) == distTo.end() || distTo[edge._to] < distTo[edge._from] + edge._weight)
		{
			distTo[edge._to] = distTo[edge._from] + edge._weight;
			edgeTo[edge._to] = edge._from;
		}
	}
}