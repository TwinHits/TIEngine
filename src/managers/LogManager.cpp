#include "managers/ConfigManager.h"
#include "managers/ConsoleManager.h"
#include "managers/LogManager.h"

#include "objects/LogLevel.h"

#include "utilities/LocalTime.h"


using namespace TIE;

LogManager::LogManager()  {
	log.open(ConfigManager::Instance()->getDebugLogPath() + "debug.log", std::ios_base::app);
	if (!log.is_open()) {
		logError("Could not open '" + ConfigManager::Instance()->getDebugLogPath() + "'.");
	}
}


LogManager::~LogManager() {
	log.close();
}


void LogManager::setDebugLogLevel(LogLevel debugLogLevel) {
	TIE::ConfigManager::Instance()->setDebugLogLevel(debugLogLevel);
}


std::queue<std::string>& LogManager::getQueueToDraw() {
	return queueToDraw;
}


bool LogManager::isErrorEnabled() {
	return ConfigManager::Instance()->getDebugLogLevel() >= TIE::LogLevel::ERROR;
}


bool LogManager::isInfoEnabled() {
	return ConfigManager::Instance()->getDebugLogLevel() >= TIE::LogLevel::INFO;
}


bool LogManager::isWarnEnabled() {
	return ConfigManager::Instance()->getDebugLogLevel() >= TIE::LogLevel::WARN;
}


void LogManager::logCommand(const std::string& message) {
	if (ConfigManager::Instance()->getDebugLogLevel() > 0) {
		std::string logString = "[" +  LocalTime() +  "]" + "COMMAND: " +  message;
		queueToDraw.push(logString);
		log << logString << std::endl;
	}
}


void LogManager::logError(const std::string& message) {
	if (ConfigManager::Instance()->getDebugLogLevel() > 0) {
		std::string logString = "[" +  LocalTime() +  "]" + " ERROR: " +  message;
		queueToDraw.push(logString);
		log << logString << std::endl;
	}
}


void LogManager::logInfo(const std::string& message) {
	if (ConfigManager::Instance()->getDebugLogLevel() > 2) {
		std::string logString = "[" +  LocalTime() +  "]" + " INFO: " +  message;
		queueToDraw.push(logString);
		log << logString << std::endl;
	}
}


void LogManager::logWarn(const std::string& message) {
	if (ConfigManager::Instance()->getDebugLogLevel() > 1) {
		std::string logString = "[" +  LocalTime() +  "]" + " WARN: " +  message;
		queueToDraw.push(logString);
		log << logString << std::endl;
	}
}
