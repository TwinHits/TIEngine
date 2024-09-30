#ifndef UIELEMENTFACTORY_H
#define UIELEMENTFACTORY_H 

#include "objects/factories/tientities/TIEntityFactory.h"

#include <string>

#include <sol/sol.hpp>
#include <SFML/Graphics.hpp>

namespace TIE {

class UIElementFactory : public TIEntityFactory {
    public:
        UIElementFactory();
        UIElementFactory(const sol::table&);
        UIElementFactory(const ScriptTableReader&);
        ~UIElementFactory() {};

        UIElementFactory& setDrawn(const bool);
        const bool getDrawn();

        UIElementFactory& setPosition(const sf::Vector2f&);
        const sf::Vector2f& getPosition();

        UIElementFactory& setSize(const sf::Vector2f&);
        const sf::Vector2f& getSize();

        UIElementFactory& setText(const std::string&);
        const std::string& getText();

        UIElementFactory& setOnEventId(const GlobalId);
        const GlobalId getOnEventId();

        TIEntity& build();
    private:
        bool drawn = false;
        sf::Vector2f position = sf::Vector2f(0, 0);
        sf::Vector2f size = sf::Vector2f(0, 0);
        std::string text = "";
        GlobalId onEventId = 0;
        
		static const inline std::string DRAWN = "drawn";
		static const inline std::string TEXT = "text";
		static const inline std::string POSITION_X = "x";
		static const inline std::string POSITION_Y = "y";
		static const inline std::string ON_EVENT_ID = "onEvent";
};

}

#endif 
