#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "objects/components/Component.h"

#include <SFML/Graphics.hpp>

namespace TIE {

class PositionComponent : public Component {
    public:
        void setPosition(const sf::Vector2f& position);
        const sf::Vector2f& getPosition();

        void setAngle(const float);
        float getAngle();
    private:
        sf::Vector2f position = sf::Vector2f(0, 0);
        float angle = 0;
};

}

#endif