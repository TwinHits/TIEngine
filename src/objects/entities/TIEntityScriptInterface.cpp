#include "objects/entities/TIEntityScriptInterface.h"

#include "componentsystems/MovesComponentSystem.h"
#include "managers/LogManager.h"
#include "managers/WorldManager.h"
#include "objects/components/MovesComponent.h"
#include "objects/enumeration/Direction.h"

using namespace TIE;

TIEntityScriptInterface::TIEntityScriptInterface(TIEntity& tientity) {
    this->tientity = &tientity;
}

sf::Vector2f TIEntityScriptInterface::getPosition() {
    SpriteComponent* spriteComponent = this->tientity->getComponent<SpriteComponent>();
    if (spriteComponent != nullptr) {
        return spriteComponent->getPosition();
    }
}


void TIEntityScriptInterface::setDestination() {

}


void TIEntityScriptInterface::moveUp() {
    MovesComponent* movesComponent = this->tientity->getComponent<MovesComponent>();
    SpriteComponent* spriteComponent = this->tientity->getComponent<SpriteComponent>();
    if (movesComponent != nullptr) {
        MovesComponentSystem::Instance()->setTargetPosition(*movesComponent, *spriteComponent, Direction::TOP);
    }
}


void TIEntityScriptInterface::moveRight() {
    MovesComponent* movesComponent = this->tientity->getComponent<MovesComponent>();
    SpriteComponent* spriteComponent = this->tientity->getComponent<SpriteComponent>();
    if (movesComponent != nullptr && spriteComponent != nullptr) {
        MovesComponentSystem::Instance()->setTargetPosition(*movesComponent, *spriteComponent, Direction::RIGHT);
    }
}


void TIEntityScriptInterface::moveLeft() {
    MovesComponent* movesComponent = this->tientity->getComponent<MovesComponent>();
    SpriteComponent* spriteComponent = this->tientity->getComponent<SpriteComponent>();
    if (movesComponent != nullptr && spriteComponent != nullptr) {
        MovesComponentSystem::Instance()->setTargetPosition(*movesComponent, *spriteComponent, Direction::LEFT);
    }
}


void TIEntityScriptInterface::moveDown() {
    MovesComponent* movesComponent = this->tientity->getComponent<MovesComponent>();
    SpriteComponent* spriteComponent = this->tientity->getComponent<SpriteComponent>();
    if (movesComponent != nullptr && spriteComponent != nullptr) {
        MovesComponentSystem::Instance()->setTargetPosition(*movesComponent, *spriteComponent, Direction::BOTTOM);
    }
}


void TIEntityScriptInterface::spawn(const std::string& entityName) {
    TIEntity* tientity = WorldManager::Instance()->spawnTIEntity(entityName);
}
