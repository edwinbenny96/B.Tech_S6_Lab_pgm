#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
int main() {
 int sd, i, port = 1234;
 char content[30], fname[30];
 struct sockaddr_in ser;
 if ((sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
 printf("\nError Socket Creation\n");
 return 0;
 }
 bzero((char *)&ser, sizeof(ser));
 ser.sin_family = AF_INET;
 ser.sin_port = htons(port);
 ser.sin_addr.s_addr = htonl(INADDR_ANY);
 if (connect(sd, (struct sockaddr *)&ser, sizeof(ser)) == -1) {
 printf("\nError Connecting to Server.\n");
 return 0;
 }
 printf("\nEnter the name of the file to request: ");
 scanf("%s", fname);
 send(sd, fname, strlen(fname), 0);
 FILE *fp = fopen("received_file", "wb");
 if (fp == NULL) {
 printf("\nError creating the file to store received data.\n");
 close(sd);
 return 0;
 }
 while ((i = recv(sd, content, 30, 0)) > 0) {
 if (strcmp(content, "EOF") == 0)
 break;
 fwrite(content, 1, i, fp);
 printf("%s", content);
 }
 printf("\nFile received and saved as 'received_file'.\n");
 fclose(fp);
 close(sd);
 return 0;
}