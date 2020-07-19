#include "objects/components/EventsComponent.h"
#include "objects/components/SelectableComponent.h"

using namespace TIE;

bool SelectableComponent::isSelectable() {
	return this->selectable;
}

void SelectableComponent::setSelectable(bool selectable) {
	this->selectable = selectable;
}

bool SelectableComponent::isSelected() {
	return this->selected;
}

void SelectableComponent::setSelected(bool selected) {
	this->selected = selected;
}

