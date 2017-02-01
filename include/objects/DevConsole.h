#ifndef DEVCONSOLE_H
#define DEVCONSOLE_H

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "TIEntity.h"
#include "SceneText.h"

namespace TIE
{
	class DevConsole : public TIEntity
	{
		public:
			void processCommand(const std::string& command);
			virtual int runClientCommand(const std::string& command);

			const std::vector<SceneText>& getCommandHistory();

			DevConsole();
			virtual ~DevConsole();
		private:
			std::vector<SceneText> commandHistory;
			int writePosition = 0;
			int fontSize = 10;
			const sf::Font& font;

			void addCommandHistory(const std::string& command);


	};
} 

#endif
