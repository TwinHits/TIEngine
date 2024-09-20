#ifndef UIELEMENTFACTORY_H
#define UIELEMENTFACTORY_H 

#include "objects/factories/tientities/TIEntityFactory.h"

#include "sol/sol.hpp"

#include "objects/tientities/ui/UIElement.h"
#include "objects/ScriptTableReader.h"

namespace TIE {

class UIElementFactory : public TIEntityFactory {
    public:
        UIElementFactory();
        UIElementFactory(const sol::table&);
        ~UIElementFactory() {};

        virtual TIEntity& build();
    private:
		static const inline std::string BUTTON = "button";

};

}

#endif 
