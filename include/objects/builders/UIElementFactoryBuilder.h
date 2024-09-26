#ifndef UIELEMENTFACTORYBUILDER_H
#define UIELEMENTFACTORYBUILDER_H

#include <memory>
#include <string>

#include <sol/sol.hpp>

#include "objects/ScriptTableReader.h"
#include "objects/tientities/TIEntity.h"
#include "objects/factories/ui/UIElementFactory.h"

namespace TIE {

class UIElementFactoryBuilder {
    public:
        UIElementFactoryBuilder() {}
        ~UIElementFactoryBuilder() {}

        static std::unique_ptr<UIElementFactory> make_factory(const sol::table&);
        static std::unique_ptr<UIElementFactory> make_factory(const ScriptTableReader&);

    private:
		static const inline std::string TYPE = "type";

		static const inline std::string MENU = "Menu";
		static const inline std::string LABEL = "Label";
		static const inline std::string BUTTON = "Button";
};

}

#endif
