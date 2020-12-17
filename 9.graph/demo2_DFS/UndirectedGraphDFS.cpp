#include "UndirectedGraphDFS.h"
#include <stack>

void UndirectedGraphDFS::printf()
{
    /*
		set是为了防止节点重复遍历，比如1指向3，遍历1所指向的节点，会遍历到3.
		而2也指向3，遍历2所指向的节点，也会遍历到3，如果不用set判断是否已经遍历过，那么会重复遍历，如果是连通图，会死循环
	*/
    set<Node *> setNode;
    /*
        找出所有与根节点相连通的节点。也就是根节点所在的连通量的所有节点
        但是有的节点可能和根节点不连通
    */
    printfHelp(_nodeRoot, setNode);
}

void UndirectedGraphDFS::printfHelp(Node *node, set<Node *> &setNode)
{
    if (node == NULL)
        return;
    cout << node->_data << "  ";
    setNode.insert(node);

    for (auto it = _mapUndirectedGraph[node].begin(); it != _mapUndirectedGraph[node].end(); it++)
    {
        if (setNode.find(*it) == setNode.end())
        {
            //在遍历的同时，记录前一个节点
            _mapNodePaths[*it] = node;
            printfHelp(*it, setNode);
        }
    }
}

int UndirectedGraphDFS::printfAllNodes()
{
    /*
        上面的printf()函数，是输出所有与根节点相连通的节点，
        但是有的节点不和根节点相连通，所有要遍历所有的节点，进行dfs
        这样同时也能求出连通量的数量
    */
    int count;
    set<Node *> setNode;
    for (auto it = _mapUndirectedGraph.begin(); it != _mapUndirectedGraph.end(); it++)
    {
        if (setNode.find(it->first) == setNode.end())
        {
            printfHelp(it->first, setNode);
            count++;
        }
    }

    return count;
}

void UndirectedGraphDFS::printf_noRecursion()
{
    if (_nodeRoot == NULL)
        return;
    //自己使用栈，不让系统出压栈
    stack<Node *> stackNode;
    set<Node *> setNode;

    cout << _nodeRoot->_data << "  ";
    setNode.insert(_nodeRoot);
    stackNode.push(_nodeRoot);

    while (!stackNode.empty())
    {
        Node *curr = stackNode.top();
        stackNode.pop();
        //遍历curr的邻接点，选择一条路，一直走到头
        for (auto it = _mapUndirectedGraph[curr].begin(); it != _mapUndirectedGraph[curr].end(); it++)
        {
            if (setNode.find(*it) == setNode.end())
            {
                setNode.insert(*it);
                //先把当前节点放入栈中
                stackNode.push(curr);
                //再把下一节点放入栈中，这样回溯的时候，先出来的是下一节点
                stackNode.push(*it);
                /*
                    上面的入栈操作，不用担心会加入重复节点，因为每次都是先取出一个节点再选择一条路
                    如果有疑惑，画一个图
                */
                cout << (*it)->_data << "  ";
                //选择了一条路，沿着这条路走到头，走到头了回溯，如果不break，变成广度的了
                break;
            }
        }
    }
}

void UndirectedGraphDFS::printfAllPaths(Node *start)
{
    //先填充 _mapNodePaths
    set<Node *> setNode;
    printfHelp(start, setNode);
    cout << endl;

    for (auto it = _mapUndirectedGraph.begin(); it != _mapUndirectedGraph.end(); it++)
    {
        Node *curr = it->first;
        cout << start->_data << " to " << curr->_data << ": ";

        //start 和curr节点是否连通，如果是连通的，那么_mapNodePaths中含有key为curr的项
        if (_mapNodePaths.find(curr) == _mapNodePaths.end())
        {
            cout << " not path" << endl;
            continue;
        }

        //因为查找的顺序是反着查，使用栈让数据正序
        stack<Node *> stackNode;
        //反向一直找到start
        while (curr != start)
        {
            stackNode.push(curr);
            curr = _mapNodePaths[curr];
        }

        cout << start->_data;
        while (!stackNode.empty())
        {
            Node *curr = stackNode.top();
            stackNode.pop();
            cout << "->" << curr->_data;
        }
        cout << endl;
    }
}

void UndirectedGraphDFS::printfPathsStartToEnd(Node *start, Node *end)
{
    //先填充 _mapNodePaths
    set<Node *> setNode;
    printfHelp(start, setNode);
    cout << endl;

    /*
        要先检查 start节点和end节点是否连通
        _mapNodePaths 被填充了以后，如果两个节点是连通的，
        那么 _mapNodePaths.find(end) != _mapNodePaths.end();
    */

    if (_mapNodePaths.find(end) == _mapNodePaths.end())
    {
        cout << start->_data << " not path to " << end->_data << endl;
        return;
    }

    cout << start->_data << " to " << end->_data << ": ";
    //因为查找的顺序是反着查，使用栈让数据正序
    stack<Node *> stackNode;
    //反向一直找到start
    Node *curr = end;
    while (curr != start)
    {
        stackNode.push(curr);
        curr = _mapNodePaths[curr];
    }

    cout << start->_data;
    while (!stackNode.empty())
    {
        Node *curr = stackNode.top();
        stackNode.pop();
        cout << "->" << curr->_data;
    }
    cout << endl;
}