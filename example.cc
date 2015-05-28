#include "connector.h"

#include<iostream>
using namespace std;

int main(){
	int fd = connect("localhost",3720);

	send(fd,"RED");
	cout<<"received color: \""<<receive(fd)<<"\""<<endl;

	send(fd,"M653262226 4288924BB5 727165B452 73334BFBB3");

	cout<<"received confirmation: \""<<receive(fd)<<"\""<<endl;

	cout<<"received start/wait: \""<<receive(fd)<<"\""<<endl;

	disconnect(fd);
}
