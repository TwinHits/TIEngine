#include "objects/entities/PerformanceDisplay.h"

#include <iomanip>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "objects/components/TextComponent.h"
#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"
#include "managers/SceneManager.h"
#include "managers/TimeManager.h"
#include "managers/WindowManager.h"

using namespace TIE;

PerformanceDisplay::PerformanceDisplay() : clock(TimeManager::Instance()->addClock()) {}


void PerformanceDisplay::initialize() {
	this->setName("PerformanceDisplay");

	const sf::Vector2i windowSize = WindowManager::Instance()->getWindowSize();
	this->textComponent.setDrawn(true);
	this->textComponent.setFont(AssetsManager::Instance()->getFont(ConfigManager::Instance()->getEngineFontName()));
	this->textComponent.setCharacterSize(16);
	this->textComponent.setPosition(0 - windowSize.x / 2 + 5, 0 - windowSize.y / 2);
}


void PerformanceDisplay::update(const float delta) {
    std::stringstream ss;
    ss << "Frames: " << this->framesCounter << std::endl;
    ss << "FPS: " << SceneManager::Instance()->getFPS() << std::endl;
    ss << "Runtime: " << static_cast<int>(this->clock.getElapsedTime().asSeconds()) << std::endl;
    this->textComponent.setString(ss.str());
	this->framesCounter++;
}