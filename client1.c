#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

void main(){

    struct sockaddr_in saddr;
    int client=socket(AF_INET,SOCK_STREAM,0);
    if(client<0){
       printf("error creating socket:\n");
       return;
    }
    
    printf("socket created successfully, socket id:%d\n",client);
    
    saddr.sin_family=AF_INET;
    saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    saddr.sin_port=htons(8000);
    
    if(connect(client,(struct sockaddr *)&saddr,sizeof(saddr))<0){
       printf("connection to server failed:\n");
       close(client);
       return;
    }
    
    printf("connection established successfully:\n");
    
    int len,arr[10];
    printf("enter the array length\n");
    scanf("%d",&len);
    if(send(client,&len,sizeof(len),0)<0){
       printf("error sending array length:\n:");
       close(client);
       return;
    }
    printf("array length sent successfully:\n");
    printf("enter the array:\n");
    for(int i=0;i<len;i++){
      scanf("%d",&arr[i]);
    }
    
    if(send(client,arr,len*sizeof(int),0)<0){
       printf("error sending the array:\n");
       close(client);
       return;
    }
    printf("array sent successfully:\n");
    
    if(recv(client,arr,len*sizeof(int),0)<0){
       printf("error receiving sorted array:\n");
       close(client);
       return;
    }
    
    printf("received sorted array:\n");
    for(int i=0;i<len;i++){
       printf("%d\t",arr[i]);
    }
    printf("\n");
    close(client);
 }
    
    
