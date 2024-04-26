#ifndef BEHAVIORTREEDISPLAY_H
#define BEHAVIORTREEDISPLAY_H

#include "objects/tientities/TIEntity.h"

#include <SFML/Graphics.hpp>

#include "objects/components/BehavesComponent.h"
#include "objects/tientities/engine/explorer/BehaviorTreeDisplayNode.h"

namespace TIE {

class BehaviorTreeDisplay : public TIEntity {
    public:
        BehaviorTreeDisplay(TIEntity&, const sf::Vector2f&);
        ~BehaviorTreeDisplay() {};

        void setTIEntity(TIEntity&);

    private:
        sf::Vector2f size = sf::Vector2f(175, 50);
        float xPadding = 25;
        float yPadding = 25;

        TIEntity* tientity = nullptr;
        sf::Vector2f displayArea = sf::Vector2f(0,0);

        void createBehaviorTreeNodes();
        void createBehaviorTreeNodes(std::map<int, std::vector<BehaviorTreeDisplayNode*>>&, BehaviorTreeNode&, BehaviorTreeDisplayNode*, const int);
};

}


#endif 
