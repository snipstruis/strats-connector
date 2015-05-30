#include "connector.h"

#include<iostream>
using namespace std;

int main(){
	int r = connect("localhost",3720);
	int b = connect("localhost",3720);
	sendln(r,"RED");
	sendln(b,"BLUE");

	if(receiveln(r)=="RED") cout << "r: I got the color I wanted!\n";
	else	cout << "r: aww, I got blue :(\n";
	if(receiveln(b)=="BLUE") cout << "b: I got the color I wanted!\n";
	else	cout << "b: aww, I got red :(\n";

	sendln(r,"M653262226 4288924BB5 727165B452 73334BFBB3");
	sendln(b,"M653262226 4288924BB5 727165B452 73334BFBB3");
	cout<<"r: \""<<receiveln(r)<<"\""<<endl;
	cout<<"b: \""<<receiveln(b)<<"\""<<endl;
	cout<<"r: \""<<receiveln(r)<<"\""<<endl;
	cout<<"b: \""<<receiveln(b)<<"\""<<endl;
}
