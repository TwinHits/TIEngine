#ifndef MENUFACTORY_H
#define MENUFACTORY_H 

#include "objects/factories/ui/UIElementFactory.h"

#include "sol/sol.hpp"

#include <string>

#include "objects/Message.h"
#include "objects/ScriptTableReader.h"
#include "objects/tientities/TIEntity.h"


namespace TIE {

    class MenuFactory : public UIElementFactory {
    public:
        MenuFactory();
        MenuFactory(const sol::table&);
        ~MenuFactory() {};

        MenuFactory& setPosition(const sf::Vector2f&);

        TIEntity& build(const ScriptTableReader&);
        TIEntity& build();
    private:
        sf::Vector2f position = sf::Vector2f(0, 0);

		static const inline std::string MENU_ITEMS  = "menuItems";
		static const inline std::string ON_CLICK = "onClick";
    };

}

#endif