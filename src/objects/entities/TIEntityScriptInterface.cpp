#include "objects/entities/TIEntityScriptInterface.h"

#include "componentsystems/MovesComponentSystem.h"
#include "managers/LogManager.h"
#include "objects/components/MovesComponent.h"
#include "objects/enumeration/Direction.h"

using namespace TIE;

TIEntityScriptInterface::TIEntityScriptInterface(TIEntity& tientity) {
    this->tientity = &tientity;
}


void TIEntityScriptInterface::setDestination() {

}


void TIEntityScriptInterface::moveUp() {
    LogManager::Instance()->out("C++ move up");
    MovesComponent* movesComponent = this->tientity->getComponent<MovesComponent>();
    SpriteComponent* spriteComponent = this->tientity->getComponent<SpriteComponent>();
    if (movesComponent != nullptr) {
        MovesComponentSystem::Instance()->setTargetPosition(*movesComponent, *spriteComponent, Direction::TOP);
    }
}


void TIEntityScriptInterface::moveRight() {
    LogManager::Instance()->out("C++ move right");
    MovesComponent* movesComponent = this->tientity->getComponent<MovesComponent>();
    SpriteComponent* spriteComponent = this->tientity->getComponent<SpriteComponent>();
    if (movesComponent != nullptr) {
        MovesComponentSystem::Instance()->setTargetPosition(*movesComponent, *spriteComponent, Direction::RIGHT);
    }
}


void TIEntityScriptInterface::moveLeft() {
    LogManager::Instance()->out("C++ move left");
    MovesComponent* movesComponent = this->tientity->getComponent<MovesComponent>();
    SpriteComponent* spriteComponent = this->tientity->getComponent<SpriteComponent>();
    if (movesComponent != nullptr) {
        MovesComponentSystem::Instance()->setTargetPosition(*movesComponent, *spriteComponent, Direction::LEFT);
    }
}


void TIEntityScriptInterface::moveDown() {
    LogManager::Instance()->out("C++ move down");
    MovesComponent* movesComponent = this->tientity->getComponent<MovesComponent>();
    SpriteComponent* spriteComponent = this->tientity->getComponent<SpriteComponent>();
    if (movesComponent != nullptr) {
        MovesComponentSystem::Instance()->setTargetPosition(*movesComponent, *spriteComponent, Direction::BOTTOM);
    }
}


void TIEntityScriptInterface::spawn() {

}
