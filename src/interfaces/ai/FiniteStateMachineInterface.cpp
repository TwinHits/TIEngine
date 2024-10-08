#include "interfaces/ai/FiniteStateMachineInterface.h"

#include "managers/WorldManager.h"

using namespace TIE;

FiniteStateMachineInterface::FiniteStateMachineInterface(FiniteStateMachine& finiteStateMachine) {
    this->finiteStateMachine = &finiteStateMachine;
}


FiniteStateMachineInterface::FiniteStateMachineInterface(FiniteStateMachine* finiteStateMachine) {
    this->finiteStateMachine = finiteStateMachine;
}


void FiniteStateMachineInterface::registerUserType(sol::state& luaState) {
    sol::usertype<FiniteStateMachineInterface> interfaceUserType = luaState.new_usertype<FiniteStateMachineInterface>("FiniteStateMachineInterface");

    interfaceUserType["addChildState"] = &FiniteStateMachineInterface::addChildState;
    interfaceUserType["hasChildState"] = &FiniteStateMachineInterface::hasChildState;
    interfaceUserType["removeChildState"] = &FiniteStateMachineInterface::removeChildState;
    interfaceUserType["exit"] = &FiniteStateMachineInterface::exit;
} 


void FiniteStateMachineInterface::addChildState(GlobalId id, const sol::object payload) {
    if (id) {
        FiniteStateMachineFactory* factory = WorldManager::Instance()->getFiniteStateMachineFactory(id);
        if (factory) {
            this->finiteStateMachine->setChildState(id, std::move(factory->build(this->finiteStateMachine->getTIEntity())), payload);
        }
    }
}


bool FiniteStateMachineInterface::hasChildState(GlobalId id) {
    return this->finiteStateMachine->hasChildState(id);
}


void FiniteStateMachineInterface::removeChildState(GlobalId id) {
    this->finiteStateMachine->setChildState(id, nullptr);
}


void FiniteStateMachineInterface::exit() {
    this->finiteStateMachine->setExit(true);
}
