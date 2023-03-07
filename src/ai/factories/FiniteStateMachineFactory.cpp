#include "objects/factories/ai/FiniteStateMachineFactory.h"

#include <sol/sol.hpp>

#include "managers/HashManager.h"
#include "managers/ScriptManager.h"
#include "managers/WorldManager.h"
#include "objects/ai/FiniteStateMachine.h"
#include "templates/MakeUnique.h"

using namespace TIE;

FiniteStateMachineFactory::FiniteStateMachineFactory(const sol::table& definition) {
    ScriptManager::Instance()->loadFiniteStateMachineDefinition(*this, definition);
    this->id = HashManager::Instance()->getNewGlobalId();
    WorldManager::Instance()->saveFiniteStateMachineFactory(this->id, *this);
}


std::unique_ptr<FiniteStateMachine> FiniteStateMachineFactory::build(TIEntity& tientity) {
    std::unique_ptr<FiniteStateMachine> finiteStateMachine = make_unique<FiniteStateMachine>(tientity);

    if (this->functionValues.count(FiniteStateMachine::ON_ENTER)) {
        finiteStateMachine->setOnEnterFunctionId(this->functionValues.at(FiniteStateMachine::ON_ENTER));
    }

    if (this->functionValues.count(FiniteStateMachine::ON_UPDATE)) {
        finiteStateMachine->setOnUpdateFunctionId(this->functionValues.at(FiniteStateMachine::ON_UPDATE));
    }

    if (this->functionValues.count(FiniteStateMachine::ON_EXIT)) {
        finiteStateMachine->setOnExitFunctionId(this->functionValues.at(FiniteStateMachine::ON_EXIT));
    }

    return finiteStateMachine;
}


GlobalId FiniteStateMachineFactory::getId() {
    return this->id;
}
