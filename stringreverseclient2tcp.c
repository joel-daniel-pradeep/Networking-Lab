#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
void main()
{
 struct sockaddr_in saddr,caddr;
 int sockfd=socket(AF_INET,SOCK_STREAM,0);
 char str[20];
 if(sockfd==-1)
 {
  printf("Error in socket creation");
  return;
 }

 printf("Socket created with sockfd %d",sockfd);
 caddr.sin_family=AF_INET;
 caddr.sin_port=htons(10001);
 caddr.sin_addr.s_addr=inet_addr("127.0.0.1");
 if(connect(sockfd,(struct sockaddr *)&caddr,sizeof(caddr))==-1){
    printf("\nError in connecting");
    close(sockfd);
    return;
 }
 printf("\nconnected");
 if(recv(sockfd,str,sizeof(str),0)==-1){
   printf("\nError in receiving");
   close(sockfd);
   return;
 }
 else
 {
 printf("\nData received from server is %s",str);
 }
}
