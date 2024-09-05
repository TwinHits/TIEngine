#include "managers/LogManager.h"

#include <iostream>

#include <boost/filesystem.hpp>

#include "constants/MessageSubscriptions.h"
#include "enumeration/LogLevel.h"
#include "managers/ConfigManager.h"
#include "managers/MessageManager.h"
#include "utils/LocalTime.h"
#include "utils/String.h"

using namespace TIE;

void LogManager::initialize()  {
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
	ConfigManager::Instance()->setDebugLogLevel(debugLogLevel);
}


const std::string& LogManager::getLastLogEntered() {
	return this->lastLogEntered;
}


void LogManager::clearLog() {
	this->log.close();
	this->log.open(this->debugLogPath, std::ofstream::trunc);
	if (!this->log.is_open()) {
		std::cout << "Could not open '" + this->debugLogPath + "' after clearing." << std::endl;
	}
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
		this->lastLogEntered = logString;
		if (this->log.is_open()) {
			log << logString << std::endl;
		}
		MessageManager::Instance()->publish(MessageSubscriptions::LOG_ENTERED);
	}
}


void LogManager::info(const std::string& message) {
	if (this->isInfoEnabled()) {
		std::string logString = "[" +  LocalTime() +  "]" + " INFO: " +  message;
		this->lastLogEntered = logString;
		if (this->log.is_open()) {
			log << logString << std::endl;
		}
		MessageManager::Instance()->publish(MessageSubscriptions::LOG_ENTERED);
	}
}


void LogManager::warn(const std::string& message) {
	if (this->isWarnEnabled()) {
		std::string logString = "[" +  LocalTime() +  "]" + " WARN: " +  message;
		this->lastLogEntered = logString;
		if (this->log.is_open()) {
			log << logString << std::endl;
		}
		MessageManager::Instance()->publish(MessageSubscriptions::LOG_ENTERED);
	}
}


void LogManager::error(const std::string& message) {
	if (this->isErrorEnabled()) {
		std::string logString = "[" +  LocalTime() +  "]" + " ERROR: " +  message;
		this->lastLogEntered = logString;
		if (this->log.is_open()) {
			log << logString << std::endl;
		}
		MessageManager::Instance()->publish(MessageSubscriptions::LOG_ENTERED);
	}
}


void LogManager::command(const std::string& message) {
    std::string logString = "[" +  LocalTime() +  "]" + " COMMAND: " +  message;
	this->lastLogEntered = logString;
	if (this->log.is_open()) {
		log << logString << std::endl;
	}
	MessageManager::Instance()->publish(MessageSubscriptions::LOG_ENTERED);
}
