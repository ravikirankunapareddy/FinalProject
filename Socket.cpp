#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "Socket.h"
#include "Server.h"
#include<iostream>
#include<fstream>
#include<istream>
#include<string>//getline
#include<cstring>


#define STR "E:\\NCR_PHASE2\\multi_threading\\files\\"
using namespace std;


DWORD WINAPI clientThread(LPVOID lpParam)
{
	Logger log;
	Socket sock;
	string filepath = STR;
	cout << "Thread created successfully"<<endl;
	
	char RecvBuffer[LEN];
	int iRecv;
	int irecvBuffer = strlen(RecvBuffer) + 1;
	
	struct socket_info* s = (socket_info*)lpParam;
	struct sockaddr_in* addr_in = (struct sockaddr_in*) & s->TCPClientAdd;
	char* ip = inet_ntoa(addr_in->sin_addr);
	
	cout << s->sAcceptSocket << endl;
	
	//step8 receiving data from client
	while (1)
	{
		cout << "thread id " << GetCurrentThreadId() << endl;

		iRecv = recv(s->sAcceptSocket, RecvBuffer, irecvBuffer, 0);
		irecvBuffer = strlen(RecvBuffer) + 1;

		if (iRecv <= 0)
		{
			cout << "DATA receiving failed. ERROR -> " << WSAGetLastError() << endl;
			CloseHandle(GetCurrentThread());
			log.logg_error(ip, "Error: Data Receive Failed", 0);
			cout << "thread closed" << endl;
			break;
		}
		cout << "DATA RECEIVED  " << RecvBuffer << endl;

		//getting the filename from the client request
		char filename[LEN];
		int i, j, c = 0, flag = 0;
		for (i = 0; i < irecvBuffer; i++)
		{
			if (RecvBuffer[i] == '/')
			{
				flag = 1;
				for (j = i + 1; RecvBuffer[j] != ' '; j++)
				{
					filename[c++] = RecvBuffer[j];
				}


			}
			if (flag == 1)
				break;
		}
		filename[c] = '\0';

		if (strlen(filename) == 0)  //if url doesnot contain file then default file is index.html
		{
			strcpy(filename, "index.html");
		}

		filepath.append(filename);
		cout << endl << "-------" << filename << "------" << endl;

		WIN32_FIND_DATAA FindFileData;
		HANDLE hFile = FindFirstFileA(filepath.c_str(), &FindFileData); //finding the file in directory
		if (hFile == INVALID_HANDLE_VALUE)
		{
			sock.SenderBuffer = "HTTP/1.1 404 NOT FOUND\nContent-Type: text/plain\nContent-Length:25 \n\nError 404.File Not Found.";
			log.logg_error(ip, "Error: File Handle Error", 0);
		}

		else
		{
			//reading the content from the file

			ifstream infile(filepath);
			string s;
			string temp;
			while (!infile.eof())
			{
				getline(infile, temp);
				s = s + temp;
			}

			cout << "----------CONTENT OF FILE IS---------" << endl;
			cout << endl << s << endl << endl;


			std::string size = std::to_string(s.length());
			sock.SenderBuffer = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
			sock.SenderBuffer.append(size);
			sock.SenderBuffer.append("\n\n");
			sock.SenderBuffer.append(s);


		}//else

		int iSenderBuffer = strlen(sock.SenderBuffer.c_str()) + 1;


		//step7 send data to client
		sock.iSend = send(s->sAcceptSocket, sock.SenderBuffer.c_str(), iSenderBuffer, 0);
		if (sock.iSend == SOCKET_ERROR)
		{
			log.logg(ip, filename, 0);
			log.logg_error(ip, "Error: Data Sending Failed", 0);
			cout << "sending failed. ERROR -> " << WSAGetLastError() << endl;
			exit(0);
		}

		cout << "Data sending success " << sock.SenderBuffer << endl;
		log.logg(ip, filename, 1);
		FindClose(hFile);
		if (s->sAcceptSocket == INVALID_SOCKET)
		{
			cout << "Socket closded" << endl;
			log.logg_error(ip, "Error: Socket Closed", 0);
			closesocket(s->sAcceptSocket);
			CloseHandle(GetCurrentThread());

		}
	}
}
Socket::Socket()
{
	port = 8080;
	iWsaStartup = WSAStartup(MAKEWORD(2, 2), &winSockData);
	if (iWsaStartup != 0)
	{
		cout << "WSaStartup failed " << endl;
		Log.logg_error("", "", 1);
		exit(0);
	}
	cout << "WSaStartup Success " << endl;

	//step2 Fillthe structure
	TCPServerAdd.sin_family = AF_INET;
	TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
	TCPServerAdd.sin_port = htons(port);
	iTCPClientAdd = sizeof(TCPClientAdd);
}
void Socket::createSocket()
{
	TCPServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (TCPServerSocket == INVALID_SOCKET)
	{
		cout << "TCP serversocket creation failed " << WSAGetLastError() << endl;
		Log.logg_error("", "", 2);
		exit(0);
	}
	cout << "TCP serversocket creation success " << endl;
}
void Socket::bindSocket()
{
	iBind = bind(TCPServerSocket, (SOCKADDR*)& TCPServerAdd, sizeof(TCPServerAdd));
	if (iBind == SOCKET_ERROR)
	{
		cout << "Binding failed. ERROR -> " << WSAGetLastError() << endl;

		Log.logg_error("", "", 3);
		system("pause");
		exit(0);
	}
	cout << "Binding success " << endl;
}
void Socket::startListen()
{
	iListen = listen(TCPServerSocket, 2);
	if (iListen == SOCKET_ERROR)
	{
		cout << "listen function failed. ERROR -> " << WSAGetLastError() << endl;
		Log.logg_error("", "", 4);
		system("pause");
		exit(0);
	}
	cout << "listen function success " << endl;
}
void Socket::acceptConnection()
{

	sAcceptSocket = accept(TCPServerSocket, (SOCKADDR*)& TCPClientAdd, &iTCPClientAdd);
	if (sAcceptSocket == INVALID_SOCKET)
	{
		cout << "Accept function failed. ERROR -> " << WSAGetLastError() << endl;

		Log.logg_error("", "", 5);
		system("pause");
		exit(0);
	}
	cout << "Accept function success " << endl;
	cout << sAcceptSocket << endl;
	socket_data.port = port;
	socket_data.sAcceptSocket = sAcceptSocket;
	socket_data.TCPClientAdd = TCPClientAdd;
	socket_data.TCPServerAdd = TCPServerAdd;
	hThread = CreateThread(NULL, 0, clientThread, (LPVOID)&socket_data, 0, &threadid);
	if (hThread == NULL)
	{
		Log.logg_error("", "", 6);
	}

}
void Socket::CleanUp()
{
	iCloseSocket = closesocket(TCPServerSocket);
	if (iCloseSocket == SOCKET_ERROR)
	{
		cout << "closing socket failed. ERROR -> " << WSAGetLastError() << endl;
		Log.logg_error("", "", 7);
		exit(0);
	}
	cout << "closing socket  success " << endl;

	//step10 cleanup
	iWsaCleanup = WSACleanup();
	if (iWsaCleanup == SOCKET_ERROR)
	{
		cout << "clean up failed. ERROR -> " << WSAGetLastError() << endl;
		Log.logg_error("", "", 8);
		exit(0);
	}
	cout << "cleanup success " << endl;

}
