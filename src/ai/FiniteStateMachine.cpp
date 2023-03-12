#include "objects/ai/FiniteStateMachine.h"

#include <memory>

#include "managers/ScriptManager.h"
#include "objects/GlobalId.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

FiniteStateMachine::FiniteStateMachine(TIEntity& tientity, const GlobalId factoryId) : tientity(tientity) {
    this->factoryId = factoryId;
};


TIEntity& FiniteStateMachine::getTIEntity() {
    return this->tientity;
}


const GlobalId FiniteStateMachine::getFactoryId() {
    if (this->childState) {
        return this->childState->factoryId;
    } else {
        return 0;
    }
}


const GlobalId FiniteStateMachine::getOnEnterFunctionId() {
    return this->onEnterFunctionId;
}


void FiniteStateMachine::setOnEnterFunctionId(const GlobalId onEnterFunctionId) {
    this->onEnterFunctionId = onEnterFunctionId;
}


const GlobalId FiniteStateMachine::getOnUpdateFunctionId() {
    return this->onUpdateFunctionId;
}


void FiniteStateMachine::setOnUpdateFunctionId(const GlobalId onUpdateFunctionId) {
    this->onUpdateFunctionId = onUpdateFunctionId;
}


const GlobalId FiniteStateMachine::getOnExitFunctionId() {
    return this->onExitFunctionId;

}


void FiniteStateMachine::setOnExitFunctionId(const GlobalId onExitFunctionId) {
    this->onExitFunctionId = onExitFunctionId;
}


void FiniteStateMachine::onEnter() {
    this->runFunction(this->onEnterFunctionId);
};


FiniteStateMachine* FiniteStateMachine::update(float delta) {
    this->runFunction(this->onUpdateFunctionId);
    if (this->childState) {
        this->childState->update(delta);
    }
    return nullptr;
};


void FiniteStateMachine::onExit() {
    this->runFunction(this->onExitFunctionId);
};


void FiniteStateMachine::setState(std::unique_ptr<FiniteStateMachine> newChildState) {
    if (this->childState) {
        this->childState->onExit();
    }
    this->childState = std::move(newChildState);
    if (this->childState) {
        this->childState->onEnter();
    }
}


void FiniteStateMachine::runFunction(const GlobalId functionId) {
    if (functionId) {
        ScriptManager::Instance()->runFunction<sol::optional<float> >(functionId, *this);
    }
}
