#ifndef COMPONENTPROPERTIESDISPLAY_H
#define COMPONENTPROPERTIESDISPLAY_H

#include "objects/tientities/TIEntity.h"

#include "componentsystems/ComponentSystem.h"
#include "objects/components/TextComponent.h"

namespace TIE {

class ComponentPropertiesDisplay : public TIEntity {
    public:
        ComponentPropertiesDisplay();
        ~ComponentPropertiesDisplay() {};

        void update(const float);

        void setTIEntity(TIEntity* tientity);

    private:
        TIEntity* tientity;
        TextComponent& textComponent;
        std::vector<ComponentSystem*> componentSystemsToDisplay;
};

}

#endif COMPONENTPROPERTIESDISPLAY_H

