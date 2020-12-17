#pragma once
#include <string>
#include <map>
#include <set>
#include "Edge.h"
#include "Node.h"
using namespace std;
class Graph
{
public:
	Graph();
	~Graph();

public:
	Node* GetGraph(int arr[8][3]);

public:
	map<int, Node*> nodes;
	set<Edge*> edges;

};

