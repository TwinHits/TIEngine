#include "interfaces/TIEntityInterface.h"

#include "sol/sol.hpp"

#include "componentsystems/MovesComponentSystem.h"
#include "managers/LogManager.h"
#include "managers/WorldManager.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/enumeration/Direction.h"

using namespace TIE;

TIEntityInterface::TIEntityInterface(TIEntity& tientity, sol::state& luaState) {
    this->tientity = &tientity;

    sol::usertype<TIEntityInterface> interfaceUserType = luaState.new_usertype<TIEntityInterface>("tientity");
	interfaceUserType["getPosition"] = &TIEntityInterface::getPosition;
    interfaceUserType["moveRight"] = &TIEntityInterface::moveRight;
    interfaceUserType["moveLeft"] = &TIEntityInterface::moveLeft;
    interfaceUserType["moveUp"] = &TIEntityInterface::moveUp;
    interfaceUserType["moveDown"] = &TIEntityInterface::moveDown;
    interfaceUserType["spawn"] = &TIEntityInterface::spawn;
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
