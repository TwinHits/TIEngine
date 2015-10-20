#include <iostream>
#include <ctime>

#include "LogManager.h"

LogManager::LogManager() 
{
	setLogFile();	
}
LogManager::~LogManager()
{
	log.close();
}

void LogManager::setLogFile()
{
	log.open("bin/logs/debug.log");
	if (!log)
	{
		std::cout << "ERROR: Could not open debug.log" << std::endl;
		return;
	}
}

std::string LogManager::getTime()
{

	auto t = std::time(nullptr);
	auto local = std::localtime(&t);

	char buffer[30];
	std::strftime(buffer, 30,"%c", local);

	return std::string(buffer);
}

void LogManager::logError(std::string error)
{
	log << "[" << getTime() << "]" << " ERROR: " << error << std::endl;
}

void LogManager::logWarn(std::string error)
{
	log << "[" << getTime() << "]" << " WARN: " << error << std::endl;
}

void LogManager::logInfo(std::string error)
{
	log << "[" << getTime() << "]" << " INFO: " << error << std::endl;
}
