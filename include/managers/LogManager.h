#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <fstream>
#include <string>
#include <queue>

#include "objects/enumeration/LogLevel.h"

namespace TIE {

class LogManager: public Singleton<LogManager>, Manager {
	public:
		bool initialize();

		std::queue<std::string>& getQueueToDraw();
		void clearQueueToDraw();

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

		LogManager() {};
		~LogManager();
	private:
		std::string debugLogPath;
		std::ofstream log;
		std::queue<std::string> logHistory;

		LogManager(const LogManager&);
		void operator=(const LogManager&) {};
};

}
#endif
