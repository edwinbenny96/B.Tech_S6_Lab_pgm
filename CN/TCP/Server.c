#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdbool.h>
int main()
{
 int sd, len, nsd, clilen;
 char sendmsg[30], recvmsg[30]; 
 struct sockaddr_in cliaddr, servaddr;
 
 sd = socket(AF_INET, SOCK_STREAM, 0);
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 servaddr.sin_port = htons(33345);
 
 bind(sd, (struct sockaddr*)&servaddr, sizeof(servaddr));
 listen(sd, 5);
 
 clilen = sizeof(cliaddr);
 nsd = accept(sd, (struct sockaddr*)&cliaddr, &clilen);
 
 do
 {
 printf("\nReceived String: ");
 recv(nsd, recvmsg, sizeof(recvmsg), 0); 
 printf("%s\n", recvmsg);
 
 printf("\nEnter a Message: ");
 fgets(sendmsg, sizeof(sendmsg), stdin); 
 
 len = strlen(sendmsg);
 sendmsg[len - 1] = '\0';
 
 send(nsd, sendmsg, strlen(sendmsg) + 1, 0); 
 }while (strcmp(recvmsg, "exit") != 0);
 
 return 0;
}
