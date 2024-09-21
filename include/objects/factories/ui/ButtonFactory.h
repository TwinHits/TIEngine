#ifndef BUTTONFACTORY_H
#define BUTTONFACTORY_H 

#include "objects/factories/tientities/TIEntityFactory.h"

#include "sol/sol.hpp"

#include <string>

#include "objects/Message.h"
#include "objects/ScriptTableReader.h"
#include "objects/tientities/TIEntity.h"


namespace TIE {

class ButtonFactory : public TIEntityFactory {
    public:
        ButtonFactory();
        ButtonFactory(const sol::table&);
        ~ButtonFactory() {};

        ButtonFactory& setPosition(const sf::Vector2f&);
        ButtonFactory& setSize(const sf::Vector2f&);
        ButtonFactory& setText(const std::string&);
        ButtonFactory& setOnClickId(const GlobalId);
        ButtonFactory& setOnClick(const std::function<void(Message&)>);
        ButtonFactory& setDrawn(const bool);

        TIEntity& build(const ScriptTableReader&);
        TIEntity& build();
    private:
        sf::Vector2f position = sf::Vector2f(0, 0);
        sf::Vector2f size = sf::Vector2f(0, 0);
        std::string text = "";
        GlobalId onClickId = 0;
        std::function<void(Message&)> onClick = nullptr;
        bool drawn = true;

		static const inline std::string TEXT  = "text";
		static const inline std::string ON_CLICK = "onClick";

};

}

#endif 
