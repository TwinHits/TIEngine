#ifndef MENUFACTORY_H
#define MENUFACTORY_H 

#include "objects/factories/ui/UIElementFactory.h"

#include "sol/sol.hpp"

#include <string>

#include "objects/ScriptTableReader.h"
#include "objects/tientities/TIEntity.h"


namespace TIE {

    class MenuFactory : public UIElementFactory {
    public:
        MenuFactory();
        MenuFactory(const sol::table&);
        MenuFactory(const ScriptTableReader&);
        ~MenuFactory() {};

        MenuFactory& setEvent(const std::string&);

        TIEntity& build();
    private:
        std::string event = "";

		static const inline std::string EVENT = "event";
		static const inline std::string MENU_ITEMS  = "menuItems";
		static const inline std::string ON_CLICK = "onClick";
    };

}

#endif