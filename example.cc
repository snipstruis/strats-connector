#include "connector.h"

#include<iostream>
using namespace std;

int main(){
	connect("localhost",3720);

	send("RED");
	cout<<"received color: \""<<receive()<<"\""<<endl;

	send("M653262226 4288924BB5 727165B452 73334BFBB3");

	cout<<"received confirmation: \""<<receive()<<"\""<<endl;

	cout<<"received start/wait: \""<<receive()<<"\""<<endl;

	disconnect();
}
