#include "objects/factories/ui/UIElementFactory.h"

#include "managers/HashManager.h"
#include "objects/ScriptTableReader.h"
#include "objects/factories/ui/ButtonFactory.h"
#include "objects/factories/ui/MenuFactory.h"
#include "templates/MakeUnique.h"

using namespace TIE;

UIElementFactory::UIElementFactory() : TIEntityFactory() {}


UIElementFactory::UIElementFactory(const sol::table& definition) : TIEntityFactory(definition) {}


TIEntity& UIElementFactory::build() {
    return this->build(this->getReader());
}


TIEntity& UIElementFactory::build(const ScriptTableReader& reader) {
    const std::string type = reader.get<std::string>(UIElementFactory::TYPE, "");
    std::unique_ptr<TIEntityFactory> tientityFactory = nullptr;
    if (type == UIElementFactory::MENU) {
        tientityFactory = TIE::make_unique<MenuFactory>();
    } else if (type == UIElementFactory::BUTTON) {
        tientityFactory = TIE::make_unique<ButtonFactory>();
    } else {
        return this->TIEntityFactory::build();
    }

    tientityFactory->setParent(this->getParent());
    
    return tientityFactory->build(reader);
}
