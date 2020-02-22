#include <winsock2.h>
#include <stdio.h>
#include <string.h>

#define BUFFSIZE 1024

int main(int argc, char**argv)
{
	int             Ret;
	WSADATA         wsaData;
	SOCKET          ListeningSocket;
	SOCKET          NewConnection;
	SOCKADDR_IN     ServerAddr;
	SOCKADDR_IN     ClientAddr;
	int             ClientAddrLen = sizeof(ClientAddr);
	unsigned short  Port = 9999;
	//char            sendData[BUFFSIZE];
	char            recvData[BUFFSIZE];

	if((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
	{
		printf("WSASTARTUP_ERROR: %d\n", Ret);
		return 0;
	}

	if((ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		printf("SOCKET_ERROR: %d\n", INVALID_SOCKET);
		return 0;
	}

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(Port);
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if(bind(ListeningSocket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		printf("BIND_ERROR: %d\n", SOCKET_ERROR);
		return 0;
	}

	if(listen(ListeningSocket, 5) == SOCKET_ERROR)
	{
		printf("LISTEN_ERROR: %d\n", SOCKET_ERROR);
		return 0;
	}

	while(1)
	{
		if((NewConnection = accept(ListeningSocket, (SOCKADDR *)&ClientAddr, &ClientAddrLen)) == INVALID_SOCKET)
		{
			printf("ACCPET_ERROR: %d\n", INVALID_SOCKET);
			closesocket(ListeningSocket);
			return 0;
		}
		printf("%s:%d\n", inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));

		while(1)
		{
			Ret = recv(NewConnection, recvData, BUFFSIZE, 0);
			if(Ret > 0)
			{
				printf("%s:%d\t%s\n", inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port), recvData);
			}
			else
			{
				break;
			}
			if (strcmp(recvData, "get") == 0)
			{
				if(send(NewConnection, "http://www.baidu.com", BUFFSIZE, 0) == SOCKET_ERROR)
					break;
				continue;
			}
			if(strcmp(recvData, "quit") == 0)
			{
				break;
			}
			if(send(NewConnection, recvData, BUFFSIZE, 0) == SOCKET_ERROR)
			{
				break;
			}

		}
		shutdown(NewConnection, SD_BOTH);

		closesocket(NewConnection);
	}
	closesocket(ListeningSocket);

	if(WSACleanup() == SOCKET_ERROR)
	{
		return 0;
	}

	system("pause");
	return 0;
}
