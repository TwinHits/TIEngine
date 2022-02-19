#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "objects/components/Component.h"

#include <SFML/Graphics.hpp>

namespace TIE {

class PositionComponent : public Component {
    public:
        sf::Vector2f position = sf::Vector2f(0, 0);
        float rotation = 0.0f;

        sf::Vector2f worldPosition = sf::Vector2f(0, 0);
        float worldRotation = 0.0f;

        bool rotates = true;
};

}

#endif