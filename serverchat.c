#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

void handle_client(int client_sock){
    char buffer[50];
    int word_count=0;
    memset(buffer,0,sizeof(buffer));
    if(recv(client_sock,&buffer,sizeof(buffer),0)<0){
        printf("receive failed!\n");
        close(client_sock);
        return;
    }
    printf("%s\n",buffer);
    if(strcmp(buffer,"start")==0){
        printf("server communication started!\n");
        send(client_sock,"Server communication Started!\n",strlen("Server communication Started!\n"),0);
    }
    else{
       printf("invalid start command!\n");
       send(client_sock,"invalid start command!\n",strlen("invalid start command!\n"),0);
       close(client_sock);
       exit(0);
    }
    while(1){
       memset(buffer,0,sizeof(buffer));
       if(recv(client_sock,&buffer,sizeof(buffer),0)<0){
        printf("receive failed!\n");
        close(client_sock);
        return;
    }
    buffer[(strcspn(buffer,"\n"))]=0;
    printf("%s\n",buffer);
    if(strcmp(buffer,"stop")==0){
       send(client_sock,"connection terminated\n",strlen("connection terminated\n"),0);
       close(client_sock);
       return;
    }
    int words=0;
    char *token=strtok(buffer," ");
    while(token!=NULL){
        words++;
        token=strtok(NULL," ");
    }
    
    if((word_count+words)>25)
        {
            send(client_sock,"Max limit Exceeded!!!\n",strlen("Max limit Exceeded!!!\n"),0);
            close(client_sock);
            return;
        }
        else{
            word_count+=words;
            memset(buffer,0,sizeof(buffer));
            printf("enter your message:\n");  
            fgets(buffer,sizeof(buffer),stdin);
           
            send(client_sock,buffer,strlen(buffer),0);
        }
    }
    close(client_sock);
    return;
}

void main(){
   struct sockaddr_in saddr,caddr;
   int sock=socket(AF_INET,SOCK_STREAM,0);
   if(sock<0){
      printf("socket creation failed!\n");
      return;
   }
   saddr.sin_family=AF_INET;
   saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
   saddr.sin_port=htons(8000);
   
   if(bind(sock,(struct sockaddr *)&saddr,sizeof(saddr))<0){
     printf("binding failed!\n");
     close(sock);
     return;
   }
   
   if(listen(sock,5)<0){
     printf("listening failed!\n");
     close(sock);
     return;
   }
   printf("server listening,,\n");
   
   while(1){
     int addr_size=sizeof(caddr);
     int client_sock=accept(sock,(struct sockaddr *)&caddr,&addr_size);
     if(client_sock<0){
         printf("waiting for new connections..\n");
         sleep(5);
         continue;
     }
     printf("new client accepted\n");
     if(fork()==0){
        close(sock);
        handle_client(client_sock);
     }
     close(client_sock);
   }
   close(sock);
   return;
}   
       
           
