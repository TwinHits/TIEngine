#include "objects/tientities/engine/DegreeGuide.h"

#include <cmath>

#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"
#include "constants/MessageSubscriptions.h"
#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"
#include "managers/MessageManager.h"
#include "managers/WindowManager.h"
#include "utils/TIEMath.h"

using namespace TIE;

DegreeGuide::DegreeGuide() {
	this->setName("DegreeGuide");

	const FontAsset& font = AssetsManager::Instance()->getFont(ConfigManager::Instance()->getEngineFontName());
	const bool drawn = ConfigManager::Instance()->getShowDegreeGuide();
	const sf::Vector2i& windowSize = WindowManager::Instance()->getWindowSize();

	for (auto& cardinalDegree : this->CARDINAL_DEGREES) {
		TIEntity& degreeGuidePoint = this->attachChild();
		this->degreeGuidePoints[cardinalDegree] = &degreeGuidePoint;
		degreeGuidePoint.setName("DegreeGuidePoint");

		TextComponent& textComponent = TextComponentSystem::Instance()->addComponent(degreeGuidePoint);
		textComponent.setFont(font);
		textComponent.setCharacterSize(this->FONT_SIZE);
		textComponent.setString(std::to_string(cardinalDegree));
		textComponent.setDrawn(drawn);

		this->setPosition(degreeGuidePoint, cardinalDegree, windowSize);
	}

	MessageManager::Instance()->subscribe(MessageSubscriptions::WINDOW_SIZE_CHANGE, std::bind(&DegreeGuide::onWindowSizeChange, this));
}


void DegreeGuide::setPosition(TIEntity& degreeGuidePoint, int cardinalDegree, const sf::Vector2i& windowSize) {
    float x = std::cos(Math::toRadians(cardinalDegree)) * (windowSize.x / 2 * this->PADDING);
    float y = std::sin(Math::toRadians(cardinalDegree)) * (windowSize.y / 2 * this->PADDING);
	PositionComponentSystem::Instance()->setPosition(degreeGuidePoint, x, y);
}


void DegreeGuide::onWindowSizeChange() {
	for (auto& [cardinalDegree, degreeGuidePoint] : this->degreeGuidePoints) {
		this->setPosition(*degreeGuidePoint, cardinalDegree, WindowManager::Instance()->getWindowSize());
	}
}
