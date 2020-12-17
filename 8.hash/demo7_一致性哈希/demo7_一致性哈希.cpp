#include <iostream>
#include <string>
#include "../ConsistentHashing/ConsistentHashing.h"

using namespace std;

/*
	http://www.zsythink.net/archives/1182
	https://www.cnblogs.com/moonandstar08/p/5405991.html
	https://blog.csdn.net/qq_34672033/article/details/88916789
	经典的服务器负载均衡：
		假设有很多数据，每条数据都是 <姓名，年纪> 的格式，比如<张三，10>，<李四，11>
		现在集群有3台机器，编号为0，1，2，
		每条数据用哈希函数计算出hashcode，hashcode%3求出这条数据应该放到哪条机器上
		因为数据会在0，1，2上均匀分布，所以三台机器存储的数据大小差不多，实现负载均衡
		获取数据的时候，%3以后看看在哪台机器上

		
		但是如果要加机器，处理就会很麻烦了，因为本来是%3，现在要%4
		张三本来%3放到1号机器中，但是%4不等于1，就找不到了
		所以如果加机器，每一条数据都得重新算，数据迁移量很大

		关键问题在于，服务器数量变动的时候，要能够保证旧的数据能够按照老的算法，
		计算到数据所在的服务器，而新的数据能够按照新的散列算法，计算出数据所在的服务器
		一致性哈希结构可以把数据迁移的代价降低，并且还能实现负载均衡

		一致性哈希：
			假设某哈希函数H的hashcode有4位字节，一共32位，可以表示0 ~ 2^32-1范围的无符号整数，
			哈希值的范围就是0 ~ 2^32-1，将整个哈希值空间组织成一个虚拟的圆环，2^32 -1 的下一个值是0

			见博客：
			https://www.cnblogs.com/moonandstar08/p/5405991.html
			http://www.zsythink.net/archives/1182

			负载均衡问题：一致性哈希算法在服务节点太少时，容易因为节点分部不均匀而造成数据倾斜问题
				为了解决这种数据倾斜问题，一致性哈希算法引入了虚拟节点机制		

*/

int main()
{
	ConsistentHashing csshash;
	csshash.addServerNode("192.168.0.1:8080", 2);
	csshash.addServerNode("192.168.0.2:8859", 3);
	csshash.addServerNode("10.0.1.56:80", 2);
	csshash.addServerNode("10.0.1.57:80", 3);
	csshash.addServerNode("192.168.1.101:8080", 1);
	cout << "all server node: " << csshash.getAllNodeCount() << endl;
	cout << csshash.statDist() << endl;

	//模拟一个客户端
	string clientIp = "192.168.56.1:12345";
	ServerNode *serverNode = csshash.getServerNodee(clientIp);
	cout << clientIp << " hash值：" << csshash.calculateHashCode(clientIp) << " -> " << serverNode->GetServerName() << endl;

	clientIp = "10.1.0.194:12345";
	serverNode = csshash.getServerNodee(clientIp);
	cout << clientIp << " hash值：" << csshash.calculateHashCode(clientIp) << " -> " << serverNode->GetServerName() << endl;
	return 0;
}