#ifndef COMPONENTSYSTEMS_UTILS_H
#define COMPONENTSYSTEMS_UTILS_H

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/tientities/TIEntity.h"
#include "utils/types/ComponentSystemsTypes.h"

namespace TIE {
    namespace ComponentSystems {

        void setDrawn(TIEntity&, bool);
        bool isDrawn(TIEntity&);
        const sf::FloatRect getGlobalBounds(TIEntity&);
        const sf::FloatRect getLocalBounds(TIEntity&);
        bool doesGlobalBoundsContain(TIEntity&, const sf::Vector2f&);

    }
}

#endif