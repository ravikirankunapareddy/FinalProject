#pragma once
#ifndef SOCKET_H
#define SOCKET_H
#include<WinSock2.h>
#include"logger.h"

#define LEN 512
struct socket_info
{
	sockaddr_in TCPClientAdd;
	sockaddr_in TCPServerAdd;
	int sAcceptSocket;
	int port;
};
class Socket
{
public:
	
	int iWsaStartup;
	int iWsaCleanup;
	int iCloseSocket;
	int iBind;
	int iListen;
	int port;
	int iSend;
	int iTCPClientAdd;
	struct sockaddr_in TCPClientAdd;
	struct sockaddr_in TCPServerAdd;
	struct socket_info socket_data;
	SOCKET TCPServerSocket;
	SOCKET sAcceptSocket;
	WSADATA winSockData;
	DWORD threadid;
	HANDLE hThread;
	Logger Log;
	std::string SenderBuffer;
	
	Socket();
	void createSocket();
	void bindSocket();
	void startListen();
	void acceptConnection();
	void CleanUp();
};
#endif

