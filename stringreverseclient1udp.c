#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void main(){
    struct sockaddr_in saddr;
    int client=socket(AF_INET,SOCK_DGRAM,0);
    if(client<0){
       printf("error in creating socket\n");
       return;
    }
    
    printf("socket created successfully, socket id: %d\n",client);
    saddr.sin_family=AF_INET;
    saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    saddr.sin_port=htons(8000);
    char buffer[50];
    printf("enter a message\n");
    scanf("%s",buffer);
    if(sendto(client,buffer,sizeof(buffer),0,(struct sockaddr *)&saddr,sizeof(saddr))<0){
       printf("message sending failed\n");
       close(client);
       return;
    }
    printf("message sent to server\n");
    close(client);
    return;
 }
