#include "managers/ConfigManager.h"
#include "managers/ConsoleManager.h"
#include "managers/LogManager.h"

#include "utilities/LocalTime.h"


using namespace TIE;


LogManager::LogManager() 
{
	log.open(ConfigManager::Instance()->getDebugLogPath() + "debug.log", std::ios_base::app);
	if (!log.is_open())
	{
		logError("Could not open '" + ConfigManager::Instance()->getDebugLogPath() + "'.");
	}
}


LogManager::~LogManager()
{
	log.close();
}


std::queue<std::string>& LogManager::getQueueToDraw()
{
	return queueToDraw;
}

bool LogManager::isErrorEnabled() {

	return ConfigManager::Instance()->getDebugLogLevel() > 0;
}

bool LogManager::isInfoEnabled() {
	
	return ConfigManager::Instance()->getDebugLogLevel() > 2;
}

bool LogManager::isWarnEnabled() {

	return ConfigManager::Instance()->getDebugLogLevel() > 1;
}

void LogManager::logCommand(const std::string& message)
{
	if (ConfigManager::Instance()->getDebugLogLevel() > 0)
	{
		std::string logString = "[" +  LocalTime() +  "]" + "COMMAND: " +  message;
		queueToDraw.push(logString);
		log << logString << std::endl;
	}
}


void LogManager::logError(const std::string& message)
{
	if (ConfigManager::Instance()->getDebugLogLevel() > 0)
	{
		std::string logString = "[" +  LocalTime() +  "]" + " ERROR: " +  message;
		queueToDraw.push(logString);
		log << logString << std::endl;
	}
}


void LogManager::logInfo(const std::string& message)
{
	if (ConfigManager::Instance()->getDebugLogLevel() > 2)
	{
		std::string logString = "[" +  LocalTime() +  "]" + " INFO: " +  message;
		queueToDraw.push(logString);
		log << logString << std::endl;
	}
}


void LogManager::logWarn(const std::string& message)
{
	if (ConfigManager::Instance()->getDebugLogLevel() > 1)
	{
		std::string logString = "[" +  LocalTime() +  "]" + " WARN: " +  message;
		queueToDraw.push(logString);
		log << logString << std::endl;
	}
}
