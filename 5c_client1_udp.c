#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<math.h>
void main(){
   int client;
   struct sockaddr_in saddr;
   client=socket(AF_INET,SOCK_DGRAM,0);
   if(client<0){
     printf("socket creation failed\n");
     return;
   }
   saddr.sin_family=AF_INET;
   saddr.sin_port=htons(8000);
   saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
   
   
   float a;
   printf("enter the value:\n");
   scanf("%f",&a);
   if(sendto(client,&a,sizeof(a),0,(struct sockaddr*)&saddr,sizeof(saddr))<0){
     printf("sending failed\n");
     close(client);
     return;
   }
   printf("Sent successfully\n");
   close(client);
}
