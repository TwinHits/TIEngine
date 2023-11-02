#include "objects/factories/tientities/TraceFactory.h"

#include "componentsystems/BehavesComponentSystem.h"
#include "componentsystems/CollidesComponentSystem.h"
#include "componentsystems/LineComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/MessagesComponentSystem.h"
#include "managers/HashManager.h"
#include "managers/WorldManager.h"
#include "templates/MakeUnique.h"

using namespace TIE;

TraceFactory::TraceFactory(TIEntity* parent): TraceFactory(*parent) {}


TraceFactory::TraceFactory(TIEntity& parent) {
    this->id = HashManager::Instance()->getNewGlobalId();
    this->setParent(parent);
}


const GlobalId TraceFactory::getId() {
    return this->id;
}


TraceFactory& TraceFactory::setParent(TIEntity& parent) {
    this->parent = &parent;
    return *this;
}


TraceFactory& TraceFactory::setMagnitude(const float magnitude) {
    this->magnitude = magnitude;
    return *this;
}


TraceFactory& TraceFactory::setDirection(const float direction) {
    this->direction = direction;
    return *this;
}


TIEntity& TraceFactory::build() {
    TIEntity& trace = this->parent->attachChild();

    BehavesComponent& behavesComponent = BehavesComponentSystem::Instance()->addComponent(trace);
    // Collisions with traces should get renamed when being redirected to TraceCollisions
    // Perhaps MessageRedriect should have a map of types of messages to rename to other types of messages
    // Collision -> TraceCollision
    MessagesComponent& messagesComponent = MessagesComponentSystem::Instance()->addComponent(trace);
    messagesComponent.redirectFromId = this->parent->getId();

    CollidesComponent& collidesComponent = CollidesComponentSystem::Instance()->addComponent(trace);
    collidesComponent.setCollides(true);
    
    LineComponent& lineComponent = LineComponentSystem::Instance()->addComponent(trace);
    lineComponent.setMagnitude(magnitude);

    PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(trace);
    positionComponent.rotation = direction;
    WorldManager::Instance()->registerTIEntity(trace);
    return trace;
}