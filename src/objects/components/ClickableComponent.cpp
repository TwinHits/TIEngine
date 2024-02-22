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

const std::function<void(Message&)> ClickableComponent::getOnClick() {
    return this->onClick;
}

void ClickableComponent::setOnClick(std::function<void(Message&)> onClick) {
    this->onClick = onClick;
}
