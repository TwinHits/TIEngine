#ifndef COMPONENTSYSTEMS_UTILS_H
#define COMPONENTSYSTEMS_UTILS_H

#include <string>

#include "objects/ScriptTableReader.h"
#include "objects/tientities/TIEntity.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "managers/ScriptManager.h"
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