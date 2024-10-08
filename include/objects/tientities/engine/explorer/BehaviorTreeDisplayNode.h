#ifndef BEHAVIORTREEDISPLAYNODE_H
#define BEHAVIORTREEDISPLAYNODE_H

#include "objects/tientities/TIEntity.h"

#include "SFML/Graphics.hpp"

#include "ai/behaviortree/nodes/BehaviorTreeNode.h"
#include "objects/Message.h"
#include "objects/components/TextComponent.h"

namespace TIE {

class BehaviorTreeDisplayNode : public TIEntity {

    public:
        BehaviorTreeDisplayNode(BehaviorTreeNode&, BehaviorTreeDisplayNode*, const sf::Vector2f&);
        ~BehaviorTreeDisplayNode() {};

        void addLineToParent();

        virtual void update(const float);

    private:
        BehaviorTreeDisplayNode* parentDisplayNode = nullptr;
        sf::Vector2f size = sf::Vector2f(0,0);
        short isNodeHighlightedTernaryFlag = 0;

        BehaviorTreeNode& behaviorTreeNode;
        sf::RectangleShape* rectangleShape = nullptr;
        sf::RectangleShape* lineShape = nullptr;
        TextComponent* textComponent;

        void onEvent(Message& message);

};

}

#endif
