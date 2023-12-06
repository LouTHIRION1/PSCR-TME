#include "Socket.h"
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

namespace pr {

void Socket::close(){
	if(fd!=-1){
		shutdown(fd, 1);
		::close(fd); // on va chercher le close() à la racine des namespace
	}
}

void Socket::connect(const std::string &host, int port) {
	struct addrinfo *addr;
	if(getaddrinfo(host.c_str(), nullptr, nullptr, &addr) != 0){
		perror("getaddrinfo error");
		return;
	}
	in_addr ipv4 = ((struct sockaddr_in *) addr->ai_addr)->sin_addr;
	freeaddrinfo(addr);
	connect(ipv4, port);
}

void Socket::connect(in_addr ipv4, int port){
	sockaddr_in dest;
	dest.sin_family = AF_INET;
	dest.sin_addr = ipv4;
	dest.sin_port = htons(port); // conversion host to network short
	fd = socket(AF_INET, SOCK_STREAM,0);
	if(fd<0) {
		perror("error socket");
		return;
	}
	if(::connect(fd, (struct sockaddr *) &dest, sizeof dest) < 0){
		perror("connect");
		::close(fd);
		fd = -1;
		return;
	}
}

}