#include <iostream>
#include <ctime>

#include "ConfigManager.h"
#include "LogManager.h"

LogManager::LogManager() 
{
	std::shared_ptr<ConfigManager> configmanager = ConfigManager::Instance();
	setLogFile(configmanager->getConfigValue("debugLogPath"));	
}
LogManager::~LogManager()
{
	log.close();
}

void LogManager::setLogFile(const std::string& debugLogPath)
{
	log.open(debugLogPath + "debug.log");
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
	std::cout << message << std::endl;
	log << "[" << getTime() << "]" << " INFO: " << message << std::endl;
}
