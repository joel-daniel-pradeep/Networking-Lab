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
     int temp;
     for(int i=0;i<len-1;i++){
       for(int j =0;j<len-i-1;j++){
          if(arr[j]>arr[j+1]){
             temp=arr[j];
             arr[j]=arr[j+1];
             arr[j+1]=temp;
           }
        }
     }
     
     if(send(isock,arr,len*sizeof(int),0)<0){
       printf("error sending sorted array:\n");
       close(isock);
       close(server);
       return;
     }
     
     printf("sent the sorted array to client:\n");
     close(isock);
     close(server);
  }
