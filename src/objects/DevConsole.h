#ifndef DEVCONSOLE_H
#define DEVCONSOLE_H

#include <string>

#include "SceneObject.h"

namespace TIE
{
	class DevConsole : public SceneObject
	{
		public:
			void processCommand(const std::string& command);
			virtual int runClientCommand(const std::string& command);

			DevConsole();
			virtual ~DevConsole();
		private:
	};
} 

#endif
