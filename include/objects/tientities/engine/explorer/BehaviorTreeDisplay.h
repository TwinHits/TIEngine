#ifndef BEHAVIORTREEDISPLAY_H
#define BEHAVIORTREEDISPLAY_H

#include "objects/tientities/TIEntity.h"

#include <SFML/Graphics.hpp>

#include "objects/components/BehavesComponent.h"

namespace TIE {

class BehaviorTreeDisplay : public TIEntity {
    public:
        BehaviorTreeDisplay(TIEntity&);
        ~BehaviorTreeDisplay() {};

        void setTIEntity(TIEntity&);

    private:
        TIEntity* tientity;
        std::map<int, std::vector<TIEntity*>> behaviorTreeNodeTIEntities;
        sf::Vector2f size = sf::Vector2f(175, 50);
        float xPadding = 25;
        float yPadding = 25;

        void generateBehaviorTreeTIEntities(BehavesComponent&);
        void generateBehaviorTreeTIEntity(BehaviorTreeNode&, const int);
};

}


#endif 
