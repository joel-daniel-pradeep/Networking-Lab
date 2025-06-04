#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
void rev(char * buf)
{
int i,j;
char t;
i=0;
j=strlen(buf)-1;
while(i<j)
{
t=buf[i];
buf[i]=buf[j];
buf[j]=t;
i++;
j--;
}
printf("\nRev is %s",buf);

}
void main()
{
 struct sockaddr_in saddr,caddr;
 int sockfd=socket(AF_INET,SOCK_STREAM,0);
 char buf[20];
 if(sockfd==-1)
 {
  printf("Error in socket creation");
  return;
 }  
 printf("Socket created with sockfd %d",sockfd);
 saddr.sin_family=AF_INET;
 saddr.sin_port=htons(10001);
 saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
 if(bind(sockfd,(struct sockaddr *)&saddr,sizeof(saddr))==-1){
     printf("\nError in binding");
     close(sockfd);
     return;
 }
 
 printf("\nbinding successful");
 if(listen(sockfd,5)==-1)
 {
  printf("\nListening error");
  close(sockfd);
  return;
 }
 printf("\nListening");
 int clen=sizeof(caddr);
 int isock=accept(sockfd,(struct sockaddr *)&caddr,&clen);
 if(isock==-1)
 {
  printf("\nError in accepting");
 }
 printf("\nAccepted");
 
 if(recv(isock,buf,sizeof(buf),0)==-1){
    printf("\nError in receiving");
    close(sockfd);
    return;
 }

 printf("\nData received is %s",buf);
 rev(buf);
 close(isock);



  clen=sizeof(caddr);
  isock=accept(sockfd,(struct sockaddr *)&caddr,&clen);
 if(isock==-1)
 {
  printf("\nError in accepting client2");
  close(sockfd);
  return;
 }
 
 printf("\nAccepted");
 if(send(isock,buf,sizeof(buf),0)==-1){
  printf("\nError in sending rev");
  close(sockfd);
  return;
 }
 else
 {
  printf("\ndata sent");
 }
}
