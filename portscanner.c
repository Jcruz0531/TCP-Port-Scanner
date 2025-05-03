#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h> 
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>

int IsPortOpen(const char *ip, int port){

int sockfd;
struct sockaddr_in target; 
struct timeval timeout;
fd_set fdset;

sockfd = socket(AF_INET, SOCK_STREAM, 0);

if(sockfd < 0) {
    return 0;
}

fcntl(sockfd, F_SETFL, O_NONBLOCK);

target.sin_family = AF_INET;
target.sin_port = htons(port);

inet_pton(AF_INET, ip, &target.sin_addr);

connect(sockfd, (struct sockaddr *)&target, sizeof(target));

FD_ZERO(&fdset);
FD_SET(sockfd, &fdset);

timeout.tv_sec = 1;
timeout.tv_usec = 0;

if(select(sockfd + 1, NULL, &fdset, NULL, &timeout) == 1) {
    int so_error;
    socklen_t len = sizeof(so_error);
    getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &so_error, &len);
    close(sockfd);
    return so_error == 0;
}

close(sockfd);
return 0; 

}

int main() {

char ip[16];
int startport;
int endport;

printf("Target IP Adress: ");
scanf("%s", ip);

printf("\nStarting Port: ");
scanf("%d", &startport);

printf("\nEnd Port: ");
scanf("%d", &endport);

if(startport < 1 || endport > 65535 || startport > endport) {
    printf("Invalid Entry!\n");
    return 1;
}

printf("Scanning Host: %s, Ports %d - %d\n", ip, startport, endport);

for(int port = startport; port<= endport; port++) {
    if(IsPortOpen(ip, port)) {
        printf("Port %d Is Open!\n", port);
    }
}

printf("Scan Complete!\n");
return 0;

}
