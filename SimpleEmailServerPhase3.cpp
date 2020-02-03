#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib> 
#include <sstream>
#include <iostream>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <sstream> 
#include <string>
#include<netdb.h>
#include<arpa/inet.h>
#include<fstream>
#define MAXLINE 4096
#include <dirent.h>
using namespace std;
//#define PORT 8080 
int main(int argc, char** argv) 
{
    if(argc!=4){
        cout<< "usage" <<endl;
        exit(1);
    }
    DIR *pDir;
    pDir = opendir (argv[3]);
    if(!pDir){
        cout<<"Database error"<<endl;
        exit(4);
    }

    
//ofstream file(argv[2]);

    stringstream geek(argv[1]);
    int PORT = 0; 
    geek >> PORT; 

    int server_fd, new_socket; 
    struct sockaddr_in address; 
    int addrlen = sizeof(address); 
    char buffer[1024]={0}; 
    
    // Creating socket file descriptor 
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    /*if (( == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } */
    
     
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
    inet_aton("127.0.0.1",&(address.sin_addr));
    memset(&(address.sin_zero), '\0', 8);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    // Forcefully attaching socket to the port 8080 
    int binder = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    if (binder == -1)                             
    { 
        cout<<"bind error"<<endl; 
        exit(2); 
    }
    else{
        cout<<"BindDone:"<<PORT<<endl;
    }
    ifstream my_file(argv[2]);
    if (!my_file.good()){
    cout<<"file not present/not readable"<<endl;
    exit(3);
    } 


    if (listen(server_fd, 3) == 0) 
    { 
        cout<<"ListenDone:"<<PORT<<endl;
        }
    struct sockaddr_in caddress;
    int sin_size = sizeof(struct sockaddr_in);
    while((new_socket = accept( server_fd,(struct sockaddr *)&caddress, (socklen_t*)&sin_size))!=0){
    printf("Client:%s:%d \n" , inet_ntoa(caddress.sin_addr) , ntohs(caddress.sin_port));  
    memset(&buffer, 0, sizeof(buffer));
    recv(new_socket,buffer,100,0);
    int j=0;
    string words[4];
    stringstream ssin(buffer);
    	while (ssin.good() && j < 4){
        	ssin >> words[j];
        	++j;
    	}
    //cout<<words[0]<<words[1]<<words[2]<<words[3];
    if(words[0]!="User:" or words[2]!= "Pass:"){
        cout<<"Unable to parse"<<endl;
        close(new_socket);
    }
    string welmsg = "welcome: ";
    string out=welmsg.append(words[1]);
    ifstream inf("passwd.txt");
    
    //if couldnt opened
    if (!inf)
    {
        cout<< "file not exists/readable" << endl;
        exit(1);
    }
    int x,y=0;
    while (inf)
    {
        // read stuff from the file into a string and print it
        string strInput;
        getline(inf, strInput);
        string arr[2];
    	int i = 0;
    	stringstream ssin(strInput);
    	while (ssin.good() && i < 2){
        	ssin >> arr[i];
        	++i;
    	}
    if(arr[0]==words[1]){
    	if(arr[1]==words[3]){
        x = x+1;
    }
    y=y+1;
    }
}
    if(x==0 && y==0){
        cout<<"Invalid User"<<endl;
        string I = "Invalid User";
        send(new_socket,I.c_str(), strlen(I.c_str())+1,0);
        close(new_socket);
    }
    else if(x==0 && y!=0){
        cout<<"Wrong Passwd"<<endl;
        string I = "Wrong Passwd";
        send(new_socket,I.c_str(), strlen(I.c_str())+1,0);
        close(new_socket);
    }
    else{
        send(new_socket, out.c_str(),strlen(out.c_str())+1,0);
        cout<<out<<endl;
        char bufff[100]={0};
        memset(&buffer, 0, sizeof(buffer));
        int N;
        while((N=recv(new_socket,buffer,1024,0))>0){///////////////////////////////////////
        
        
        if(string(buffer)=="quit"){

            cout<<"Bye "<<words[1]<<endl;
            bzero(bufff,100);
            close(new_socket);
        }
        else{
            char *token,*dummy;
            dummy=buffer;
            token=strtok(dummy," ");
            token=strtok(NULL," \n");
            char port[MAXLINE],buffer1[MAXLINE],char_num_blks[MAXLINE],char_num_last_blk[MAXLINE];
            int datasock,lSize,num_blks,num_last_blk,i;
            bzero(port, MAXLINE);
            bzero(buffer1,MAXLINE);
            bzero(char_num_blks, MAXLINE);
            bzero(char_num_last_blk, MAXLINE);
            FILE *fp;
            FILE *fpipe;
            string q = "ls ./" ;
            string qqq="/";
            string qq = " | grep ";
            string s = q.append(argv[3]).append(qqq).append(words[1]).append(qqq).append(qq).append(token);
            //cout<<s<<endl;
            char c=0;
            string k= "";

            if (0 == (fpipe = (FILE*)popen(s.c_str(), "r")))
            {
                perror("Message Read Fail");
                close(new_socket);
            }

            while (fread(&c, sizeof c, 1, fpipe))
            {
            if(!isspace(c))
            k=k+c;
            }
            pclose(fpipe);
            string x="./";
            string kk =  x.append(argv[3]).append(qqq).append(words[1]).append(qqq).append(k);
            fp= fopen(kk.c_str(),"r");
            //cout<<kk<<endl;
            //accepting connnection by client
            if ((fp!=NULL))
            {
                //size of file

                send(new_socket,"1",MAXLINE,0);
                send(new_socket,k.c_str(),MAXLINE,0);
                fseek (fp , 0 , SEEK_END);
                lSize = ftell (fp);
                rewind (fp);
                num_blks = lSize/MAXLINE;
                num_last_blk = lSize%MAXLINE; 
                sprintf(char_num_blks,"%d",num_blks);
                send(new_socket, char_num_blks, MAXLINE, 0);
                //cout<<num_blks<<" "<<num_last_blk<<endl;

                for(i= 0; i < num_blks; i++) { 
                    fread (buffer1,sizeof(char),MAXLINE,fp);
                    send(new_socket, buffer1, MAXLINE, 0);
                    //cout<<buffer<<"   "<<i<<endl;
                }
                sprintf(char_num_last_blk,"%d",num_last_blk);
                send(new_socket, char_num_last_blk, MAXLINE, 0);
                if (num_last_blk > 0) { 
                    fread (buffer1,sizeof(char),num_last_blk,fp);
                    send(new_socket, buffer1, MAXLINE, 0);
                    //cout<<buffer<<endl;
                }
                fclose(fp);
                //close(datasock);
                cout<<words[1]<<": Transferring Message "<<token<<endl;
                
            }
            else{
                cout<<"Message Read Fail"<<endl;
                close(new_socket);
            }
            
    


    
        }
    }
}
}
    return 0;
}
