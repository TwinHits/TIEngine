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
			DevConsole();
			virtual ~DevConsole();

			const std::vector<SceneText>& getCommandHistory();

			virtual int runClientCommand(const std::string& command);
			void processCommand(const std::string& command);
			void update();

		private:
			std::vector<SceneText> commandHistory;
			int writePosition = -500;
			int fontSize = 16;
			const sf::Font& font;

	};
} 


#endif
