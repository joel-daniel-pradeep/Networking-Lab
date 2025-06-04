#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void main(){
   int client=socket(AF_INET,SOCK_STREAM,0);
   struct sockaddr_in saddr;
   if(client<0){
     printf("socket creation failed\n");
     return;
   }
   saddr.sin_family=AF_INET;
   saddr.sin_port=htons(8000);
   saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
   if(connect(client,(struct sockaddr*)&saddr,sizeof(saddr))<0){
     printf("connection failed\n");
     close(client);
     return;
   }
   float sq;
   if(recv(client,&sq,sizeof(float),0)<0){
      printf("receiving failed\n");
      close(client);
      return;
   }
   printf("received square value:%f\n",sq);
   close(client);
}
