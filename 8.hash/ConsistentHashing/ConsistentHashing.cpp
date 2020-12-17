#include "ConsistentHashing.h"
#include "md5.h"
#include <sstream>
//服务器节点
ServerNode::ServerNode(string strServerName, int iVirtualNodeCount)
{
    _strServerName = strServerName;
    _iVirtualNodeCount = 0;
    if (iVirtualNodeCount > 0)
        _iVirtualNodeCount = iVirtualNodeCount;
}
ServerNode::~ServerNode() {}

int ServerNode::GetVirtualNodeCount()
{
    return _iVirtualNodeCount;
}

string ServerNode::GetServerName()
{
    return _strServerName;
}

//一致性哈希
ConsistentHashing::ConsistentHashing() {}

ConsistentHashing::~ConsistentHashing()
{
    auto itNode = _setRealServerNode.begin();
    for (; itNode != _setRealServerNode.end(); itNode++)
    {
        ServerNode *server = *itNode;
        delete server;
        server = NULL;
    }

    _setRealServerNode.clear();
    _mapAllServerNode.clear();
}

void ConsistentHashing::addServerNode(string strServerName, int iVirtualNodeCount)
{
    unsigned int hashCode = calculateHashCode(strServerName);
    if (_mapAllServerNode.find(hashCode) != _mapAllServerNode.end())
        return;

    ServerNode *newNode = new ServerNode(strServerName, iVirtualNodeCount);

    //增加真实节点
    _mapAllServerNode.insert(make_pair(hashCode, newNode));
    _setRealServerNode.insert(newNode);

    //增加虚拟节点
    stringstream ss;
    //虚拟节点name后面加后缀
    for (int i = 0; i < iVirtualNodeCount; ++i)
    {
        string strVirtualName;
        ss << strServerName << "##" << i + 1;
        ss >> strVirtualName;
        ss.clear();
        unsigned int hashCode = calculateHashCode(strVirtualName);
        _mapAllServerNode.insert(make_pair(hashCode, newNode));
    }
}

ServerNode *ConsistentHashing::getServerNodee(string strClientName)
{
    //根据客户端的ip找到可以提供服务的节点
    ServerNode *serverNode = NULL;
    unsigned int clientHashCode = calculateHashCode(strClientName);
    auto it = _mapAllServerNode.begin();
    /* 找到第一个比 clientHashCode 大的节点 */
    for (; it != _mapAllServerNode.end(); it++)
    {
        if (clientHashCode < it->first)
        {
            serverNode = it->second;
            break;
        }
    }

    //当没找到时，可能是因为客户端的hashcode太大，返回第一个server节点
    if (it == _mapAllServerNode.end())
        serverNode = _mapAllServerNode.begin()->second;

    return serverNode;
}

void ConsistentHashing::delServerNode(string strServerName)
{
    unsigned int hashCode = calculateHashCode(strServerName);
    auto itRealNode = _mapAllServerNode.find(hashCode);
    if (itRealNode == _mapAllServerNode.end())
        return;

    ServerNode *serverNode = itRealNode->second;
    //删除该节点的所有虚拟节点
    int iVirtualNodeCount = serverNode->GetVirtualNodeCount();
    stringstream ss;
    //虚拟节点name后面加后缀
    for (int i = 0; i < iVirtualNodeCount; ++i)
    {
        string strVirtualName;
        ss << strServerName << "##" << i + 1;
        ss >> strVirtualName;
        ss.clear();
        unsigned int virtualHashCode = calculateHashCode(strVirtualName);
        auto itVirtual = _mapAllServerNode.find(virtualHashCode);
        if (itVirtual != _mapAllServerNode.end())
            _mapAllServerNode.erase(itVirtual);
    }

    //删除真实节点
    _mapAllServerNode.erase(itRealNode);
    _setRealServerNode.erase(serverNode);

    delete serverNode;
    serverNode = NULL;
}

int ConsistentHashing::getRealNodeCount()
{
    return _setRealServerNode.size();
}

int ConsistentHashing::getVirtualNodeCount(string strServerName)
{
    unsigned int hashCode = calculateHashCode(strServerName);
    auto itRealNode = _mapAllServerNode.find(hashCode);
    if (itRealNode == _mapAllServerNode.end())
        return 0;
    return itRealNode->second->GetVirtualNodeCount();
}

int ConsistentHashing::getAllNodeCount()
{
    return _mapAllServerNode.size();
}

string ConsistentHashing::statDist()
{
    //max = 2^32 = 4294967296
    //所以分8个区 500000000 1000000000 1500000000 ---
    int i = 1;
    unsigned int sum = 0;
    std::ostringstream oss;
    for (auto it = _mapAllServerNode.begin(); it != _mapAllServerNode.end();)
    {
        if (it->first / 500000000 < i)
        {
            ++sum;
            ++it;
        }
        else
        {
            oss << "hash( " << i - 1 << ", " << i << " )million   nodeNum = " << sum << "\n";
            ++i;
            sum = 0;
        }
    }
    return oss.str();
}

unsigned int ConsistentHashing::calculateHashCode(string strServerName)
{
    MD5 md5(strServerName);
    const unsigned char *digest = md5.getDigest(); //16个字节
    unsigned int hash = 0;
    /* 
		每四个字节构成一个32位整数，将四个32位整数相加得到hash值
        或者把 digest 转为整数，%(2^32)，余数为哈希值
        反正是让hash值在 0 ~ (2^32)-1 之间，也就是 0 ~ 最大的4字节int值，也就是任意一个4字节的 int 值
	*/
    for (int i = 0; i < 4; i++)
    {
        hash += ((unsigned int)(digest[i * 4 + 3] & 0xFF) << 24) | ((unsigned int)(digest[i * 4 + 2] & 0xFF) << 16) | ((unsigned int)(digest[i * 4 + 1] & 0xFF) << 8) | ((unsigned int)(digest[i * 4 + 0] & 0xFF));
    }
    return hash;
}