#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <fstream>
#include <string>

#include "templates/Singleton.h"

namespace TIE
{

	class LogManager: public Singleton<LogManager>
	{
		public:
			void logError(const std::string& message);
			void logWarn(const std::string& message);
			void logInfo(const std::string& message);
	
			LogManager();
			~LogManager();

		private:
			std::ofstream log;

			LogManager(const LogManager&);
			void operator=(const LogManager&);
	};

}

#endif
