#include "interfaces/TIEntityInterface.h"

#include "componentsystems/MovesComponentSystem.h"
#include "managers/LogManager.h"
#include "managers/WorldManager.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/enumeration/Direction.h"

using namespace TIE;

TIEntityInterface::TIEntityInterface(TIEntity& tientity) {
    this->tientity = &tientity;
}

sf::Vector2f TIEntityInterface::getPosition() {
    PositionComponent* positionComponent = this->tientity->getComponent<PositionComponent>();
    if (positionComponent != nullptr) {
        return positionComponent->position;
    }
}


void TIEntityInterface::setDestination() {

}


void TIEntityInterface::moveUp() {
    MovesComponent* movesComponent = this->tientity->getComponent<MovesComponent>();
    PositionComponent* positionComponent = this->tientity->getComponent<PositionComponent>();
    if (movesComponent != nullptr && positionComponent != nullptr) {
        MovesComponentSystem::Instance()->setTargetPosition(*movesComponent, *positionComponent, Direction::TOP);
    }
}


void TIEntityInterface::moveRight() {
    MovesComponent* movesComponent = this->tientity->getComponent<MovesComponent>();
    PositionComponent* positionComponent = this->tientity->getComponent<PositionComponent>();
    if (movesComponent != nullptr && positionComponent != nullptr) {
        MovesComponentSystem::Instance()->setTargetPosition(*movesComponent, *positionComponent, Direction::RIGHT);
    }
}


void TIEntityInterface::moveLeft() {
    MovesComponent* movesComponent = this->tientity->getComponent<MovesComponent>();
    PositionComponent* positionComponent = this->tientity->getComponent<PositionComponent>();
    if (movesComponent != nullptr && positionComponent != nullptr) {
        MovesComponentSystem::Instance()->setTargetPosition(*movesComponent, *positionComponent, Direction::LEFT);
    }
}


void TIEntityInterface::moveDown() {
    MovesComponent* movesComponent = this->tientity->getComponent<MovesComponent>();
    PositionComponent* positionComponent = this->tientity->getComponent<PositionComponent>();
    if (movesComponent != nullptr && positionComponent != nullptr) {
        MovesComponentSystem::Instance()->setTargetPosition(*movesComponent, *positionComponent, Direction::BOTTOM);
    }
}


void TIEntityInterface::spawn(const std::string& entityName) {
    WorldManager::Instance()->spawnTIEntity(entityName);
}
