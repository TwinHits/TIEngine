#include "objects/tientities/engine/explorer/ComponentPropertiesDisplay.h"

#include <sstream>

#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/SpriteComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"
#include "componentsystems/MovesComponentSystem.h"
#include "enumeration/TextAlignment.h"
#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"

using namespace TIE;

ComponentPropertiesDisplay::ComponentPropertiesDisplay() : textComponent(TextComponentSystem::Instance()->addComponent(*this)) {
    this->setName("Component Properties Display");

    this->textComponent.setCharacterSize(16.0f);
    this->textComponent.setFont(AssetsManager::Instance()->getFont(ConfigManager::Instance()->getEngineFontName()));
    this->textComponent.setTextAlignment(TextAlignment::TOP_LEFT);
    this->textComponent.setDrawn(false);

    this->componentSystemsToDisplay = {
        PositionComponentSystem::Instance(),
        MovesComponentSystem::Instance(),
        SpriteComponentSystem::Instance(),
        TextComponentSystem::Instance(),
    };
}

 
void ComponentPropertiesDisplay::update(const float delta) {
    if (this->tientity && this->textComponent.isDrawn()) {
        std::stringstream ss;
        ss << this->tientity->getName() << std::endl << std::endl;
        ss << this->tientity->getId() << std::endl << std::endl;
        for (auto componentSystem : this->componentSystemsToDisplay) {
            ss << componentSystem->getComponentPropertiesString(*tientity);
        }
        this->textComponent.setString(ss.str());
    }
}

void ComponentPropertiesDisplay::setTIEntity(TIEntity* tientity) {
    this->tientity = tientity;
}

