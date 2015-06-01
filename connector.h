#pragma once
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <vector>
#include <string>
#include <cstring>
#include <cassert>

int connect(std::string const host, int const port){
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

void clear_readbuf(int const fd){
	static char c;
	while(recv(fd,&c,sizeof(c),MSG_DONTWAIT)>0){};
}

bool send(int const fd, std::string const & message){
	assert(fd>0);
	size_t bytes_left    = message.size();
	size_t bytes_written = 0;
	while(bytes_left > 0){
		int w = write(fd,&message[bytes_written],bytes_left);
		if(w <= 0){
			return false;
		}else{
			bytes_left    -= w;
			bytes_written += w;
		}
	}
	return true;
}

bool sendln(int const fd, std::string const &message){
	return send(fd,message+'\n');
}

std::string receiveln(int const fd){
	assert(fd>=0);

	std::string s="";
	char prev;
	char c = '\n';
	int  bytes_read;
	while(true){
		prev = c;
		bytes_read = read(fd,&c,1);
		//printf("%2X ",(unsigned)c);
		if(bytes_read!=1){
			break;
		}else if(c=='\n') {
			if(prev<=' '){
				s.pop_back();
			} 
			break;
		}else if(c<=' ' && prev<=' '){
			continue;
		}else if( (c>='A'&&c<='Z') || (c>='0'&&c<='9') || c=='#' || c=='.' || c=='~' ){
			s += c;
		}else if( c<=' ' ){
		   	s += ' ';
		}else{
			continue;
		}
	}
	//printf(" (%s)\n",s.c_str());
	return s;
}

void disconnect(int const fd){
	assert(fd>=0);
	close(fd);
}
