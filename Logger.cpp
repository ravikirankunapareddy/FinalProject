#include "Logger.h"
#include<iostream>
#include<WinSock2.h>
#include<fstream>
#include<istream>
#include<string>//getline
#include<cstring>
#include<fileapi.h>
#define STR "E:\\NCR_PHASE2\\multi_threading\\files\\"
using namespace std;
void Logger::logg_error(string ip, string msg, int stat)
{
	SYSTEMTIME lt;
	GetLocalTime(&lt);
	ofstream loge("log_error.txt", ios::app);
	switch (stat)
	{
	case 1:
		loge << "IP: " << "No Connection" << " " << "Error:Startup failed " << " Time: " << lt.wHour << ":" << lt.wMinute << " Date:" << lt.wDay << "/" << lt.wMonth << "/" << lt.wYear << endl;
		break;
	case 2:
		loge << "IP: " << "No Connection" << " " << "Error:Socket creation failed " << " Time: " << lt.wHour << ":" << lt.wMinute << " Date:" << lt.wDay << "/" << lt.wMonth << "/" << lt.wYear << endl;
		break;
	case 3:

		loge << "IP: " << "No Connection" << " " << "Error:Binding failed " << " Time: " << lt.wHour << ":" << lt.wMinute << " Date:" << lt.wDay << "/" << lt.wMonth << "/" << lt.wYear << endl;
		break;
	case 4:
		loge << "IP: " << "No Connection" << " " << "Error:Listen failed " << " Time: " << lt.wHour << ":" << lt.wMinute << " Date:" << lt.wDay << "/" << lt.wMonth << "/" << lt.wYear << endl;
		break;
	case 5:
		loge << "IP: " << "No Connection" << " " << "Error:Accept failed " << " Time: " << lt.wHour << ":" << lt.wMinute << " Date:" << lt.wDay << "/" << lt.wMonth << "/" << lt.wYear << endl;
		break;

	case 6:
		loge << "IP: " << "No Connection" << " " << "Error:Thread creation failed " << " Time: " << lt.wHour << ":" << lt.wMinute << " Date:" << lt.wDay << "/" << lt.wMonth << "/" << lt.wYear << endl;
		break;
	case 7:
		loge << "IP: " << "No Connection" << " " << "Error:Socket closing failed " << " Time: " << lt.wHour << ":" << lt.wMinute << " Date:" << lt.wDay << "/" << lt.wMonth << "/" << lt.wYear << endl;
		break;
	case 8:
		loge << "IP: " << "No Connection" << " " << "Error:Cleanup failed " << " Time: " << lt.wHour << ":" << lt.wMinute << " Date:" << lt.wDay << "/" << lt.wMonth << "/" << lt.wYear << endl;
		break;
	default:
		loge << "IP: " << ip << " " << msg << " Time: " << lt.wHour << ":" << lt.wMinute << " Date:" << lt.wDay << "/" << lt.wMonth << "/" << lt.wYear << endl;
		break;

	}
}
void Logger::logg(string ip, string filename, int i)
{
	SYSTEMTIME lt;
	GetLocalTime(&lt);
	ofstream log("log.txt", ios::app);
	if (i == 0)
	{
		log << "IP:" << ip << " Time:" << lt.wHour << ":" << lt.wMinute << " Date:" << lt.wDay << "/" << lt.wMonth << "/" << lt.wYear << " Server Status: Fail" << " Requested file: " << filename << endl;
	}
	else
	{
		log << "IP:" << ip << " Time:" << lt.wHour << ":" << lt.wMinute << " Date:" << lt.wDay << "/" << lt.wMonth << "/" << lt.wYear << " Server Status: Success" << " Requested file: " << filename << endl;
	}
}
