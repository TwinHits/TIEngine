#ifndef DEVCONSOLE_H
#define DEVCONSOLE_H

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "TIEntity.h"
#include "SceneText.h"

namespace TIE {

class DevConsole : public TIEntity {
	public:
		DevConsole();
		virtual ~DevConsole();

		const std::vector<SceneText>& getCommandHistory();
		const SceneText& getCurrentCommand();

		virtual int runClientCommand(const std::string& command);
		void processCommand(const std::string& command);
		void update();

	private:
		std::vector<SceneText> commandHistory;
		SceneText currentCommand;
		const sf::Font& font;
		int fontSize = 14;
		sf::Vector2i textWritePosition;

};

} 
#endif
