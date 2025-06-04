
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>


void main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    char buffer[50];
    if(sock<0)
    {
        printf("Socket Creation Failed!!!\n");
        return;
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8000);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(connect(sock,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("Connection Failed!!!\n");
        close(sock);
        return;
    }

    printf("Connected to Server\n");

    send(sock,"start",strlen("start"),0);
    recv(sock,buffer,sizeof(buffer),0);
    printf("%s",buffer);

    while(1)
    {
        if(strcmp(buffer,"Max limit Exceeded!!!\n")==0)
        {
            break;
        }
        printf("Enter your message(stop to exit) :");
        fgets(buffer,sizeof(buffer),stdin);

        send(sock,buffer,sizeof(buffer),0);

        if(strcmp(buffer,"stop\n")==0)
        {
            break;
        }
        memset(buffer,0,sizeof(buffer));
        recv(sock,buffer,sizeof(buffer),0);
        printf("%s",buffer);
    }
    close(sock);
    return;
}

