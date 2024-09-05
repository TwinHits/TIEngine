#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

#include "enumeration/LogLevel.h"

namespace TIE {

class LogManager: public Singleton<LogManager>, public Manager {
	public:
		void initialize();

		const std::string& getLastLogEntered();

		void setDebugLogLevel(LogLevel debugLogLevel);

		void clearLog();

		bool isDebugEnabled();
		bool isInfoEnabled();
		bool isWarnEnabled();
		bool isErrorEnabled();

		void debug(const std::string& message);
		void info(const std::string& message);
		void warn(const std::string& message);
		void error(const std::string& message);
		void command(const std::string& message);
		
		template <typename T>
		void out(const T& message) {
			std::cout << message << std::endl;
		}

		LogManager() {};
		~LogManager();
	private:
		std::string debugLogPath;
		std::ofstream log;
		std::string lastLogEntered;

		LogManager(const LogManager&);
		void operator=(const LogManager&) {};
};

}
#endif
