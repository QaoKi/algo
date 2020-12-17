#ifndef _CONSISTENT_HASHING_H_
#define _CONSISTENT_HASHING_H_

#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

//服务器节点
class ServerNode
{
public:
    ServerNode(string strServerName, int iVirtualNodeCount);
    ~ServerNode();
    int GetVirtualNodeCount();
    string GetServerName();

private:
    string _strServerName;
    int _iVirtualNodeCount;
};

//一致性哈希
class ConsistentHashing
{
public:
    ConsistentHashing();
    ~ConsistentHashing();

    //用服务器的ip计算哈希值
    void addServerNode(string strServerName, int iVirtualNodeCount);
    void delServerNode(string strServerName);

    //根据client找对应的server
    ServerNode *getServerNodee(string strClientName);
    //获取真实节点个数
    int getRealNodeCount();
    //获取某个真实节点的虚拟节点个数
    int getVirtualNodeCount(string strServerName);
    //获取所有节点数量
    int getAllNodeCount();

    //统计环上所有节点分布情况（供测试使用）
    string statDist();

    //计算哈希值
    unsigned int calculateHashCode(string strServerName);

private:
    /*
        key为服务器ip的hashcode，在根据客户端hashcode查找可以访问的服务器节点时，
        需要服务器的hashcode是有序的，所以使用map，而不是使用unordered_map
    */
    map<unsigned int, ServerNode *> _mapAllServerNode;
    //保存真实的节点，方便最终释放所有节点
    set<ServerNode *> _setRealServerNode;
};

#endif