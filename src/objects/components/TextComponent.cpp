#include "objects/components/TextComponent.h"

#include "utilities/GetMissingText.h"

using namespace TIE;

TextComponent::TextComponent() {
	//Move to get as a future optimization
}

void TextComponent::setDrawn(bool drawn) {
	this->drawn = drawn;
}


bool TextComponent::isDrawn() const {
	return this->drawn;
}
