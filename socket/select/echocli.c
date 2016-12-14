#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>

#define ERR_EXIT(m) \
	do \
	{ \
		perror(m);  \
		exit(EXIT_FAILURE); \
	}while(0)

int main(int argc, char* argv[]){
	int servfd;
	servfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_port = htons(5188);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr =  inet_addr("127.0.0.1");

	socklen_t servlen = sizeof(servaddr);
	if(connect(servfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("connnect");

	char sendbuf[1024] = {0};
	char recvbuf[1024] = {0};
	while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL){
		
		write(servfd, sendbuf, sizeof(sendbuf));
		read(servfd, recvbuf, sizeof(recvbuf));
		
		fputs(recvbuf, stdout);

		memset(recvbuf, 0, sizeof(recvbuf));
		memset(sendbuf, 0, sizeof(sendbuf));
	}

}
