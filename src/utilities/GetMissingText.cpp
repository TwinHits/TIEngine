#include "utilities/GetMissingText.h"

#include "managers/AssetsManager.h"

sf::Text TIE::getMissingText() {
	sf::Text text;
	std::string missingText = "NO_TEXT";
	const sf::Font& font = TIE::AssetsManager::Instance()->getFont("font.tff");
	int fontSize = 14;
	sf::Vector2f position = sf::Vector2f(0, 0);

	text.setString(missingText);
	text.setFont(font);
	text.setCharacterSize(fontSize);
	text.setPosition(position);
	
	return text;
}
