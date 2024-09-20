#include "objects/factories/ui/UIElementFactory.h"

#include "managers/HashManager.h"
#include "objects/ScriptTableReader.h"
#include "objects/factories/ui/ButtonFactory.h"
#include "objects/tientities/ui/UIElement.h"

using namespace TIE;

UIElementFactory::UIElementFactory() {}


UIElementFactory::UIElementFactory(const sol::table& definition) {}


TIEntity& UIElementFactory::build() {
	TIEntity& uiElement = TIEntityFactory::build();
    return uiElement;
}
