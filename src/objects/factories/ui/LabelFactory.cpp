
#include "objects/factories/ui/LabelFactory.h"

#include "componentsystems/ClickableComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/ShapeComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"

using namespace TIE;

LabelFactory::LabelFactory(): UIElementFactory() {}


LabelFactory::LabelFactory(const sol::table& definition): UIElementFactory(definition) {}


LabelFactory::LabelFactory(const ScriptTableReader& reader): UIElementFactory(reader) {}


TIEntity& LabelFactory::build() {
	TIEntity& label = this->UIElementFactory::build();

    PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(label);
    positionComponent.position = this->getPosition();

    TextComponent& textComponent = TextComponentSystem::Instance()->addComponent(label);
    textComponent.setTextAlignment(TextAlignment::CENTER);
    textComponent.setString(this->getText());
    textComponent.setCharacterSize(16);
    textComponent.setDrawn(this->getDrawn());

	return label;
}
