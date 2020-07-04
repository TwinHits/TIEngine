#ifndef DEVCONSOLE_H
#define DEVCONSOLE_H

#include "TIEntity.h"

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

namespace TIE {

class DevConsole : public TIEntity {
	public:
		DevConsole();
		virtual ~DevConsole() {};

		void initialize();
		void update(const float delta);

		TIEntity& getCommandText();
		const sf::Vector2i& getWritePosition();
		void setWritePosition(const sf::Vector2i&);
		void resetWritePosition();

	private:
		const sf::Font& font;
		TIEntity& currentCommand;
		int fontSize = 16;
		sf::Vector2i textWritePosition;
};

} 
#endif
