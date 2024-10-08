#ifndef BUTTONFACTORY_H
#define BUTTONFACTORY_H 

#include "objects/factories/ui/UIElementFactory.h"

#include <sol/sol.hpp>

#include <string>

#include "objects/Message.h"


namespace TIE {

class ButtonFactory : public UIElementFactory {
    public:
        ButtonFactory();
        ButtonFactory(const sol::table&);
        ButtonFactory(const ScriptTableReader&);
        ~ButtonFactory() {};

        ButtonFactory& setOnClickId(const GlobalId);
        ButtonFactory& setOnClick(const std::function<void(Message&)>);

        TIEntity& build();
    private:
        GlobalId onClickId = 0;
        std::function<void(Message&)> onClick = nullptr;

		static const inline std::string TEXT  = "text";
		static const inline std::string ON_CLICK = "onClick";

};

}

#endif 
