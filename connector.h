#pragma once
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <string>
#include <cstring>
#include <cassert>

static int fd=-1;

void connect(std::string host, int port){
	// create socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0) fd=-2;

	// find host
	hostent* server = gethostbyname(host.c_str());
	if(server==NULL) fd=-3;

	// connect
	sockaddr_in serv_addr;
	memset(&serv_addr,0,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);
	serv_addr.sin_port = htons(port);

	int status = connect(sockfd,(sockaddr *) &serv_addr,sizeof(serv_addr));
	if(status<0) fd=-4;

	fd = sockfd;
}

void send(std::string message){
	assert(fd>=0);
	write(fd,&message[0],message.size());
}

// Caution! may return multiple concatenated messages.
std::string receive(){
	assert(fd>=0);

	std::string ret(256,0);
	int bytes_read = read(fd,&ret[0],256);
	ret.resize(bytes_read);

	return ret;
}

void disconnect(){
	assert(fd>=0);
	close(fd);
}

