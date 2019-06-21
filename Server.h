#pragma once
#ifndef SERVER_H
#define SERVER_H
#include"logger.h"
#include"Socket.h"
#include<string>

class Server
{
public:
	std::string filepath;
	char RecvBuffer[LEN];
	
	int iRecv;
	int irecvBuffer;
	int err;
	int port;
	
	Server();
	void createConnection();
	
};
#endif

