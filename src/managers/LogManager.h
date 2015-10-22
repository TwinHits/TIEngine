#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <fstream>
#include <string>

#include "../templates/Singleton.h"

class LogManager: public Singleton<LogManager>
{
	public:
		void logError(const std::string& message);
		void logWarn(const std::string& message);
		void logInfo(const std::string& message);

		static void logCrashFile(const std::string& message);

		LogManager();
		~LogManager();

	private:
		void setLogFile(const std::string& debugLogPath);
		static std::string getTime();

		std::ofstream log;

		LogManager(const LogManager&);
		void operator=(const LogManager&);
};

#endif
