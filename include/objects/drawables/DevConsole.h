#ifndef DEVCONSOLE_H
#define DEVCONSOLE_H

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "TIEntity.h"
#include "TIExt.h"

namespace TIE {

class DevConsole : public TIEntity {
	public:
		DevConsole();
		virtual ~DevConsole();

		const std::vector<TIExt>& getCommandHistory() const;
		const TIExt& getCurrentCommand() const;

		virtual int runClientCommand(const std::string& command);
		void processCommand(const std::string& command);

		const sf::Vector2i& getWritePosition();


	private:
		virtual void drawSelf(sf::RenderTarget&, sf::RenderStates) const;
		void updateSelf(const float delta);
	
		const sf::Font& font;
		TIExt& currentCommand;
		int fontSize = 14;
		sf::Vector2i textWritePosition;

};

} 
#endif
