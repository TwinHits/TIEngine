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
	log.open("logs/debug.log", std::ios_base::app);
	if (!log.is_open())
	{
		logError("Could not open logs/debug.log.");
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

void LogManager::logError(const std::string& message)
{
	log << "[" << getTime() << "]" << " ERROR: " << message << std::endl;
}

void LogManager::logWarn(const std::string& message)
{
	log << "[" << getTime() << "]" << " WARN: " << message << std::endl;
}

void LogManager::logInfo(const std::string& message)
{
	log << "[" << getTime() << "]" << " INFO: " << message << std::endl;
}
