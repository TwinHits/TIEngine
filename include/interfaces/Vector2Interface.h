#ifndef VECTOR2INTERFACE_H
#define VECTOR2INTERFACE_H

#include <sol/sol.hpp>
#include <SFML/Graphics.hpp>

namespace TIE {
    namespace Vector2Interface {
        static void registerUserType(sol::state& luaState) {
            sol::usertype<sf::Vector2f> vector2fUserType = luaState.new_usertype<sf::Vector2f>("Vector2f");
            vector2fUserType["x"] = &sf::Vector2f::x;
            vector2fUserType["y"] = &sf::Vector2f::y;

            sol::usertype<sf::Vector2i> vector2iUserType = luaState.new_usertype<sf::Vector2i>("Vector2i");
            vector2iUserType["x"] = &sf::Vector2i::x;
            vector2iUserType["y"] = &sf::Vector2i::y;
        };
    }
}

#endif
