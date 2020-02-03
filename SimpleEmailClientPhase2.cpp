#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h> 
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int main(int argc,char* argv[]){
	if(argc!=4){
		cout<< "usage" <<endl;
		exit(1);}
	else{
		char mseg[13+strlen(argv[2])+strlen(argv[3])+1];
		strcpy (mseg, (string("User: ") + argv[2] + " Pass: " + argv[3] + "\0").c_str());
		char buffer[1024] = {0};
		char buf[1024] = {0};
		int sock;
		
		char *ipp = argv[1];
		int pos = string(ipp).find(':');
		string ip = string(ipp).substr(0,pos);
		string p = string(ipp).substr(pos+1);
		stringstream geek(p);
		int x = 0;
		geek >> x;
		struct sockaddr_in dest_addr;
		sock = socket (PF_INET, SOCK_STREAM, 0);
		dest_addr.sin_family = AF_INET;
		dest_addr.sin_port = htons(x);
		inet_aton(ip.c_str(),&(dest_addr.sin_addr));
		memset(&(dest_addr.sin_zero), '\0', 8); // zero the rest of the struct
		int conn = connect(sock, (struct sockaddr*)&dest_addr, sizeof(struct sockaddr));
		if(conn==-1){
			cerr<<"connection to server fails"<<endl;
			exit(2);
		}
		else 
			cout <<"ConnectDone:"<<argv[1]<<endl;

		send(sock, mseg,strlen(mseg)+1,0);
		recv(sock, buffer,100,0);
		if(string(buffer)=="Invalid User"){
			close(sock);
		}
		else if(string(buffer)=="Wrong Passwd"){
			close(sock);
		}
		else{
		cout<<buffer<<endl;
        string y= "LIST";
		send(sock,y.c_str(),1024,0);
		recv(sock,buffer,1024,0);
		cout<<buffer;
		//bzero(buffer,1024);
		//bzero(buf,1024);
		char q[5]="quit";
		send(sock,q,strlen(q)+1,0);
		close(sock);
		}
	}
		return 0;

}

		
		







