#ifndef UIELEMENTFACTORY_H
#define UIELEMENTFACTORY_H 

#include "objects/factories/tientities/TIEntityFactory.h"

#include "sol/sol.hpp"
#include "SFML/Graphics.hpp"

#include "objects/ScriptTableReader.h"
#include "objects/tientities/TIEntity.h"

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

        TIEntity& build();
    private:
        bool drawn = false;
        sf::Vector2f position = sf::Vector2f(0, 0);
        sf::Vector2f size = sf::Vector2f(0, 0);

};

}

#endif 
