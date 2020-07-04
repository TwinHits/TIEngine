#include "managers/LogManager.h"

#include <iostream>

#include <boost/filesystem.hpp>

#include "managers/ConfigManager.h"
#include "managers/ConsoleManager.h"
#include "objects/enumeration/LogLevel.h"
#include "utilities/LocalTime.h"

using namespace TIE;

LogManager::LogManager()  {
	std::string debugLogPathConfig = ConfigManager::Instance()->getDebugLogPath();
	boost::filesystem::path debugLogPath = boost::filesystem::path(debugLogPathConfig);
	if (!boost::filesystem::exists(debugLogPath) || !boost::filesystem::is_directory(debugLogPath)) {
		boost::filesystem::create_directory(debugLogPath);
	}

	this->debugLogPath = debugLogPathConfig + "debug.log";
	this->log.open(this->debugLogPath, std::ios_base::app);
	if (!this->log.is_open()) {
		std::cout << "Could not open '" + this->debugLogPath + "'." << std::endl;
	}
}


LogManager::~LogManager() {
	this->log.close();
}


void LogManager::setDebugLogLevel(LogLevel debugLogLevel) {
	TIE::ConfigManager::Instance()->setDebugLogLevel(debugLogLevel);
}


std::queue<std::string>& LogManager::getQueueToDraw() {
	return logHistory;
}

void LogManager::clearQueueToDraw() {
	// Efficently clear queue
	std::queue<std::string> swap;
	this->logHistory.swap(swap);
}

void LogManager::clearLog() {
	this->log.close();
	this->log.open(this->debugLogPath, std::ofstream::trunc);
	if (!this->log.is_open()) {
		std::cout << "Could not open '" + this->debugLogPath + "' after clearing." << std::endl;
	}
	this->clearQueueToDraw();
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


void LogManager::debug(const std::string& message) {
	if (this->isDebugEnabled()) {
		std::string logString = "[" +  LocalTime() +  "]" + " DEBUG: " +  message;
		logHistory.push(logString);
		log << logString << std::endl;
	}
}


void LogManager::info(const std::string& message) {
	if (this->isInfoEnabled()) {
		std::string logString = "[" +  LocalTime() +  "]" + " INFO: " +  message;
		logHistory.push(logString);
		log << logString << std::endl;
	}
}


void LogManager::warn(const std::string& message) {
	if (this->isErrorEnabled()) {
		std::string logString = "[" +  LocalTime() +  "]" + " WARN: " +  message;
		logHistory.push(logString);
		log << logString << std::endl;
	}
}


void LogManager::error(const std::string& message) {
	if (this->isErrorEnabled()) {
		std::string logString = "[" +  LocalTime() +  "]" + " ERROR: " +  message;
		logHistory.push(logString);
		log << logString << std::endl;
	}
}


void LogManager::command(const std::string& message) {
	if (ConfigManager::Instance()->getDebugLogLevel() > 0) {
		std::string logString = "[" +  LocalTime() +  "]" + " COMMAND: " +  message;
		logHistory.push(logString);
		log << logString << std::endl;
	}
}
