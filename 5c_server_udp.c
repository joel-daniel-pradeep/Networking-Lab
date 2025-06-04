#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<math.h>
void main(){
   int server;
   struct sockaddr_in saddr,caddr1,caddr2;
   server=socket(AF_INET,SOCK_DGRAM,0);
   if(server<0){
     printf("socket creation failed\n");
     return;
   }
   saddr.sin_family=AF_INET;
   saddr.sin_port=htons(8000);
   saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
   if(bind(server,(struct sockaddr*)&saddr,sizeof(saddr))<0){
     printf("binding failed..\n");
     close(server);
     return;
   }
   char msg[50];
   float a,sq;
   int clen=sizeof(caddr1);
   if(recvfrom(server,&a,sizeof(a),0,(struct sockaddr*)&caddr1,&clen)<0){
     printf("receiving failed\n");
     close(server);
     return;
   }
   printf("received no succesfully\n");
   sq=pow(a,1.5);
   int clen2=sizeof(caddr2);
   if(recvfrom(server,&msg,sizeof(msg),0,(struct sockaddr*)&caddr2,&clen2)<0){
     printf("receiving failed\n");
     close(server);
     return;
   }
   if(sendto(server,&sq,sizeof(sq),0,(struct sockaddr *)&caddr2,sizeof(caddr2))<0){
     printf("sending failed\n");
     close(server);
     return;
   }
   printf("powered value sent successfully\n");
   close(server);
}
