#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

void send_command(int sock, char msg[])
{
    send(sock, msg, strlen(msg), 0);
    printf("Client: %s\n", msg);

    char response[1024];
    recv(sock, response, sizeof(response), 0);
    printf("Server: %s\n", response);

}

void main()
{
    char buffer[1024], msg[2048];
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sock < 0)
    {
        printf("Socket creation failed!!!\n");
        return;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("Connection Failed!!!\n");
        close(sock);
        return;
    }
    printf("Connected to Server...\n");
    printf("enter domain\n");
    scanf("%s",buffer);
    snprintf(msg,sizeof(msg),"HELO %s",buffer);
    send_command(sock,msg);
    printf("enter sender\n");
    scanf("%s",buffer);
    snprintf(msg,sizeof(msg),"MAIL FROM: %s",buffer);
    send_command(sock,msg);
    printf("enter receiver\n");
    scanf("%s",buffer);
    snprintf(msg,sizeof(msg),"TO: %s",buffer);
    send_command(sock,msg);
    
    while(getchar()!='\n');
    
    printf("enter message\n");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0; 
    snprintf(msg,sizeof(msg),"MSG: %s",buffer);
    send_command(sock,msg);
    
    send_command(sock,"QUIT");
    
    close(sock);
    
    
 }
