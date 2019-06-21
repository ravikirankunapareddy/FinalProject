#include "Server.h"
#include "Socket.h"
#include<iostream>
#include<winsock2.h>
#include<fstream>
#include<istream>
#include<string>//getline
#include<cstring>
#include<fileapi.h>
#define FLEN 20
#define STR "E:\\NCR_PHASE2\\multi_threading\\files\\"
using namespace std;


Server::Server()
{
	irecvBuffer = strlen(RecvBuffer) + 1;
	filepath = STR;
	port = 8080;
}
void Server::createConnection()
{

	Socket sock;
	sock.createSocket();
	sock.bindSocket();
	sock.startListen();
	while (1)
	{
		sock.acceptConnection();
	}
	sock.CleanUp();
}
