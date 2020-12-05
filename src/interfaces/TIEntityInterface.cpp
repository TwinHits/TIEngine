#include "interfaces/TIEntityInterface.h"

#include "sol/sol.hpp"

#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/EventsComponentSystem.h"
#include "interfaces/Vector2fInterface.h"
#include "managers/LogManager.h"
#include "managers/WorldManager.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/enumeration/Direction.h"

using namespace TIE;

TIEntityInterface::TIEntityInterface(TIEntity& tientity) {
    this->tientity = &tientity;
}


void TIEntityInterface::registerUserType(sol::state& luaState) {
    sol::usertype<TIEntityInterface> interfaceUserType = luaState.new_usertype<TIEntityInterface>("tientity");
	interfaceUserType["getPosition"] = &TIEntityInterface::getPosition;
	interfaceUserType["setDestination"] = &TIEntityInterface::setDestination;
	interfaceUserType["atDestination"] = &TIEntityInterface::atDestination;
    interfaceUserType["moveRight"] = &TIEntityInterface::moveRight;
    interfaceUserType["moveLeft"] = &TIEntityInterface::moveLeft;
    interfaceUserType["moveUp"] = &TIEntityInterface::moveUp;
    interfaceUserType["moveDown"] = &TIEntityInterface::moveDown;
    interfaceUserType["spawn"] = &TIEntityInterface::spawn;
    interfaceUserType["addState"] = &TIEntityInterface::addState;
    interfaceUserType["removeState"] = &TIEntityInterface::removeState;
}


Vector2fInterface TIEntityInterface::getPosition() {
    PositionComponent* positionComponent = this->tientity->getComponent<PositionComponent>();
    if (positionComponent != nullptr) {
        return Vector2fInterface(positionComponent->position.x, positionComponent->position.y);
    } else {
        return Vector2fInterface(0.0F, 0.0F);
    }
}


void TIEntityInterface::setDestination(const float x, const float y) {
    MovesComponent* movesComponent = this->tientity->getComponent<MovesComponent>();
    PositionComponent* positionComponent = this->tientity->getComponent<PositionComponent>();
    if (movesComponent != nullptr && positionComponent != nullptr) {
        MovesComponentSystem::Instance()->setTargetPosition(*movesComponent, *positionComponent, sf::Vector2f(x, y));
    }
}

bool TIEntityInterface::atDestination() {
    return MovesComponentSystem::Instance()->atTargetPosition(*this->tientity);
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


void TIEntityInterface::addState(const std::string& state) {
    EventsComponentSystem::Instance()->addState(*this->tientity, state);
}


void TIEntityInterface::removeState(const std::string& state) {
    EventsComponentSystem::Instance()->removeState(*this->tientity, state);
}
