#ifndef BUTTON_H
#define BUTTON_H

#include "objects/tientities/ui/UIElement.h"

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/Message.h"

namespace TIE {

class Button : public UIElement {
    public:
        Button(const std::string, const sf::Vector2f&, const sf::Vector2f&, std::function<void(Message&)>);
        ~Button() {};
};

}

#endif