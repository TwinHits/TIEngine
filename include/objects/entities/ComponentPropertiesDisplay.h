#ifndef COMPONENTPROPERTIESDISPLAY_H
#define COMPONENTPROPERTIESDISPLAY_H

#include "componentsystems/ComponentSystem.h"
#include "objects/entities/TIEntity.h"

namespace TIE {

class ComponentPropertiesDisplay : public TIEntity {
    public:
        ComponentPropertiesDisplay();
        ~ComponentPropertiesDisplay() {};

        void update(const float);

    private:
        std::vector<ComponentSystem*> componentSystemsToDisplay;
};

}

#endif COMPONENTPROPERTIESDISPLAY_H

