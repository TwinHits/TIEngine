#include "objects/components/HoverableComponent.h"

#include <functional>

#include "objects/Message.h"

using namespace TIE;

void HoverableComponent::setHoverable(const bool hoverable) {
    this->hoverable = hoverable;
}


const bool HoverableComponent::isHoverable() {
    return this->hoverable;
}


const bool HoverableComponent::isHoverable() const {
    return this->hoverable;
}


const std::function<void(Message&)> HoverableComponent::getOnHoverFunction() {
    return this->onHoverFunction;
}


void HoverableComponent::setOnHoverFunction(std::function<void(Message&)> onHover) {
    this->onHoverFunction = onHover;
}


const GlobalId HoverableComponent::getOnHoverFunctionId() {
    return this->onHoverFunctionId;
}


void HoverableComponent::setOnHoverFunctionId(const GlobalId onHoverFunctionId) {
    this->onHoverFunctionId = onHoverFunctionId;
}
