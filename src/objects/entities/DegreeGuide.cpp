#include <cmath>

#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"
#include "managers/WindowManager.h"

#include "objects/entities/DegreeGuide.h"
#include "objects/components/TextComponent.h"

#include "templates/MakeUnique.h"

#include "utilities/ToRadians.h"

using namespace TIE;

void DegreeGuide::initialize() {
	this->setName("DegreeGuide");
	const sf::Font& font = AssetsManager::Instance()->getFont("DevConsole.ttf");
	const sf::Vector2i windowSize = WindowManager::Instance()->getWindowSize();
	const bool drawn = ConfigManager::Instance()->getShowDegreeGuide();

	for (int i = 0; i < this->CARDINAL_DEGREES.size(); i++) {
		TIEntity& degree = this->attachChild(make_unique<TIEntity>());
		degree.setName("DegreeGuidePoint");
		TextComponent* textComponent = degree.addComponent<TextComponent>();
		textComponent->setFont(font);
		textComponent->setCharacterSize(this->FONTSIZE);
		textComponent->setOrigin(0, this->FONTSIZE / 2);
		textComponent->setString(std::to_string(this->CARDINAL_DEGREES[i]));
		float x = std::cos(ToRadians(this->CARDINAL_DEGREES[i])) * (windowSize.x / 2 * this->PADDING);
		float y = std::sin(ToRadians(this->CARDINAL_DEGREES[i])) * (windowSize.y / 2 * this->PADDING);
		textComponent->move(sf::Vector2f(x, y));
		textComponent->setDrawn(drawn);
	}
}
