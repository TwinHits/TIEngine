#include "objects/ai/FiniteStateMachine.h"

#include <memory>

#include "managers/ScriptManager.h"
#include "objects/GlobalId.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

FiniteStateMachine::FiniteStateMachine(TIEntity& tientity, const GlobalId factoryId) : tientity(tientity) {
    this->factoryId = factoryId;
};


void FiniteStateMachine::setParent(FiniteStateMachine* parent) {
    this->parent = parent;
}


FiniteStateMachine* FiniteStateMachine::getParent() {
    return this->parent;
}


TIEntity& FiniteStateMachine::getTIEntity() {
    return this->tientity;
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


void FiniteStateMachine::setExit(bool exit) {
    this->exit = exit;
}


bool FiniteStateMachine::getExit() {
    return this->exit;
}


void FiniteStateMachine::onEnter() {
    this->runFunction(this->onEnterFunctionId);
};


void FiniteStateMachine::update(float delta) {
    this->runFunction(this->onUpdateFunctionId, delta);
    if (!this->childStates.empty()) {
        // Allow for removal of elements while iterating
        for (auto index = this->childStates.cbegin(), next = index; index != this->childStates.cend(); index = next) {
            ++next;
            index->second->update(delta);
            if (index->second->exit) {
                this->setChildState(index->first, nullptr);
            }
        }
    }
};


void FiniteStateMachine::onExit() {
    this->runFunction(this->onExitFunctionId);
};


const bool FiniteStateMachine::hasChildState(const GlobalId id) {
    return this->childStates.count(id);
}


void FiniteStateMachine::setChildState(const GlobalId id, std::unique_ptr<FiniteStateMachine> newChildState) {
    if (!this->childStates.count(id) || newChildState == nullptr) {
        if (this->childStates.count(id) && this->childStates.at(id) != nullptr) {
            this->childStates[id]->onExit();
        }

        if (newChildState != nullptr) {
            this->childStates[id] = std::move(newChildState);
            this->childStates[id]->setParent(this);
            this->childStates[id]->onEnter();
        }
        else {
            this->childStates.erase(id);
        }
    }
}


void FiniteStateMachine::runFunction(const GlobalId functionId, const float delta) {
    if (functionId) {
        ScriptManager::Instance()->runFunction<sol::optional<float> >(functionId, *this, delta);
    }
}


void FiniteStateMachine::runFunction(const GlobalId functionId) {
    if (functionId) {
        ScriptManager::Instance()->runFunction<sol::optional<float> >(functionId, *this, 0);
    }
}

