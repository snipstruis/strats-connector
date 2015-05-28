#pragma once
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <string>
#include <cstring>
#include <cassert>

int connect(std::string host, int port){
	// create socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0) return -1;

	// find host
	hostent* server = gethostbyname(host.c_str());
	if(server==NULL) return -2;

	// connect
	sockaddr_in serv_addr;
	memset(&serv_addr,0,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);
	serv_addr.sin_port = htons(port);

	int status = connect(sockfd,(sockaddr *) &serv_addr,sizeof(serv_addr));
	if(status<0) return -3;

	return sockfd;
}

void send(int fd, std::string message){
	assert(fd>=0);
	write(fd,&message[0],message.size());
}

// Caution! may return multiple concatenated messages.
std::string receive(int fd){
	assert(fd>=0);

	std::string ret(256,0);
	int bytes_read = read(fd,&ret[0],256);
	ret.resize(bytes_read);

	return ret;
}

void disconnect(int fd){
	assert(fd>=0);
	close(fd);
}

