#include "objects/entities/TIEntityScriptInterface.h"

#include "componentsystems/MovesComponentSystem.h"
#include "managers/LogManager.h"
#include "managers/WorldManager.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/enumeration/Direction.h"

using namespace TIE;

TIEntityScriptInterface::TIEntityScriptInterface(TIEntity& tientity) {
    this->tientity = &tientity;
}

sf::Vector2f TIEntityScriptInterface::getPosition() {
    PositionComponent* positionComponent = this->tientity->getComponent<PositionComponent>();
    if (positionComponent != nullptr) {
        return positionComponent->getPosition();
    }
}


void TIEntityScriptInterface::setDestination() {

}


void TIEntityScriptInterface::moveUp() {
    MovesComponent* movesComponent = this->tientity->getComponent<MovesComponent>();
    PositionComponent* positionComponent = this->tientity->getComponent<PositionComponent>();
    if (movesComponent != nullptr && positionComponent != nullptr) {
        MovesComponentSystem::Instance()->setTargetPosition(*movesComponent, *positionComponent, Direction::TOP);
    }
}


void TIEntityScriptInterface::moveRight() {
    MovesComponent* movesComponent = this->tientity->getComponent<MovesComponent>();
    PositionComponent* positionComponent = this->tientity->getComponent<PositionComponent>();
    if (movesComponent != nullptr && positionComponent != nullptr) {
        MovesComponentSystem::Instance()->setTargetPosition(*movesComponent, *positionComponent, Direction::RIGHT);
    }
}


void TIEntityScriptInterface::moveLeft() {
    MovesComponent* movesComponent = this->tientity->getComponent<MovesComponent>();
    PositionComponent* positionComponent = this->tientity->getComponent<PositionComponent>();
    if (movesComponent != nullptr && positionComponent != nullptr) {
        MovesComponentSystem::Instance()->setTargetPosition(*movesComponent, *positionComponent, Direction::LEFT);
    }
}


void TIEntityScriptInterface::moveDown() {
    MovesComponent* movesComponent = this->tientity->getComponent<MovesComponent>();
    PositionComponent* positionComponent = this->tientity->getComponent<PositionComponent>();
    if (movesComponent != nullptr && positionComponent != nullptr) {
        MovesComponentSystem::Instance()->setTargetPosition(*movesComponent, *positionComponent, Direction::BOTTOM);
    }
}


void TIEntityScriptInterface::spawn(const std::string& entityName) {
    TIEntity* tientity = WorldManager::Instance()->spawnTIEntity(entityName);
}
