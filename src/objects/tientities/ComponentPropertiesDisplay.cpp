#include "objects/tientities/ComponentPropertiesDisplay.h"

#include <sstream>

#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/SpriteComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"
#include "componentsystems/MovesComponentSystem.h"
#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"
#include "managers/EventsManager.h"
#include "managers/MessageManager.h"
#include "managers/WindowManager.h"
#include "objects/constants/MessageSubscriptions.h"
#include "objects/enumeration/TextAlignment.h"

using namespace TIE;

ComponentPropertiesDisplay::ComponentPropertiesDisplay() {
    this->setName("Component Properties Display");

    const sf::Vector2i& windowSize = WindowManager::Instance()->getWindowSize();
    this->setPosition(windowSize);
    this->setSize(windowSize);

    TextComponent& textComponent = TextComponentSystem::Instance()->addComponent(*this);
    textComponent.setCharacterSize(16.0f);
    textComponent.setFont(AssetsManager::Instance()->getFont(ConfigManager::Instance()->getEngineFontName()));
    textComponent.setDrawn(true);
    textComponent.setTextAlignment(TextAlignment::TOP_LEFT);

    this->componentSystemsToDisplay = {
        PositionComponentSystem::Instance(),
        MovesComponentSystem::Instance(),
        SpriteComponentSystem::Instance(),
        TextComponentSystem::Instance(),
    };

	MessageManager::Instance()->subscribe(MessageSubscriptions::WINDOW_SIZE_CHANGE, std::bind(&ComponentPropertiesDisplay::onWindowSizeChange, this));
}

 
void ComponentPropertiesDisplay::update(const float delta) {
    const std::vector<TIEntity*>& tientitiesUnderMousePosition = EventsManager::Instance()->getTIEntitiesUnderMousePosition();
    TIEntity* tientity = tientitiesUnderMousePosition.back();

    std::stringstream ss;
    ss << tientity->getName() << std::endl << std::endl;
    ss << tientity->getId() << std::endl << std::endl;
    for (auto componentSystem : this->componentSystemsToDisplay) {
        ss << componentSystem->getComponentPropertiesString(*tientity);
    }
    TextComponent* textComponent = this->getComponent<TextComponent>();
    textComponent->setString(ss.str());
}


void ComponentPropertiesDisplay::setPosition(const sf::Vector2i& windowSize) {
    PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(*this);
    positionComponent.position = sf::Vector2f(windowSize.x / 4.0f, -windowSize.y / 2.0f);
}


void ComponentPropertiesDisplay::setSize(const sf::Vector2i& windowSize) {
    SpriteComponent& spriteComponent = SpriteComponentSystem::Instance()->addComponent(*this);
    spriteComponent.setTexture(AssetsManager::Instance()->getTexture("dev_console.png"));
    sf::FloatRect& bounds = spriteComponent.getLocalBounds();
    float scaleX = float(windowSize.x / 4.0f) / float(bounds.width);
    float scaleY = float(windowSize.y) / float(bounds.height);
    const sf::Vector2f scale = sf::Vector2f(scaleX, scaleY);
    spriteComponent.setScale(scale);
    spriteComponent.setOrigin(0, 0);
    spriteComponent.setDrawn(true);
}


void ComponentPropertiesDisplay::onWindowSizeChange() {
    const sf::Vector2i& windowSize = WindowManager::Instance()->getWindowSize();
    this->setPosition(windowSize);
    this->setSize(windowSize);
}
