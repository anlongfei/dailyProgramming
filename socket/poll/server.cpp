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
#include <poll.h>
#include <vector>
#include <iostream>
using namespace std;

#define USER_LIMIT 5
#define BUFFER_SIZE 64
#define FD_LIMIT 65535

typedef std::vector<struct pollfd> pollfdlist;

#define ERR_EXIT(m) \
	do	\
{ \
	perror(m); \
	exit(EXIT_FAILURE); \
} while(0)



struct client_data
{
    struct sockaddr_in address;
    char* write_buf;
    char buf[ BUFFER_SIZE ];
};

int setnonblocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return old_option;
}

int main( int argc, char* argv[] )
{
    const char* ip = "127.0.0.1";
    int port = 5188;
	int num = 0;

    int ret = 0;
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

	struct pollfd pfd;
	pfd.fd = listenfd;
	pfd.events = POLLIN;

	pollfdlist pollfds;
	pollfds.push_back(pfd);

	int nready;

	struct sockaddr_in peeraddr;
	socklen_t peerlen;
	int connfd;


	while( 1 )
	{
		nready = poll( &*pollfds.begin(), pollfds.size(), -1 );
		if ( nready == -1 )
		{
			if(errno == EINTR)
				continue;
			printf( "poll failure\n" );
			break;
		}

		if(nready == 0)
			continue;
		if(pollfds[0].revents & POLLIN){
			peerlen = sizeof(peeraddr);
			connfd = accept(listenfd,(struct sockaddr *) &peeraddr, &peerlen);

			if(connfd == -1)
				ERR_EXIT("accept");

			pfd.fd = connfd;
			pfd.events = POLLIN;
			pfd.revents = 0;
			pollfds.push_back(pfd);
			--nready;

			cout << "num : " << num++ << "\t ip = " << inet_ntoa(peeraddr.sin_addr) << " port= "  << ntohs(peeraddr.sin_port) << endl;

			if(nready == 0)
				continue;
		}
		for(pollfdlist::iterator it = pollfds.begin()+1; it != pollfds.end() && nready > 0; it++){
			if(it->revents & POLLIN){
				--nready;
				connfd = it->fd;
				char buf[1024] = {0};
				int ret = read(connfd, buf, 1024);
				if(ret == -1)
					ERR_EXIT("read!");
				if(ret == 0){
					cout << "client closed" << endl;
					it = pollfds.erase(it);
					--it;

					close(connfd);
					continue;
				}

				cout << buf;
				write(connfd, buf, strlen(buf));
			}
		}
	}

	close( listenfd );
	return 0;
}
