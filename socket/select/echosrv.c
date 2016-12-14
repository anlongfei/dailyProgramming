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
	int i = 0;
	int num = 0;
	int listenfd;
	listenfd = socket(AF_INET,SOCK_STREAM,0);
  
  struct sockaddr_in servaddr;
	servaddr.sin_port = htons(5188);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr =  htonl(INADDR_ANY);
	if( bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("bind");
	if(listen(listenfd,5) < 0)
		ERR_EXIT("listen");


	int on = 1;
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
		ERR_EXIT("setsockopt err");

	struct sockaddr_in peeraddr;
	socklen_t peerlen = sizeof(peeraddr);
	int client[FD_SETSIZE] = {-1};
	for(i=0; i<FD_SETSIZE; i++)
		client[i] = -1;
	int conn;
	int nready;
	int maxfd = listenfd;
	fd_set rset;
	fd_set allset;
	FD_ZERO(&rset);
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);
	while(1){
		rset = allset;
		nready = select(maxfd+1, &rset, NULL, NULL, NULL);
		if(nready == -1){
			if(errno == EINTR)
				continue;
			ERR_EXIT("select");
		}
		if(nready == 0)
			continue;

		if(FD_ISSET(listenfd, &rset)){
			conn = accept(listenfd, (struct sockaddr *) &peeraddr, &peerlen);
			printf("client:  ip: %s\t\tport: %d\n",inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
			maxfd = maxfd > conn ? maxfd : conn;
			for(i=0; i<FD_SETSIZE; i++){
				if(client[i] == -1){
					printf("set conn\n");
					client[i] = conn;
					break;
				}
			}
			if(i == FD_SETSIZE){
				fprintf(stderr,"too many clients\n");
				exit(EXIT_FAILURE);
			}
			FD_SET(conn, &allset);
			if(--nready <= 0)
				continue;
			
		}
		for(i=0; i<FD_SETSIZE; i++){
			conn = client[i];
			if(conn == -1)
				continue;
			if(FD_ISSET(conn, &rset)){
				char recvbuf[1024];
				memset(recvbuf,0,sizeof(recvbuf));
				//int ret = readline(conn, recvbuf, 1024);
				int ret = read(conn, recvbuf, sizeof(recvbuf));
				if(ret == -1)
					ERR_EXIT("read");
				if(ret == 0){
					printf("client close\n");
					FD_CLR(conn, &allset);
					client[i] = -1;
					close(conn);
					break;
				}
				fputs(recvbuf, stdout);
				write(conn, recvbuf, ret);
				if(--nready <= 0)
					break;
			}
		}
	}
	close(listenfd);
	return 0;
}
