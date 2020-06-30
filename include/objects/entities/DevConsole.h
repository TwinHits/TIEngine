#ifndef DEVCONSOLE_H
#define DEVCONSOLE_H

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "TIEntity.h"

namespace TIE {

class DevConsole : public TIEntity {
	public:
		DevConsole();
		virtual ~DevConsole() {};

		void initialize();

		TIEntity& getCommandText();
		const sf::Vector2i& getWritePosition();
		void update(const float delta);

	private:
		const sf::Font& font;
		TIEntity& currentCommand;
		int fontSize = 14;
		sf::Vector2i textWritePosition;
};

} 
#endif
