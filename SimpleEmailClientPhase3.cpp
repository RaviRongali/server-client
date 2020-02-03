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
#include <dirent.h>
#define MAXLINE 4096
using namespace std;
int main(int argc,char* argv[]){
	if(argc!=6){
		cout<< "usage" <<endl;
		exit(1);
	}
		
	else{
		DIR *userdir;

    	userdir = opendir (argv[5]);
    	if(userdir){
    	string k0 = "./";
        string k01 = k0.append(argv[5]);
        string k2 = "/";
        string k3 = "rm ";
        string k1 = "*";
        string nee = k3.append(k01).append(k2).append(k1);
        system(k3.c_str());
        
        string k5 ="rmdir ";
        string k6 = k5.append(argv[5]);
        system(k6.c_str());
    	}

		string w="mkdir ";
		string ww=w.append(argv[5]);
		system(ww.c_str());
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
		else
		cout<<buffer<<endl;
		bzero(buffer,1024);
		bzero(buf,1024);

        





		char *lstm = argv[4];
    	string str = lstm;
    	vector<int> vect;
	    stringstream ss(str);

    	int i;
	    while (ss >> i)
    	{
        	vect.push_back(i);
	        if (ss.peek() == ',')
    	        ss.ignore();
    	}
    
    	for(int ij=0;ij<vect.size();ij++){
    		stringstream sss;
    		sss << vect[ij];
    		string q1 = sss.str();
    		char q[7];
    		strcpy(q,("RETRV " + q1).c_str());
    		//cout<<q<<endl;
    		send(sock,q,strlen(q)+1,0);
   			char port[MAXLINE], buffer1[MAXLINE],filename[MAXLINE],char_num_blks[MAXLINE],char_num_last_blk[MAXLINE],message[MAXLINE];
			int data_port,datasock,lSize,num_blks,num_last_blk,i;
			bzero(port, MAXLINE);
			bzero(buffer1, MAXLINE);
			bzero(filename, MAXLINE);
			bzero(char_num_blks, MAXLINE);
			bzero(char_num_last_blk, MAXLINE);
			FILE *fp;
			recv(sock,message,MAXLINE,0);
			recv(sock,filename,MAXLINE,0);
			if(strcmp("1",message)==0){
			string r = "./";
			string rrr = "/";
			string rr = r.append(argv[5]).append(rrr).append(filename);
			//cout<<filename<<endl;
			if((fp=fopen(rr.c_str(),"w"))==NULL)
				cout<<"Error in creating file\n";
			else
			{
				recv(sock, char_num_blks, MAXLINE,0);
				num_blks=atoi(char_num_blks);
				for(int ii= 0; ii < num_blks; ii++) { 
					recv(sock, buffer1, MAXLINE,0);
					fwrite(buffer1,sizeof(char),MAXLINE,fp);
					//cout<<buffer<<endl;
				}
				recv(sock, char_num_last_blk, MAXLINE,0);
				num_last_blk=atoi(char_num_last_blk);
				if (num_last_blk > 0) { 
					recv(sock, buffer1, MAXLINE,0);
					fwrite(buffer1,sizeof(char),num_last_blk,fp);
					//cout<<buffer<<endl;
				}
				//system("mkdir ravi");
				
				fclose(fp);
				cout<<"Downloaded Message "<<vect[ij]<<endl;
			}
		}
		else{
			cout<<"NO such file"<<endl;
		}
	}








		string d = "quit";
		send(sock,d.c_str(),1024,0);
		close(sock);
		}
		return 0;

}

		
		







