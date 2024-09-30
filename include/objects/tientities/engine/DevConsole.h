#ifndef DEVCONSOLE_H
#define DEVCONSOLE_H

#include "objects/tientities/TIEntity.h"

#include <SFML/Graphics.hpp>

#include "objects/tientities/common/SceneLayer.h"

namespace TIE {

class DevConsole : public TIEntity {
	public:
		DevConsole();
		virtual ~DevConsole() {};

		void initialize();

		TIEntity& getCurrentCommand();
		const sf::Vector2i& getWritePosition();
		void setWritePosition(const sf::Vector2i&);
		void resetWritePosition();

		void onWindowSizeChange();
		void onLogEntered();
	private:
		TIEntity& currentCommand;
		SceneLayer& consoleHistorySceneLayer;
		TIEntity& consoleHistory;
		int fontSize = 16;
		int maxLineLength = 80;
		sf::Vector2i textWritePosition;

		void setPosition();
		void setLineCharacterLimit();
};

} 
#endif
