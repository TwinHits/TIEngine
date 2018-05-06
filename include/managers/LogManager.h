#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <fstream>
#include <string>
#include <queue>

#include "objects/enumeration/LogLevel.h"

#include "templates/Singleton.h"


namespace TIE {

class LogManager: public Singleton<LogManager> {
	public:
		std::queue<std::string>& getQueueToDraw();

		void setDebugLogLevel(LogLevel debugLogLevel);

		bool isDebugEnabled();
		bool isInfoEnabled();
		bool isWarnEnabled();
		bool isErrorEnabled();

		void logDebug(const std::string& message);
		void logInfo(const std::string& message);
		void logWarn(const std::string& message);
		void logError(const std::string& message);
		void logCommand(const std::string& message);


		LogManager();
		~LogManager();
	private:
		std::ofstream log;
		std::queue<std::string> queueToDraw;

		LogManager(const LogManager&);
		void operator=(const LogManager&);
};

}
#endif
