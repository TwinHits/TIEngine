#include <boost/filesystem.hpp>

#include <iostream>

#include "managers/ConfigManager.h"
#include "managers/ConsoleManager.h"
#include "managers/LogManager.h"

#include "objects/enumeration/LogLevel.h"

#include "utilities/LocalTime.h"


using namespace TIE;

LogManager::LogManager()  {
	std::string debugLogPathConfig = ConfigManager::Instance()->getDebugLogPath();
	boost::filesystem::path debugLogPath = boost::filesystem::path(debugLogPathConfig);
	if (!boost::filesystem::exists(debugLogPath) || !boost::filesystem::is_directory(debugLogPath)) {
		boost::filesystem::create_directory(debugLogPath);
	}

	log.open(debugLogPathConfig + "debug.log", std::ios_base::app);
	if (!log.is_open()) {
		std::cout << "Could not open '" + ConfigManager::Instance()->getDebugLogPath() + "'." << std::endl;
	}
}


LogManager::~LogManager() {
	log.close();
}


void LogManager::setDebugLogLevel(LogLevel debugLogLevel) {
	TIE::ConfigManager::Instance()->setDebugLogLevel(debugLogLevel);
}


std::queue<std::string>& LogManager::getQueueToDraw() {
	return logHistory;
}


bool LogManager::isDebugEnabled() {
	return ConfigManager::Instance()->getDebugLogLevel() >= TIE::LogLevel::DEBUG;
}


bool LogManager::isInfoEnabled() {
	return ConfigManager::Instance()->getDebugLogLevel() >= TIE::LogLevel::INFO;
}


bool LogManager::isWarnEnabled() {
	return ConfigManager::Instance()->getDebugLogLevel() >= TIE::LogLevel::WARN;
}


bool LogManager::isErrorEnabled() {
	return ConfigManager::Instance()->getDebugLogLevel() >= TIE::LogLevel::ERROR;
}


void LogManager::logDebug(const std::string& message) {
	if (this->isDebugEnabled()) {
		std::string logString = "[" +  LocalTime() +  "]" + " DEBUG: " +  message;
		logHistory.push(logString);
		log << logString << std::endl;
	}
}


void LogManager::logInfo(const std::string& message) {
	if (this->isInfoEnabled()) {
		std::string logString = "[" +  LocalTime() +  "]" + " INFO: " +  message;
		logHistory.push(logString);
		log << logString << std::endl;
	}
}


void LogManager::logWarn(const std::string& message) {
	if (this->isErrorEnabled()) {
		std::string logString = "[" +  LocalTime() +  "]" + " WARN: " +  message;
		logHistory.push(logString);
		log << logString << std::endl;
	}
}


void LogManager::logError(const std::string& message) {
	if (this->isErrorEnabled()) {
		std::string logString = "[" +  LocalTime() +  "]" + " ERROR: " +  message;
		logHistory.push(logString);
		log << logString << std::endl;
	}
}


void LogManager::logCommand(const std::string& message) {
	if (ConfigManager::Instance()->getDebugLogLevel() > 0) {
		std::string logString = "[" +  LocalTime() +  "]" + " COMMAND: " +  message;
		logHistory.push(logString);
		log << logString << std::endl;
	}
}
