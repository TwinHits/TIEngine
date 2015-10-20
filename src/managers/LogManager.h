#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <fstream>
#include <string>

#include "../templates/Singleton.h"

class LogManager: public Singleton<LogManager>
{
	public:
		void logError(std::string error);
		void logWarn(std::string warn);
		void logInfo(std::string info);

		LogManager();
		~LogManager();

	private:
		void setLogFile();
		std::string getTime();

		std::ofstream log;

};

#endif
