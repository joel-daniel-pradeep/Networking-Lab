#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void main(){
   int client;
   struct sockaddr_in saddr;
   client=socket(AF_INET,SOCK_STREAM,0);
   if(client<0){
     printf("socket creation failed\n");
     return;
   }
   saddr.sin_family=AF_INET;
   saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
   saddr.sin_port=htons(8000);
   if(connect(client,(struct sockaddr*)&saddr,sizeof(saddr))<0){
      printf("connection failed\n");
      close(client);
      return;
   }
   printf("connection successful\n");
   float a ;
   printf("enter the float value\n");
   scanf("%f",&a);
   if(send(client,&a,sizeof(a),0)<0){
     printf("failed to send the value to server\n");
     close(client);
     return;
   }
   printf("sent the float successfully to the server\n");
   close(client);
}
