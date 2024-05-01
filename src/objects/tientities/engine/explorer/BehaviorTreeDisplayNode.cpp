#include "objects/tientities/engine/explorer/BehaviorTreeDisplayNode.h"

#include "SFML/Graphics.hpp"

#include "componentsystems/BehavesComponentSystem.h"
#include "componentsystems/EventsComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/ShapeComponentSystem.h"
#include "objects/Message.h"
#include "objects/ai/behaviortree/nodes/BehaviorTreeNode.h"
#include "objects/components/ShapeComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/enumeration/NodeStatus.h"
#include "utils/TIEMath.h"

using namespace TIE;

BehaviorTreeDisplayNode::BehaviorTreeDisplayNode(BehaviorTreeNode& behaviorTreeNode, BehaviorTreeDisplayNode* parentDisplayNode, const sf::Vector2f& size) : behaviorTreeNode(behaviorTreeNode) {
    this->setName("Behavior Tree Display Node");
    this->parentDisplayNode = parentDisplayNode;
    this->size = size;
    
    ShapeComponent& shapeComponent = ShapeComponentSystem::Instance()->addComponent(*this);
    shapeComponent.setDrawn(true);
    
    this->rectangleShape = &shapeComponent.addRectangleShape();
    this->rectangleShape->setSize(size);
    this->rectangleShape->setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
    this->rectangleShape->setOutlineThickness(2);
    this->rectangleShape->setFillColor(sf::Color::Transparent);

    this->textComponent = &TextComponentSystem::Instance()->addComponent(*this);
    this->textComponent->setString(this->behaviorTreeNode.getName() + "\n" + this->behaviorTreeNode.getNodeType());
    this->textComponent->setTextAlignment(TextAlignment::CENTER);
    this->textComponent->setCharacterSize(16);
    this->textComponent->setDrawn(true);

    EventsComponentSystem::Instance()->subscribe(*this, BehavesComponentSystem::Instance()->getMessageSubscriptionForNodeStatus(BehaviorTree::NodeStatus::SUCCESS), std::bind(&BehaviorTreeDisplayNode::onEvent, this, std::placeholders::_1));
    EventsComponentSystem::Instance()->subscribe(*this, BehavesComponentSystem::Instance()->getMessageSubscriptionForNodeStatus(BehaviorTree::NodeStatus::RUNNING), std::bind(&BehaviorTreeDisplayNode::onEvent, this, std::placeholders::_1));
    EventsComponentSystem::Instance()->subscribe(*this, BehavesComponentSystem::Instance()->getMessageSubscriptionForNodeStatus(BehaviorTree::NodeStatus::FAILURE), std::bind(&BehaviorTreeDisplayNode::onEvent, this, std::placeholders::_1));
}


void BehaviorTreeDisplayNode::addLineToParent() {
    if (this->parentDisplayNode) {
        TIEntity& lineTIEntity = this->attachChild();

        sf::Vector2f position = PositionComponentSystem::Instance()->getWorldPosition(*this);
        sf::Vector2f linePosition = sf::Vector2f(0, -this->size.y / 2 - 2); // half of height of button minus outline thickness
        sf::Vector2f lineOriginPosition = position + linePosition;
        sf::Vector2f parentPosition = PositionComponentSystem::Instance()->getWorldPosition(*this->parentDisplayNode);
        sf::Vector2f lineDestinationPosition = parentPosition - linePosition;

        float direction = TIE::Math::angleBetweenTwoPoints(lineOriginPosition, lineDestinationPosition);
        float magnitude = TIE::Math::distanceBetweenTwoPoints(lineOriginPosition, lineDestinationPosition);
        PositionComponentSystem::Instance()->setRotation(lineTIEntity, direction);
        PositionComponentSystem::Instance()->setPosition(lineTIEntity, linePosition);

        ShapeComponent& shapeComponent = ShapeComponentSystem::Instance()->addComponent(lineTIEntity);
        this->lineShape = &shapeComponent.addRectangleShape();
        this->lineShape->setFillColor(sf::Color::White);
        this->lineShape->setOutlineColor(sf::Color::White);
        this->lineShape->setSize(sf::Vector2f(magnitude, 1));
    }
}


/**
    Since update on engine tientities is called after update on component systems, if the node is highlighted it will be immediately un-highlighted.
    So, set a flag so that in the update immediately following an onEvent un-highlighting is skipped until the next update.
    This would mean a lot of unnecessary calls to setting the color, so use a three-state flag or ternary flag to only un-highlight once after the onEvent is run.
**/
void BehaviorTreeDisplayNode::update(const float delta) {
    if (this->isNodeHighlightedTernaryFlag == 2) {
        this->rectangleShape->setFillColor(sf::Color::Transparent);
        this->textComponent->setFillColor(sf::Color::White);
        this->textComponent->setOutlineColor(sf::Color::White);
        if (this->lineShape) {
            this->lineShape->setFillColor(sf::Color::White);
            this->lineShape->setOutlineColor(sf::Color::White);
        }
        this->isNodeHighlightedTernaryFlag = 0;
    } else if (this->isNodeHighlightedTernaryFlag == 1) {
        this->isNodeHighlightedTernaryFlag = 2;
    }
}


void BehaviorTreeDisplayNode::onEvent(Message& message) {
    BehaviorTree::NodeStatus nodeStatus = BehavesComponentSystem::Instance()->getNodeStatusForMessageSubscription(message.subscription);
    sf::Color fillColor;
    if (nodeStatus == BehaviorTree::NodeStatus::SUCCESS) {
        fillColor = sf::Color::Green;
    } else if (nodeStatus == BehaviorTree::NodeStatus::RUNNING) {
        fillColor = sf::Color(255,255,158, 255);
    } else if (nodeStatus == BehaviorTree::NodeStatus::FAILURE) {
        fillColor = sf::Color::Red;
    }

    if (message.senderId == this->behaviorTreeNode.getId()) {
        this->rectangleShape->setFillColor(fillColor);
        this->textComponent->setFillColor(sf::Color::Black);
        this->textComponent->setOutlineColor(sf::Color::Black);
        if (this->lineShape) {
            this->lineShape->setFillColor(fillColor);
            this->lineShape->setOutlineColor(fillColor);
        }
        this->isNodeHighlightedTernaryFlag = 1;
    }
}
