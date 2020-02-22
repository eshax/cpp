#include <winsock2.h>
#include <stdio.h>
#include <string.h>

#define SIZE 1024

int main(int argc, char**argv)
{
    int             n;
    WSADATA         wd;
    SOCKET          s;
    SOCKADDR_IN     addr;
    unsigned short  port = 9999;
    char            sd[SIZE];
    char            rd[SIZE];

    if((n = WSAStartup(MAKEWORD(2,2), &wd)) != 0)
        return 0;

    if((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
        return 0;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    if((connect(s, (SOCKADDR*)&addr, sizeof(addr))) == SOCKET_ERROR)
    {
        closesocket(s);
        return 0;
    }

    while(true)
    {
        printf("\n:");
        scanf("%s", sd);
        if(strcmp(sd, "quit") == 0){
            break;
		}

        if(send(s, sd, SIZE, 0) == SOCKET_ERROR)
        {
            break;
        }

        n = recv(s, rd, SIZE, 0);
        if(n > 0){
            printf(":%s\n", rd);
		}
        else
        {
            break;
        }
    }
    shutdown(s, SD_BOTH);
    closesocket(s);

    if(WSACleanup() == SOCKET_ERROR)
    {
        return 0;
    }

    system("pause");
    return 0;
}