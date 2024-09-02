#ifndef DEVCONSOLE_H
#define DEVCONSOLE_H

#include "objects/tientities/TIEntity.h"

#include <string>
#include <queue>

#include <SFML/Graphics.hpp>

#include "managers/LogManager.h"
#include "objects/tientities/common/SceneLayer.h"

namespace TIE {

class DevConsole : public TIEntity {
	public:
		DevConsole();
		virtual ~DevConsole() {};

		void initialize();
		void update(const float delta);

		TIEntity& getCurrentCommand();
		const sf::Vector2i& getWritePosition();
		void setWritePosition(const sf::Vector2i&);
		void resetWritePosition();

		void onWindowSizeChange();
	private:
		TIEntity& currentCommand;
		SceneLayer& consoleHistorySceneLayer;
		TIEntity& consoleHistory;
		int fontSize = 16;
		int lineCharacterLimit = 80;
		sf::Vector2i textWritePosition;
		std::queue<std::string>& queueToDraw = LogManager::Instance()->getQueueToDraw();

		void setPosition();
		void setLineCharacterLimit();
};

} 
#endif
