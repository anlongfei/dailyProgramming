#define _GNU_SOURCE 1
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <vector>
#include <iostream>
using namespace std;

typedef std::vector<struct epoll_event> eventlist;

#define ERR_EXIT(m) \
	do	\
{ \
	perror(m); \
	exit(EXIT_FAILURE); \
} while(0)



int setnonblocking( int fd )
{
	int old_option = fcntl( fd, F_GETFL );
	int new_option = old_option | O_NONBLOCK;
	fcntl( fd, F_SETFL, new_option );
	return old_option;
}

int main( int argc, char* argv[] )
{
	int num = 0;
	int ret = 0;

	const char* ip = "127.0.0.1";
	int port = 5188;

	struct sockaddr_in address;
	bzero( &address, sizeof( address ) );
	address.sin_family = AF_INET;
	inet_pton( AF_INET, ip, &address.sin_addr );
	address.sin_port = htons( port );

	int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
	assert( listenfd >= 0 );

	//设置端口复用
	int flag = 1,len = sizeof(int);
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &flag, len) == -1)
		ERR_EXIT("setsockopt!");

	ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
	assert( ret != -1 );

	ret = listen( listenfd, 5 );
	assert( ret != -1 );

	int epollfd = epoll_create1(EPOLL_CLOEXEC);
	struct epoll_event event;
	event.data.fd = listenfd;
	event.events = EPOLLIN | EPOLLET;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &event);

	eventlist  events(16);
	struct sockaddr_in peeraddr;
	socklen_t peerlen;
	int connfd;
	int i;
	int nready;
	while( 1 )
	{
		nready = epoll_wait(epollfd, &*events.begin(), events.size(), -1 );
		if ( nready == -1 )
		{
			if(errno == EINTR)
				continue;
			printf( "poll failure\n" );
			break;
		}

		if(nready == 0)
			continue;
		if(nready == events.size())
			events.resize(events.size()*2);

		for(int i = 0; i < nready; i++){
			if(events[i].data.fd == listenfd){
				peerlen = sizeof(peeraddr);
				connfd = accept(listenfd,(struct sockaddr *) &peeraddr, &peerlen);
				if(connfd == -1)
					ERR_EXIT("accept");
				cout << "num : "<< num++ << "\tip: " << inet_ntoa(peeraddr.sin_addr) << "  port: " << ntohs(peeraddr.sin_port) << endl;

				event.data.fd = connfd;
				event.events = EPOLLIN;
				epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &event);
			}
			else if(events[i].events & EPOLLIN){
				connfd = events[i].data.fd;
				if(connfd < 0)
					continue;
				char buf[1024] = {0};
				int ret = read(connfd, buf, 1024);
				if(ret == -1)
					ERR_EXIT("read\n");
				if(ret == 0){
					cout << "client close !" << endl;
					close(connfd);
					event = events[i];
					epoll_ctl(epollfd, EPOLL_CTL_DEL, connfd, &event);
				}
				fputs(buf, stdout);
				write(connfd, buf, strlen(buf));
			}
		}
	}

	close( listenfd );
	return 0;
}
