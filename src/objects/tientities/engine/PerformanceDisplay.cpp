#include "objects/tientities/engine/PerformanceDisplay.h"

#include <sstream>

#include <SFML/Graphics.hpp>

#include "constants/MessageSubscriptions.h"
#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"
#include "managers/MessageManager.h"
#include "managers/SceneManager.h"
#include "managers/TimeManager.h"
#include "managers/WindowManager.h"
#include "objects/components/TextComponent.h"

using namespace TIE;

PerformanceDisplay::PerformanceDisplay() : clock(TimeManager::Instance()->addClock()) {
	this->setName("PerformanceDisplay");
	this->textComponent.setDrawn(true);
	this->textComponent.setFont(AssetsManager::Instance()->getFont(ConfigManager::Instance()->getEngineFontName()));
	this->textComponent.setCharacterSize(16);
	this->setPosition();

	MessageManager::Instance()->subscribe(MessageSubscriptions::WINDOW_SIZE_CHANGE, std::bind(&PerformanceDisplay::onWindowSizeChange, this));
}


void PerformanceDisplay::update(const float delta) {
    std::stringstream ss;
    ss << "Frames: " << this->framesCounter << std::endl;
    ss << "FPS: " << SceneManager::Instance()->getFPS() << std::endl;
    ss << "Runtime: " << static_cast<int>(this->clock.getElapsedTime().asSeconds()) << std::endl;
    this->textComponent.setString(ss.str());
	this->framesCounter++;
}


void PerformanceDisplay::setPosition() {
	const sf::Vector2i& windowSize = WindowManager::Instance()->getWindowSize();
	this->textComponent.setPosition(0.0f - windowSize.x / 2.0f + 5.0f, 0.0f - windowSize.y / 2.0f);
}


void PerformanceDisplay::onWindowSizeChange() {
	this->setPosition();
}