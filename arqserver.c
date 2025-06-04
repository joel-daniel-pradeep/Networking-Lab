#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<string.h>

#define n 4
void main(){
   struct sockaddr_in saddr,caddr;
   char buffer[100], ack[100];
   int server=socket(AF_INET,SOCK_STREAM,0);
   if(server<0){
      printf("error creating socket\n");
      return;
   }
   printf("socket created successfully,server id :%d\n",server);
   saddr.sin_family=AF_INET;
   saddr.sin_port=htons(8000);
   saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
   
   if(bind(server,(struct sockaddr *)&saddr,sizeof(saddr))<0){
      printf("error binding\n");
      close(server);
      return;
   }
   printf("binding successful\n");
   if(listen(server,5)<0){
     printf("error listening\n");
     close(server);
     return;
   }
   printf("server listening...\n");
   int clen=sizeof(caddr);
   int isock=accept(server,(struct sockaddr *)&caddr,&clen);
   if(isock<0){
     printf("error accepting connection\n");
     close(server);
     return;
   }
   printf("connection accepted..\n");
   
   while(1){
     memset(buffer,sizeof(buffer),0);
     int rdval=read(isock,buffer,sizeof(buffer));
     if(rdval<0){
         printf("Client Disconnected\n");
         break;
     }
     printf("message received:%s\n",buffer);
     if(rand()%100<30){
       printf("simulating packet loss. ACK not sent\n");
       continue;
     }
     if(strncmp(buffer,"Frame",5)==0){
        sprintf(ack,"ACK %s",buffer+6);
     }
     else{
       strcpy(ack,"ACK");
     }
     send(isock,ack,sizeof(ack),0);
     printf("ACK sent :%s\n",ack);
   }
   close(isock);
   close(server);
   return;
 }
