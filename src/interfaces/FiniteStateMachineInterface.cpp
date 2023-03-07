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

} 


void FiniteStateMachineInterface::setState(GlobalId id) {
    FiniteStateMachineFactory* factory = WorldManager::Instance()->getFiniteStateMachineFactory(id);
    if (factory) {
        this->finiteStateMachine->setState(std::move(factory->build(this->finiteStateMachine->getTIEntity())));
    }
}
