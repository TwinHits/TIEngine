#ifndef UIELEMENTFACTORY_H
#define UIELEMENTFACTORY_H 

#include "objects/factories/tientities/TIEntityFactory.h"

#include "sol/sol.hpp"

#include "objects/ScriptTableReader.h"

namespace TIE {

class UIElementFactory : public TIEntityFactory {
    public:
        UIElementFactory();
        UIElementFactory(const sol::table&);
        ~UIElementFactory() {};

        TIEntity& build();
        TIEntity& build(const ScriptTableReader&);
    private:
		static const inline std::string TYPE = "type";
		static const inline std::string MENU = "Menu";
		static const inline std::string BUTTON = "Button";

};

}

#endif 
