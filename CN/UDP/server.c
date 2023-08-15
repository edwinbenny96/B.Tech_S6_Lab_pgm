#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdbool.h>
#define MAX_MSG_SIZE 30
#define SERVER_PORT 33345
int main()
{
 int sd, len;
 char sendmsg[MAX_MSG_SIZE], recvmsg[MAX_MSG_SIZE];
 struct sockaddr_in servaddr, cliaddr;
 
 sd = socket(AF_INET, SOCK_DGRAM, 0);
 
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 servaddr.sin_port = htons(SERVER_PORT);
 
 bind(sd, (struct sockaddr*)&servaddr, sizeof(servaddr));
 len = sizeof(cliaddr);
 do {
 printf("Received String: ");
 recvfrom(sd, recvmsg, sizeof(recvmsg), 0, (struct sockaddr*)&cliaddr, &len);
 printf("%s\n", recvmsg);
 
 printf("Enter a Message: ");
 fgets(sendmsg, sizeof(sendmsg), stdin);
 len = strlen(sendmsg);
 sendmsg[len - 1] = '\0';
 sendto(sd, sendmsg, strlen(sendmsg) + 1, 0, (struct sockaddr*)&cliaddr,
sizeof(cliaddr));
 } while(strcmp(recvmsg, "exit") != 0);
 
 
 return 0;
}
