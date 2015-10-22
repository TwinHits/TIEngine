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
		logCrashFile("Could not open " + debugLogPath + "debug.log.");
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

void LogManager::logCrashFile(const std::string& message)
{
	//call for errors that occur before Config is opened
	std::ofstream crashLog;
	crashLog.open("crash.log");

	if (crashLog)
	{ crashLog << "[" << getTime() << "]" << "CRASH: " << message << std::endl;
		crashLog.close();
	}

}
