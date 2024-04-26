#include "objects/components/ClickableComponent.h"

#include <functional>

#include "objects/Message.h"

using namespace TIE;

void ClickableComponent::setClickable(const bool clickable) {
    this->clickable = clickable;
}


const bool ClickableComponent::isClickable() {
    return this->clickable;
}


const bool ClickableComponent::isClickable() const {
    return this->clickable;
}


const std::function<void(Message&)> ClickableComponent::getOnClickFunction() {
    return this->onClickFunction;
}


void ClickableComponent::setOnClickFunction(std::function<void(Message&)> onClick) {
    this->onClickFunction = onClick;
}


const GlobalId ClickableComponent::getOnClickFunctionId() {
    return this->onClickFunctionId;
}


void ClickableComponent::setOnClickFunctionId(const GlobalId onClickFunctionId) {
    this->onClickFunctionId = onClickFunctionId;
}
