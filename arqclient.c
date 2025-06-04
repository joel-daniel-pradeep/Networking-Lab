#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#define n 4
void stop_and_wait(int sockid){
   char message[100],buffer[100];
   while(1){
   
     printf("enter a message: (exit to stop)\n");
     scanf("%s",message);
     if(strcmp(message,"exit")==0){
        break;
     }
     int attempts=0;
     while(1){
        send(sockid,message,sizeof(message),0);
        printf("Sent:%s\n",message);
        if(recv(sockid,buffer,sizeof(buffer),0)>0&& strcmp(buffer,"ACK")==0){
           printf("ACK received\n");
           break;
        }
        printf("timeout or packet loss, simulating retransmission,attempts:%d\n",attempts+1);
     }
  }
}

void go_back_n(int sockid){
     char message[100],buffer[100];
     int base=0,ack;
     while(1){
        printf("enter the base value:\n");
        scanf("%d",&base);
        if(base==-1){
           break;
        }
       do{
        ack=0;
        for(int i=0;i<n;i++){
           sprintf(message,"Frame%d",base+i);
           send(sockid,message,sizeof(message),0);
           printf("sent:%s\n",message);
           memset(buffer,0,sizeof(buffer));
           if(recv(sockid,buffer,sizeof(buffer),0)>0){
              printf("Ack recevied for frame %d\n",base+i);
              ack++;
           }
        }
        if(ack<n){
            printf("error ,retransmitting:\n");
        }
       }while(ack<n);
     }
 }
 
 void selective_repeat(int sockid){
    char message[100],buffer[100];
    int base=0;
    while(1){
       int received_acks[n]={0};
       printf("enter the base value:\n");
       scanf("%d",&base);
       if(base==-1){
          break;
       }
       for(int i=0;i<n;i++){
          sprintf(message,"Frame%d",base+i);
          send(sockid,message,sizeof(message),0);
          printf("sent: %s\n",message);
          memset(buffer,0,sizeof(buffer));
          if(recv(sockid,buffer,sizeof(buffer),0)>0){
              int ack_num=atoi(buffer+4);
              received_acks[ack_num-base]=1;
              printf("ack received for frame %d\n", base+i);
          }
       }
       int f=0;
       do{
          f=0;
          for(int i=0;i<n;i++){
             if(!received_acks[i]){
                f=1;
                sprintf(message,"Frame%d",base+i);
                send(sockid,message,sizeof(message),0);
                printf("sent: %s\n",message);
                memset(buffer,0,sizeof(buffer));
                if(recv(sockid,buffer,sizeof(buffer),0)>0){
                  int ack_num=atoi(buffer+4);
                  received_acks[ack_num-base]=1;
                  printf("ack received for frame %d\n", base+i);
                }
            }
         }
      }while(f==1);
}}

void main(){
   int sockid;
    struct sockaddr_in server;
    
    sockid = socket(AF_INET, SOCK_STREAM, 0);
    if (sockid == -1) 
    {
        printf("Socket creation failed\n");
        return;
    }
    printf("Successfully created socket: %d\n", sockid);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8000);

    if (connect(sockid, (struct sockaddr*)&server, sizeof(server)) < 0) 
    {
        printf("Connection failed\n");
        return;
    }
    printf("Connected to server.\n");

    struct timeval timeout;
    timeout.tv_sec = 3;
    timeout.tv_usec = 0;
    setsockopt(sockid, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

    int choice;
    while (1)
    {
        printf("\n--- MENU ---\n");
        printf("1. Stop-and-Wait ARQ\n");
        printf("2. Go-Back-N ARQ\n");
        printf("3. Selective Repeat ARQ\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: stop_and_wait(sockid); break;
            case 2: go_back_n(sockid); break;
            case 3: selective_repeat(sockid); break;
            case 4: close(sockid); return;
            default: printf("Invalid choice!\n");
        }
    }
}



           
        
        
   
