#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<math.h>

void main(){
    int server;
    struct sockaddr_in saddr,caddr;
    server=socket(AF_INET,SOCK_STREAM,0);
    if(server<0){
       printf("server socket creation failed\n");
        return;
    }
    printf("server creation successful\n");
    saddr.sin_family=AF_INET;
    saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    saddr.sin_port=htons(8000);
    if(bind(server,(struct sockaddr *)&saddr,sizeof(saddr))<0){
       printf("binding failed\n");
       return;
    }
    printf("binding successful\n");
    if(listen(server,5)<0){ 
       printf("listening failed\n");
       close(server);
       return;
    }
    printf("server listening..\n");
    int clen=sizeof(caddr);
    int isock=accept(server,(struct sockaddr*)&caddr,&clen);
    if(isock<0){
      printf("accept failed\n");
      close(server);
      return;
    }
    float a,sq;
    printf("accepted connection succesfully\n");
    if(recv(isock,&a,sizeof(a),0)<0){
        printf("receiving failed\n");
        close(server);
        close(isock);
        return;
    }
    sq=pow(a,1.5);
    close(isock);
    isock=accept(server,(struct sockaddr*)&caddr,&clen);
    if(isock<0){
      printf("accept failed\n");
      close(server);
      return;
    }
    if(send(isock,&sq,sizeof(sq),0)<0){
       printf("sending unsuccessful\n");
      
       close(isock);
       close(server);
       return;
    }
    printf("powered value sent to cluent 2 succesully\n");
    close(isock);
    close(server);
}
