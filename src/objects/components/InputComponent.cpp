#include "objects/components/InputComponent.h"

#include <string>

const std::string& TIE::InputComponent::getClick() {
	return this->click;
}

void TIE::InputComponent::setClick(const std::string& click) {
	this->click = click;
}
