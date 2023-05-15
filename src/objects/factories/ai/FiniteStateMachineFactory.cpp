#include "objects/factories/ai/FiniteStateMachineFactory.h"

#include <sol/sol.hpp>

#include "managers/HashManager.h"
#include "managers/ScriptManager.h"
#include "managers/WorldManager.h"
#include "objects/ai/FiniteStateMachine.h"
#include "templates/MakeUnique.h"

using namespace TIE;

FiniteStateMachineFactory::FiniteStateMachineFactory(const sol::table& definition) {
    this->id = HashManager::Instance()->getNewGlobalId();
    ScriptManager::Instance()->loadFiniteStateMachineDefinition(*this, definition);
    WorldManager::Instance()->saveFiniteStateMachineFactory(this->id, *this);
}


std::unique_ptr<FiniteStateMachine> FiniteStateMachineFactory::build(TIEntity& tientity) {
    std::unique_ptr<FiniteStateMachine> finiteStateMachine = make_unique<FiniteStateMachine>(tientity, this->id);

    if (this->stringToFunctionValues.count(FiniteStateMachine::ON_ENTER)) {
        finiteStateMachine->setOnEnterFunctionId(this->stringToFunctionValues.at(FiniteStateMachine::ON_ENTER));
    }

    if (this->stringToFunctionValues.count(FiniteStateMachine::ON_UPDATE)) {
        finiteStateMachine->setOnUpdateFunctionId(this->stringToFunctionValues.at(FiniteStateMachine::ON_UPDATE));
    }

    if (this->stringToFunctionValues.count(FiniteStateMachine::ON_EXIT)) {
        finiteStateMachine->setOnExitFunctionId(this->stringToFunctionValues.at(FiniteStateMachine::ON_EXIT));
    }

    for (auto& [subscriptionId, onMessageId] : this->idToFunctionValues) {
        finiteStateMachine->subscribe(subscriptionId, onMessageId);
    }

    return finiteStateMachine;
}


GlobalId FiniteStateMachineFactory::getId() {
    return this->id;
}
