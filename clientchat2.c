// client2.c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

void main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    char buffer[50];
    struct sockaddr_in server_addr;

    if(sock < 0) {
        printf("Socket Creation Failed!!!\n");
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Connection Failed!!!\n");
        close(sock);
        return;
    }

    printf("[Client 2] Connected to Server\n");

    send(sock, "start", strlen("start"), 0);
    recv(sock, buffer, sizeof(buffer), 0);
    printf("[Client 2] %s", buffer);

    char *messages[] = {
        "one two three four five six seven eight nine ten\n",
        "eleven twelve thirteen fourteen fifteen sixteen seventeen\n",
        "eighteen nineteen twenty twentyone twentytwo twentythree\n",
        "twentyfour twentyfive twentysix\n"
    };

    for(int i = 0; i < 4; i++) {
        send(sock, messages[i], strlen(messages[i]), 0);
        memset(buffer, 0, sizeof(buffer));
        recv(sock, buffer, sizeof(buffer), 0);
        printf("[Client 2] Server: %s", buffer);
        if(strstr(buffer, "Max limit") != NULL) break;
    }

    close(sock);
}

