#include "objects/tientities/engine/explorer/ComponentPropertiesDisplay.h"

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
#include "objects/enumeration/TextAlignment.h"

using namespace TIE;

ComponentPropertiesDisplay::ComponentPropertiesDisplay() {
    this->setName("Component Properties Display");

    TextComponent& textComponent = TextComponentSystem::Instance()->addComponent(*this);
    textComponent.setCharacterSize(16.0f);
    textComponent.setFont(AssetsManager::Instance()->getFont(ConfigManager::Instance()->getEngineFontName()));
    textComponent.setTextAlignment(TextAlignment::TOP_LEFT);
    textComponent.setDrawn(false);

    this->componentSystemsToDisplay = {
        PositionComponentSystem::Instance(),
        MovesComponentSystem::Instance(),
        SpriteComponentSystem::Instance(),
        TextComponentSystem::Instance(),
    };
}

 
void ComponentPropertiesDisplay::update(const float delta) {
    const std::vector<TIEntity*>& tientitiesUnderMousePosition = EventsManager::Instance()->getTIEntitiesUnderMousePosition();
    TextComponent* textComponent = this->getComponent<TextComponent>();
    if (tientitiesUnderMousePosition.size()) {
        TIEntity* tientity = tientitiesUnderMousePosition.back();
        std::stringstream ss;
        ss << tientity->getName() << std::endl << std::endl;
        ss << tientity->getId() << std::endl << std::endl;
        for (auto componentSystem : this->componentSystemsToDisplay) {
            ss << componentSystem->getComponentPropertiesString(*tientity);
        }
        textComponent->setString(ss.str());
    } else {
        textComponent->clearString();
    }
}

