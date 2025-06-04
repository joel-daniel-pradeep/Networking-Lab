#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
struct sockets{  
   int sock_id;
}sockets[10];
int length=0;

void *handle_client(void *arg){
    int client_socket=*(int*)arg;
    free(arg);
    char buffer[50];
    int word_count=0;
    memset(buffer,0,sizeof(buffer));
    if(recv(client_socket,&buffer,sizeof(buffer),0)<0){
       printf("receive failed\n");
       close(client_socket);
       return NULL;
    }
    printf("%s\n",buffer);
    if(strcmp(buffer,"start")==0){
       printf("server communication started\n");
       send(client_socket,"server communication started",sizeof("server communication started"),0);
       }
     else{
        printf("invalid start command\n");
        send(client_socket,"Invalid Start command!!\n",strlen("Invalid Start command!!\n"),0);
        close(client_socket);
        exit(0);
    }
    while(1){
      memset(buffer,0,sizeof(buffer));
      if(recv(client_socket,&buffer,sizeof(buffer),0)<0){
       printf("receive failed\n");
       close(client_socket);
       return NULL;
    }
    char msg[1024];
    for(int j = 0; j < length; j++) {
    if(sockets[j].sock_id == client_socket) {
        sender_index = j;
        break;
    }
}

// Then use sender_index in the message
for (int i=0; i<length; i++) {
    if (sockets[i].sock_id != client_socket) {
        memset(msg,0,sizeof(msg));
        snprintf(msg, sizeof(msg), "Client %d: %s", sender_index, buffer);
        //                                      ↑
        //                              Now shows sender's number
        send(sockets[i].sock_id, msg, strlen(msg), 0);
    }
}
    
    
    buffer[strcspn(buffer,"\n")]=0;
    if(strcmp(buffer,"stop")==0){
      send(client_socket,"Connection Terminated\n",strlen("Connection Terminated\n"),0);
            close(client_socket);
            return NULL;
        }
     int words=0;
     char *token=strtok(buffer," ");
     while(token!=NULL){
        words++;
        token=strtok(NULL," ");
      }
      
      
      
      if((word_count+words)>25){
         printf("wordlimit exceeded\n");
         send(client_socket,"Max limit Exceeded!!!\n",strlen("Max limit Exceeded!!!\n"),0);
         close(client_socket);
         return NULL;
      }
      else{
          word_count+=words;
          send(client_socket,"Message Received\n",strlen("Message Received\n"),0);
        }
    }
    close(client_socket);
    return NULL;
}

void main()
{
    int sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0)
    {
        printf("Socket Creation Failed!!!\n");
        return;
    }
    struct sockaddr_in server_addr,client_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8000);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("Binding Failed!!\n");
        close(sock);
        return;
    }
    printf("Binding Succesful!!\n");

    if((listen(sock,5))<0)
    {
        printf("Listening Failed!!\n");
        close(sock);
        return;
    }
    printf("Listening...\n");
    while(1){
      int addr_size=sizeof(client_addr);
      int client_socket=accept(sock,(struct sockaddr*)&client_addr,&addr_size);
      if(client_socket<0)
        {
            printf("Waiting for new connections....\n");
            sleep(5);
            continue;
        }
       printf("New Client Accepted!!\n");
       sockets[length++].sock_id=client_socket;
       
       pthread_t thread_id;
       int *new_sock=malloc(sizeof(int));
       *new_sock=client_socket;
       
       if(pthread_create(&thread_id,NULL,handle_client,new_sock)!=0){
         printf("thread creation failed\n");
         free(new_sock);
         close(client_socket);
       }
       pthread_detach(thread_id);
     }
     close(sock);
     return;
}
