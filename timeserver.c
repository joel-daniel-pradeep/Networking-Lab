#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<time.h>
void main(){
  struct sockaddr_in saddr,caddr;
  int server=socket(AF_INET,SOCK_DGRAM,0);
  if(server<0){
     printf("error in socket creation\n");
     return;
  }
  printf("socket created successfully, socket id : %d\n",server);
  saddr.sin_family=AF_INET;
  saddr.sin_port=htons(8000);
  saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
  if(bind(server, (struct sockaddr *)&saddr, sizeof(saddr)) < 0){
    perror("Bind failed");
    close(server);
    return;
  }
  printf("binding sucessful\n");

  while(1){
          printf("server waiting for message from client\n");
	  int clen=sizeof(caddr);
	  char buffer[50];
	  if(recvfrom(server,buffer,sizeof(buffer),0,(struct sockaddr *)&caddr,&clen)<0){
	     printf("error in receiving the message from client\n");
	     close(server);
	     return;
	  }
	  printf("message received successfully from client:\n");
	  printf("sending time to client...\n");
	  time_t cur_time=time(NULL);
	  snprintf(buffer,sizeof(buffer),"%s",ctime(&cur_time));
	  
	  if(sendto(server,buffer,sizeof(buffer),0,(struct sockaddr *)&caddr,sizeof(caddr))<0){
	       printf("failed to send time to client\n");
	       continue;
	   }
	   printf("current time ; %s sent successfully\n",buffer);
        }
  close(server);
  return;
 }
	  
