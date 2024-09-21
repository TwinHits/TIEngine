#ifndef MENUFACTORY_H
#define MENUFACTORY_H 

#include "objects/factories/tientities/TIEntityFactory.h"

#include "sol/sol.hpp"

#include <string>

#include "objects/Message.h"
#include "objects/ScriptTableReader.h"
#include "objects/tientities/TIEntity.h"


namespace TIE {

    class MenuFactory : public TIEntityFactory {
    public:
        MenuFactory();
        MenuFactory(const sol::table&);
        ~MenuFactory() {};

        MenuFactory& setPosition(const sf::Vector2f&);
        MenuFactory& setOnClick(const std::function<void(Message&)>);
        MenuFactory& setDrawn(const bool);

        TIEntity& build(const ScriptTableReader&);
        TIEntity& build();
    private:
        sf::Vector2f position = sf::Vector2f(0, 0);
        std::function<void(Message&)> onClick = nullptr;
        bool drawn = true;

		static const inline std::string BUTTONS  = "buttons";
		static const inline std::string ON_CLICK = "onClick";
    };

}

#endif