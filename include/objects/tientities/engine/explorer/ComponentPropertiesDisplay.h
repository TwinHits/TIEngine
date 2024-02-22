#ifndef COMPONENTPROPERTIESDISPLAY_H
#define COMPONENTPROPERTIESDISPLAY_H

#include "componentsystems/ComponentSystem.h"
#include "objects/components/TextComponent.h"
#include "objects/tientities/TIEntity.h"

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

