#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include<string>
class Logger
{
public:
	void logg_error(std::string ip, std::string msg, int stat);
	void logg(std::string ip, std::string filename, int i);
};
#endif

