#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void main(){
   
     struct sockaddr_in saddr;
     int client=socket(AF_INET,SOCK_DGRAM,0);
     if(client<0){
       printf("error in socket creation\n");
       return;
     }
     printf("socket created successfully, socket id : %d\n",client);
     printf("sending message to server\n");
     saddr.sin_family=AF_INET;
     saddr.sin_port=htons(8000);
     saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
     while(1){
     
         char buffer[50]="time";
         if(sendto(client,buffer,sizeof(buffer),0,(struct sockaddr *)&saddr,sizeof(saddr))<0){
            printf("failed to send message to server\n");
            continue;
         }
         
         printf("message sent successfully to server\n");
         printf("waiting for time from server..\n");
         int slen=sizeof(saddr);
         if(recvfrom(client,buffer,sizeof(buffer),0,(struct sockaddr *)&saddr,&slen)<0){
            printf("failed to receive time from server\n");
            continue;
         }
         printf("time received : %s from server\n",buffer);
         sleep(5);
     }
     close(client);
     return;
}
