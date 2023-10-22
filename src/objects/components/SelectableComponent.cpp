#include "objects/components/SelectableComponent.h"

using namespace TIE;

void SelectableComponent::setSelectable(const bool selectable) {
    this->selectable = selectable;
}


const bool SelectableComponent::isSelectable() {
    return this->selectable;
}


const bool SelectableComponent::isSelectable() const {
    return this->selectable;
}


void SelectableComponent::setSelected(const bool selected) {
    this->selected = selected;
}


const bool SelectableComponent::isSelected() {
    return this->selected;
}


const bool SelectableComponent::isSelected() const {
    return this->selected;
}
