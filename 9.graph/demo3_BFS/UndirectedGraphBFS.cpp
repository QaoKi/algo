#include "UndirectedGraphBFS.h"
#include <queue>
#include <stack>
void UndirectedGraphBFS::printf(Node *start)
{
    if (start == NULL)
        return;
    /*
		set是为了防止节点重复加入队列，比如1指向3，遍历1所指向的节点，会把2,3,4加入队列中
		而2也指向3，遍历2所指向的节点，也会遍历到3，如果不用set判断是否已经加过了，那么队列会出现重复节点
	*/
    set<Node *> setNode;
    queue<Node *> queueNode;
    queueNode.push(start);
    setNode.insert(start);

    while (!queueNode.empty())
    {
        //从队列中取一个值打印
        Node *curr = queueNode.front();
        queueNode.pop();
        cout << curr->_data << "  ";

        //遍历取出来的节点，它指向的所有节点加入到队列中，相当于按层遍历
        for (auto it = _mapUndirectedGraph[curr].begin(); it != _mapUndirectedGraph[curr].end(); ++it)
        {
            //如果在集合中没有找到这个node,就加入到队列和集合中
            if (setNode.find(*it) == setNode.end())
            {
                //在遍历的同时，记录前一个节点
                _mapNodePaths[*it] = curr;
                queueNode.push(*it);
                setNode.insert(*it);
            }
        }
    }
}

void UndirectedGraphBFS::printfAllPaths(Node *start)
{
    //先填充 _mapNodePaths
    printf(start);
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

void UndirectedGraphBFS::printfPathsStartToEnd(Node *start, Node *end)
{
    //先填充 _mapNodePaths
    printf(start);
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