#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
int main() {
 int sd, nsd, i, port = 1234;
 char content[30], fname[30];
 struct sockaddr_in ser, cli;
 FILE *fp;
 if ((sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
 printf("\nError Socket Creation\n");
 return 0;
 }
 bzero((char *)&ser, sizeof(ser));
 printf("\nThe Port Address is: %d\n", port);
 ser.sin_family = AF_INET;
 ser.sin_port = htons(port);
 ser.sin_addr.s_addr = htonl(INADDR_ANY);
 if (bind(sd, (struct sockaddr *)&ser, sizeof(ser)) == -1) {
 printf("\nError Binding\n");
 return 0;
 }
 i = sizeof(cli);
 listen(sd, 1);
 nsd = accept(sd, (struct sockaddr *)&cli, &i);
 if (nsd == -1) {
 printf("\nError Accepting Client.\n");
 return 0;
 }
 printf("\nClient Accepted\n");
 i = recv(nsd, fname, 30, 0);
 fname[i] = '\0';
 fp = fopen(fname, "rb");
 if (fp == NULL) {
 printf("\nFile not found.\n");
 close(nsd);
 close(sd);
 return 0;
 }
 while ((i = fread(content, 1, 30, fp)) > 0) {
 send(nsd, content, i, 0);
 }
 send(nsd, "EOF", 4, 0);
 printf("\nFile Transferred.\n");
 fclose(fp);
 close(nsd);
 close(sd);
 return 0;
}
