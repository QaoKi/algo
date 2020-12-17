#include <iostream>
#include <string>
#include "../ConsistentHashing/ConsistentHashing.h"

using namespace std;

/*
	http://www.zsythink.net/archives/1182
	https://www.cnblogs.com/moonandstar08/p/5405991.html
	https://blog.csdn.net/qq_34672033/article/details/88916789
	����ķ��������ؾ��⣺
		�����кܶ����ݣ�ÿ�����ݶ��� <���������> �ĸ�ʽ������<������10>��<���ģ�11>
		���ڼ�Ⱥ��3̨���������Ϊ0��1��2��
		ÿ�������ù�ϣ���������hashcode��hashcode%3�����������Ӧ�÷ŵ�����������
		��Ϊ���ݻ���0��1��2�Ͼ��ȷֲ���������̨�����洢�����ݴ�С��࣬ʵ�ָ��ؾ���
		��ȡ���ݵ�ʱ��%3�Ժ󿴿�����̨������

		
		�������Ҫ�ӻ���������ͻ���鷳�ˣ���Ϊ������%3������Ҫ%4
		��������%3�ŵ�1�Ż����У�����%4������1�����Ҳ�����
		��������ӻ�����ÿһ�����ݶ��������㣬����Ǩ�����ܴ�

		�ؼ��������ڣ������������䶯��ʱ��Ҫ�ܹ���֤�ɵ������ܹ������ϵ��㷨��
		���㵽�������ڵķ����������µ������ܹ������µ�ɢ���㷨��������������ڵķ�����
		һ���Թ�ϣ�ṹ���԰�����Ǩ�ƵĴ��۽��ͣ����һ���ʵ�ָ��ؾ���

		һ���Թ�ϣ��
			����ĳ��ϣ����H��hashcode��4λ�ֽڣ�һ��32λ�����Ա�ʾ0 ~ 2^32-1��Χ���޷���������
			��ϣֵ�ķ�Χ����0 ~ 2^32-1����������ϣֵ�ռ���֯��һ�������Բ����2^32 -1 ����һ��ֵ��0

			�����ͣ�
			https://www.cnblogs.com/moonandstar08/p/5405991.html
			http://www.zsythink.net/archives/1182

			���ؾ������⣺һ���Թ�ϣ�㷨�ڷ���ڵ�̫��ʱ��������Ϊ�ڵ�ֲ������ȶ����������б����
				Ϊ�˽������������б���⣬һ���Թ�ϣ�㷨����������ڵ����		

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

	//ģ��һ���ͻ���
	string clientIp = "192.168.56.1:12345";
	ServerNode *serverNode = csshash.getServerNodee(clientIp);
	cout << clientIp << " hashֵ��" << csshash.calculateHashCode(clientIp) << " -> " << serverNode->GetServerName() << endl;

	clientIp = "10.1.0.194:12345";
	serverNode = csshash.getServerNodee(clientIp);
	cout << clientIp << " hashֵ��" << csshash.calculateHashCode(clientIp) << " -> " << serverNode->GetServerName() << endl;
	return 0;
}