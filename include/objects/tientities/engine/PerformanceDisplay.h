#ifndef PERFORMANCEDISPLAY_H
#define PERFORMANCEDISPLAY_H

#include "objects/tientities/TIEntity.h"

#include <SFML/Graphics.hpp>

#include "objects/components/TextComponent.h"

namespace TIE {

class PerformanceDisplay : public TIEntity {
    public:
        PerformanceDisplay();
        ~PerformanceDisplay() {};

        void update(const float);

        void onWindowSizeChange();
    private:
        TextComponent& textComponent = this->addComponent<TextComponent>();
        float fps = 0.0f;
        int framesCounter = 0;
        sf::Clock& clock;

        void setPosition();
};

}

#endif 
