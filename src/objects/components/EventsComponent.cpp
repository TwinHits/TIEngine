#include "objects/components/EventsComponent.h"

#include <string>

const std::string& TIE::EventsComponent::getClick() {
	return this->click;
}

void TIE::EventsComponent::setClick(const std::string& click) {
	this->click = click;
}
