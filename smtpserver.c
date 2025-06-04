#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
void handle_client(int client){
   char buffer[1024],sender[100]="",receiver[100]="",msg[1024]="";
   while(1){
      memset(buffer,0,sizeof(buffer));
      int bytes_recvd=recv(client,buffer,strlen(buffer)-1,0);
      if(bytes_recvd<=0){
        printf("client disconnected\n");
        close(client);
        return;
      }
      buffer[bytes_recvd]='\0';
      printf("Client:%s\n",buffer);
      if(strncmp(buffer,"HELO ",5)==0){
         send(client,"HELLO,your request received",strlen("HELLO,your request received"),0);
      }
      else if(strncmp(buffer,"MAIL FROM: ",11)==0){
          strncpy(sender,buffer+11,sizeof(sender)-1);
          sender[sizeof(sender)-1]='\0';
          send(client,"from address received",strlen("from address received"),0);
      }
      else if(strncmp(buffer,"TO: ",4)==0){
          strncpy(receiver,buffer+4,sizeof(receiver)-1);
          sender[sizeof(receiver)-1]='\0';
          send(client,"to address received",strlen("to address received"),0);
      }
      else if(strncmp(buffer,"MSG: ",5)==0){
          strncpy(msg,buffer+5,sizeof(msg)-1);
          msg[sizeof(msg)-1]='\0';
          send(client,"message received",strlen("message received"),0);
      }
      else if(strcmp(buffer,"QUIT")==0){
          printf("from:%s\nto:%s\nmessage:%s\n",sender,receiver,msg);
          send(client,"Quit received,closing connection",sizeof("Quit received,closing connection"),0);
          close(client);
          break;
      }
      else{
         send(client, "Unknown command", strlen("Unknown command"), 0);
      }
   }
 }
 
 
void main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        printf("Socket creation failed!\n");
        return;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("Bind failed!\n");
        close(sock);
        return;
    }

    if (listen(sock, 5) < 0)
    {
        printf("Listening failed!\n");
        close(sock);
        return;
    }

    printf("SMTP Server Listening on Port 8080...\n");

    struct sockaddr_in client_addr;
    int clen = sizeof(client_addr);

    int client_sock = accept(sock, (struct sockaddr*)&client_addr, &clen);
    if (client_sock < 0)
    {
        printf("Accept failed\n");
        close(sock);
        return;
    }
    printf("Connected to client...\n");

    handle_client(client_sock); 

    close(sock);
    return;
}

   
