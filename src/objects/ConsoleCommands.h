#ifndef CONSOLECOMMANDS_H
#define CONSOLECOMMANDS_H

#include <string>

namespace TIE
{
	class ConsoleCommands
	{
		public:
			virtual int processCommand(const std::string& command);

			ConsoleCommands();
			virtual ~ConsoleCommands();
		private:
	};
} 

#endif
