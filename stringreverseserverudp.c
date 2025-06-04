#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void main(){
    struct sockaddr_in saddr,caddr;
    int server=socket(AF_INET,SOCK_DGRAM,0);
    if(server<0){
       printf("error in creating socket\n");
       return;
    }
    
    printf("socket created successfully, socket id: %d\n",server);
    saddr.sin_family=AF_INET;
    saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    saddr.sin_port=htons(8000);
    
    if(bind(server,(struct sockaddr *)&saddr,sizeof(saddr))<0){
       printf("binding failed!\n");
       close(server);
       return;
    }
    
    char buffer[50];
    int clen=sizeof(caddr);
    if(recvfrom(server,buffer,sizeof(buffer),0,(struct sockaddr *)&caddr,&clen)<0){
        printf("failed to receive string\n");
        close(server);
        return;
    }
    
    printf("received string:%s\n",buffer);
    char rev[50];
    for(int i=0,j=strlen(buffer)-1;j>=0;j--,i++){
        rev[i]=buffer[j];
    }
    rev[strlen(rev)]='\0';
    if(recvfrom(server,buffer,sizeof(buffer),0,(struct sockaddr *)&caddr,&clen)<0){
        printf("failed to receive message\n");
        close(server);
        return;
    }
    if(sendto(server,rev,sizeof(rev),0,(struct sockaddr *)&caddr,sizeof(caddr))<0){
             printf("sending failed:\n");
             close(server);
             return;
             
    }
    
    printf("message sent to client 2\n");
    
    close(server);
    return;
 }
    
