#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>

void main(){
     struct sockaddr_in saddr,caddr;
     int server=socket(AF_INET,SOCK_STREAM,0);
     if(server<0){
        printf("error in socket creation!\n");
        return;
     }
     printf("Server created! Socket id : %d\n",server);
     saddr.sin_family=AF_INET;
     saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
     saddr.sin_port=htons(8000);
     if(bind(server,(struct sockaddr *)&saddr,sizeof(saddr))<0){
           printf("Binding failed!\n");
           close(server);
           return;
     }
     
     if(listen(server,5)<0){
       printf("failed to listen\n");
       close(server);
       return;
     }
     
     printf("server listening for connections....\n");
     int isock;
     int clen=sizeof(caddr);
     isock=accept(server,(struct sockaddr *)&caddr,&clen);
     if(isock<0){
         printf("error accepting connection\n");
         close(server);
         return;
     }
     printf("connection established with client\n");
     
     int len;
     if(recv(isock,&len,sizeof(len),0)<0){
        printf("failed to receive array length\n");
        close(isock);
        close(server);
        return;
     }
     
     printf("array length received successfully:%d\n",len);
     int arr[10];
     if(recv(isock,arr,len*sizeof(int),0)<0){
         printf("failed to receive array data:\n");
         close(isock);
         close(server);
         return;
     }
     printf("array received:\n");
     for(int i=0;i<len;i++){
       printf("%d\t",arr[i]);
     }
     printf("\n");
     int max=arr[0];
     for(int i=1;i<len;i++){
        if(arr[i]>max){
           max=arr[i];
        }
     }
     
     if(send(isock,&max,sizeof(max),0)<0){
       printf("failed to send max element:\n");
       close(isock);
       close(server);
       return;
     }
     printf("sent the max element:\n");
     
     int min=arr[0];
     for(int i=1;i<len;i++){
        if(arr[i]<min){
           min=arr[i];
        }
     }
     
     if(send(isock,&min,sizeof(min),0)<0){
       printf("failed to send min element:\n");
       close(isock);
       close(server);
       return;
     }
     printf("sent the min element:\n");
     
     float avg=0;
     for(int i=0;i<len;i++){
       avg+=arr[i];
     }
     avg/=len;
     if(send(isock,&avg,sizeof(avg),0)<0){
       printf("failed to send avg element:\n");
       close(isock);
       close(server);
       return;
     }
     printf("sent the avg element:\n");
     
     close(isock);
     close(server);
  }
