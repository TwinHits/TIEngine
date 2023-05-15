#ifndef COMPONENTPROPERTIESDISPLAY_H
#define COMPONENTPROPERTIESDISPLAY_H

#include "componentsystems/ComponentSystem.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class ComponentPropertiesDisplay : public TIEntity {
    public:
        ComponentPropertiesDisplay();
        ~ComponentPropertiesDisplay() {};

        void update(const float);

		void onWindowSizeChange();
    private:
        void setPosition(const sf::Vector2i&);
        void setSize(const sf::Vector2i&);

        std::vector<ComponentSystem*> componentSystemsToDisplay;
};

}

#endif COMPONENTPROPERTIESDISPLAY_H

