// GetHostInfo.cpp : �������̨Ӧ�ó������ڵ㡣
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
	// ȡ�ñ�����������//	���ر��������ı�׼������
	::gethostname(szHost, 256);//�������ĳ���
	printf("��������Ϊ��%s \n", szHost);
	// ͨ���������õ���ַ��Ϣ//�����������İ����������ֺ͵�ַ��Ϣ��hostent�ṹ��ָ��
	hostent* pHost = ::gethostbyname(szHost);
	in_addr addr;
	for (int i = 0;; i++)
	{
		char* p = pHost->h_addr_list[i];
		if (p == NULL)
			break;

		memcpy(&addr.S_un.S_addr, p, pHost->h_length);
		char* szIp = ::inet_ntoa(addr);
		printf(" ����IP��ַ��%s  \n ", szIp);
	}
	string name[100];
	printf("��������Ҫ���ҵ�������������");
	int i = 0;
	string s;
	do
	{		cin >> s;
		name[i] = s;
		i += 1;
	} while (cin.get() != '\n');//�������������洢��string ����name��
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
			printf(" %s������IP��ַΪ��%s  \n ", name[j].c_str(), szIp);
		}
	}
	system("pause");
	WSACleanup();
	return 0;
}