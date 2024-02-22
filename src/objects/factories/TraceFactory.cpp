#include "objects/factories/tientities/TraceFactory.h"

#include "componentsystems/BehavesComponentSystem.h"
#include "componentsystems/CollidesComponentSystem.h"
#include "componentsystems/LineComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/MessagesComponentSystem.h"
#include "componentsystems/WireframeComponentSystem.h"
#include "managers/HashManager.h"
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
    trace.setName(TraceFactory::TRACE);

    BehavesComponent& behavesComponent = BehavesComponentSystem::Instance()->addComponent(trace);
    // Collisions with traces should get renamed when being redirected to TraceCollisions
    // Perhaps MessageRedriect should have a map of types of messages to rename to other types of messages
    // Collision -> TraceCollision
    MessagesComponent& messagesComponent = MessagesComponentSystem::Instance()->addComponent(trace);
    messagesComponent.redirectFromId = this->parent->getId();
    messagesComponent.redirectToId = this->parent->getId();

    CollidesComponent& collidesComponent = CollidesComponentSystem::Instance()->addComponent(trace);
    collidesComponent.setCollides(true);
    
    PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(trace);
    PositionComponentSystem::Instance()->setPosition(trace, 0, 0);
    positionComponent.rotation = direction;

    LineComponent& lineComponent = LineComponentSystem::Instance()->addComponent(trace);
    lineComponent.setMagnitude(magnitude);
    LineComponentSystem::Instance()->setLine(lineComponent, positionComponent);

    if (WireframeComponentSystem::Instance()->getShowWireframe(trace.getParent())) {
        WireframeComponentSystem::Instance()->addWireframe(trace, lineComponent);
    }

    return trace;
}
