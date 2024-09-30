#ifndef TIENTITYEXPLORER_H
#define TIENTITYEXPLORER_H

#include "objects/tientities/common/SceneLayer.h"

#include <map>

#include <SFML/Graphics.hpp>

#include "objects/Message.h"
#include "objects/tientities/engine/explorer/BehaviorTreeDisplay.h"
#include "objects/tientities/engine/explorer/ComponentPropertiesDisplay.h"

namespace TIE {

class TIEntityExplorer : public SceneLayer {
    public:
        TIEntityExplorer();
        ~TIEntityExplorer() {};

        void update(const float);

    private:
        TIEntity* selectedTIEntity = nullptr;
        SceneLayer* buttonSceneLayer = nullptr;
        ComponentPropertiesDisplay* componentPropertiesDisplay = nullptr;
        BehaviorTreeDisplay* behaviorTreeDisplay = nullptr;

        bool show = false;
        sf::Vector2f componentPropertiesDisplayPosition = sf::Vector2f(0, 0);
        sf::Vector2f tientitiesDisplayPosition = sf::Vector2f(0, 0);
        sf::Vector2f behaviorTreeDisplayPosition = sf::Vector2f(0, 0);
        std::map<GlobalId, TIEntity*> buttonToChild;

        void setBackgroundSize(const sf::Vector2i&);
        void setBackgroundPosition(const sf::Vector2i&);
        void setAreaPositions(const sf::Vector2i&);
        void setComponentPropertiesDisplay();
        void setBehaviorTreeDisplay();

        void createButtons();

        void onToggleShowHide();
        void onWindowSizeChange();

        void onButtonClick(Message& message);

};

}

#endif
