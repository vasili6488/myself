// GetHostInfo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WINSOCK2.H>   
#pragma comment(lib,"WS2_32.lib")   
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsd;
	char szHost[256];

	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("WSAStartup failed !\n");
		return 1;
	}
	// 取得本地主机名称//	返回本地主机的标准主机名
	::gethostname(szHost, 256);//缓冲区的长度
	printf("主机名字为：%s \n", szHost);
	// 通过主机名得到地址信息//给定主机名的包含主机名字和地址信息的hostent结构的指针
	hostent* pHost = ::gethostbyname(szHost);
	in_addr addr;
	for (int i = 0;; i++)
	{
		char* p = pHost->h_addr_list[i];
		if (p == NULL)
			break;

		memcpy(&addr.S_un.S_addr, p, pHost->h_length);
		char* szIp = ::inet_ntoa(addr);
		printf(" 本机IP地址：%s  \n ", szIp);
	}
	string name[100];
	printf("请输入想要查找的所有主机名：");
	int i = 0;
	string s;
	do
	{		cin >> s;
		name[i] = s;
		i += 1;
	} while (cin.get() != '\n');//输入多个域名，存储在string 数组name中
	cout << name;
	for (int j = 0; j < i; j++)
	{
		hostent* pHost1 = ::gethostbyname(name[j].c_str());
		for (int i = 0;; i++)
		{
			char* p = pHost1->h_addr_list[i];
			if (p == NULL)
				break;
			memcpy(&addr.S_un.S_addr, p, pHost1->h_length);
			char* szIp = ::inet_ntoa(addr);
			printf(" %s服务器IP地址为：%s  \n ", name[j].c_str(), szIp);
		}
	}
	system("pause");
	WSACleanup();
	return 0;
}