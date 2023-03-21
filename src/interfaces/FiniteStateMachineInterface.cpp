#include "interfaces/ai/FiniteStateMachineInterface.h"

#include "sol/sol.hpp"

#include "managers/SceneManager.h"
#include "managers/WorldManager.h"
#include "objects/GlobalId.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

FiniteStateMachineInterface::FiniteStateMachineInterface(FiniteStateMachine& finiteStateMachine) {
    this->finiteStateMachine = &finiteStateMachine;
}


FiniteStateMachineInterface::FiniteStateMachineInterface(FiniteStateMachine* finiteStateMachine) {
    this->finiteStateMachine = finiteStateMachine;
}


void FiniteStateMachineInterface::registerUserType(sol::state& luaState) {
    sol::usertype<FiniteStateMachineInterface> interfaceUserType = luaState.new_usertype<FiniteStateMachineInterface>("FiniteStateMachineInterface");

    interfaceUserType["setState"] = &FiniteStateMachineInterface::setState;
    interfaceUserType["getState"] = &FiniteStateMachineInterface::getState;
    interfaceUserType["removeState"] = &FiniteStateMachineInterface::removeState;
    interfaceUserType["hasState"] = &FiniteStateMachineInterface::hasState;
    interfaceUserType["exit"] = &FiniteStateMachineInterface::exit;
} 


void FiniteStateMachineInterface::setState(GlobalId id) {
    if (id) {
        FiniteStateMachineFactory* factory = WorldManager::Instance()->getFiniteStateMachineFactory(id);
        if (factory) {
            this->finiteStateMachine->setState(std::move(factory->build(this->finiteStateMachine->getTIEntity())));
        }
    }
}


GlobalId FiniteStateMachineInterface::getState() {
    return this->finiteStateMachine->getFactoryId();
}


void FiniteStateMachineInterface::removeState() {
    this->finiteStateMachine->setState(nullptr);
}


bool FiniteStateMachineInterface::hasState() {
    return this->finiteStateMachine->getFactoryId() != 0;
}


void FiniteStateMachineInterface::exit() {
    this->finiteStateMachine->setExit(true);
}
