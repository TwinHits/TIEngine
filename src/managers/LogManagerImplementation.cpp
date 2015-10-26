#include "LogManager.h"
#include "ConfigManager.h"

#include "../utilities/LocalTime.h"

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
	log.open(ConfigManager::Instance()->getDebugLogPath() + "debug.log", std::ios_base::app);
	if (!log.is_open())
	{
		logError("Could not open logs/debug.log.");
		return;
	}
}

void LogManager::logError(const std::string& message)
{
	if (ConfigManager::Instance()->getDebugLogLevel() > 0)
		log << "[" << LocalTime() << "]" << " ERROR: " << message << std::endl;
}

void LogManager::logWarn(const std::string& message)
{
	if (ConfigManager::Instance()->getDebugLogLevel() > 1)
		log << "[" << LocalTime() << "]" << " WARN: " << message << std::endl;
}

void LogManager::logInfo(const std::string& message)
{
	if (ConfigManager::Instance()->getDebugLogLevel() > 2)
		log << "[" << LocalTime() << "]" << " INFO: " << message << std::endl;
}
