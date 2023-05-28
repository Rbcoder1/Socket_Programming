// serverSocket.cpp : main project file.

#include "stdafx.h"
#include <WinSock.h>
#include<iostream>
#include<conio.h>

using namespace std;

#define PORT 9909

//Provide an relevant information to socket when it bind
//information like  IP Version,IP Address, Port No,etc.
struct sockaddr_in srv;

fd_set fr, fw, fe;

int nMaxFd;

int main()
{
	int nRet = 0;
	//Intilize The WSA Varibles 
	//Initilizing the version of winsock to windows os. Tells OS That we Are performing network/socket programming
	WSADATA ws;
	if(WSAStartup(MAKEWORD(2,2),&ws) < 0){
		 cout<<endl<<"WSA Failed to Intilized"<<endl;
	}
	else
	{
		cout<<"WSA Initilized "<<endl;
	}

	//Initilize the socket 
	int nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INET : - IP Version , SOCK_STREAM :- Socket Type TCP, IPPROTO_TCP :- Protocol TCP

    if (nSocket < 0)
    {
        cout << "Socket Connection is Not Open"<<endl;
    }
    else
    {
        cout << "Socket Connection Successfull  "<<nSocket<<endl;
    }

	//assinging value to member of sockaddr_in to bind socket
	srv.sin_family = AF_INET;  //specifies IP Version
	srv.sin_port = htons(PORT);	//Specifies Port No
	srv.sin_addr.s_addr = INADDR_ANY;	//Specifies IP Address Where Socket In Run/Bind
	memset(&(srv.sin_zero),0,8);

	//Bind the socket to local port 
	nRet = bind(nSocket,(sockaddr*) & srv,sizeof(sockaddr));  //Binding Socket with using sockaddr_in information.
	if(nRet < 0)
	{
		cout<<"Failed to bind"<<endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		cout<<"Bind Succesfull"<<endl;
	}

	//Listen the request from client (queue the request)
	nRet = listen(nSocket,5);  //Place socket in listening mode accept incoming request and put into queue
	if(nRet < 0)
	{
		cout<<"Failed to Listen";
	}
	else{
		cout<<"Listening of Port : "<<PORT;
	}


	nMaxFd = nSocket;
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	FD_ZERO(&fr);
	FD_ZERO(&fr);
	FD_ZERO(&fr);

	FD_SET(nSocket, &fr);
	FD_SET(nSocket, &fe);
	
	cout<<endl<<"Before Select Call"<<fr.fd_count;

	//Accepting Socket Request From Queue One By One

	nRet = select(nMaxFd +1, &fr, &fw, &fe, &tv);
	if(nRet > 0)
	{
		//when someone connect or communicate with a message over a dedicated connection
	}
	else if(nRet == 0)
	{
		//no connection or any communication request made or you can say none of the socket descriptor are ready
		cout<<endl<<"Nothing on port:"<<PORT;
	}
	else{
		//it failed and your application should show some usefull message
	}
	cout<<endl<<"After the Select Call"<<fr.fd_count;

	getch();
}
