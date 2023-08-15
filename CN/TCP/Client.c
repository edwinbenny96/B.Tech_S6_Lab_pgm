#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdbool.h>
int main()
{
 int csd, len;
 char sendmsg[30], recvmsg[30]; 
 struct sockaddr_in cliaddr, servaddr;
 
 csd = socket(AF_INET, SOCK_STREAM, 0);
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 servaddr.sin_port = htons(33345);
 
 connect(csd, (struct sockaddr*)&servaddr, sizeof(servaddr));
 
 do
 {
 printf("\nEnter a Message: ");
 fgets(sendmsg, sizeof(sendmsg), stdin); 
 
 len = strlen(sendmsg);
 sendmsg[len - 1] = '\0';
 
 send(csd, sendmsg, strlen(sendmsg) + 1, 0); 
 
 printf("\nReceived String: ");
 recv(csd, recvmsg, sizeof(recvmsg), 0); 
 printf("%s\n", recvmsg);
 }while (strcmp(recvmsg, "exit") != 0);
 
 return 0;
}