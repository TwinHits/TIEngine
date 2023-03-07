#include "objects/ai/FiniteStateMachine.h"

#include <memory>

#include "managers/ScriptManager.h"
#include "objects/GlobalId.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

FiniteStateMachine::FiniteStateMachine(TIEntity& tientity) : tientity(tientity) {};


TIEntity& FiniteStateMachine::getTIEntity() {
    return this->tientity;
}


GlobalId FiniteStateMachine::getOnEnterFunctionId() {
    return this->onEnterFunctionId;
}


void FiniteStateMachine::setOnEnterFunctionId(GlobalId onEnterFunctionId) {
    this->onEnterFunctionId = onEnterFunctionId;
}


GlobalId FiniteStateMachine::getOnUpdateFunctionId() {
    return this->onUpdateFunctionId;
}


void FiniteStateMachine::setOnUpdateFunctionId(GlobalId onUpdateFunctionId) {
    this->onUpdateFunctionId = onUpdateFunctionId;
}


GlobalId FiniteStateMachine::getOnExitFunctionId() {
    return this->onExitFunctionId;

}


void FiniteStateMachine::setOnExitFunctionId(GlobalId onExitFunctionId) {
    this->onExitFunctionId = onExitFunctionId;
}


void FiniteStateMachine::onEnter() {
    this->runFunction(this->onEnterFunctionId);
};


void FiniteStateMachine::update(float delta) {
    this->runFunction(this->onUpdateFunctionId);
    if (this->childState) {
        this->childState->update(delta);
    }
};


void FiniteStateMachine::onExit() {
    this->runFunction(this->onExitFunctionId);
};


void FiniteStateMachine::setState(std::unique_ptr<FiniteStateMachine> newChildState) {
    if (this->childState) {
        this->childState->onExit();
    }
    this->childState = std::move(newChildState);
    this->childState->onEnter();
}


void FiniteStateMachine::runFunction(GlobalId functionId) {
    if (functionId) {
        ScriptManager::Instance()->runFunction<bool>(functionId, *this);
    }
}
