#include "objects/tientities/engine/explorer/BehaviorTreeDisplay.h"

#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/ShapeComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"
#include "objects/ai/behaviortree/nodes/BehaviorTreeNode.h"
#include "objects/components/BehavesComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/components/ShapeComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

BehaviorTreeDisplay::BehaviorTreeDisplay(TIEntity& tientity) {
    this->setTIEntity(tientity);
}


void BehaviorTreeDisplay::setTIEntity(TIEntity& tientity) {
    this->tientity = &tientity;
    this->setRemoveChildren(true);
    this->behaviorTreeNodeTIEntities.clear();
    
    BehavesComponent* behavesComponent = this->tientity->getComponent<BehavesComponent>();
    if (this->tientity->hasComponent<BehavesComponent>()) {
        this->generateBehaviorTreeTIEntities(*behavesComponent);
    }
}


void BehaviorTreeDisplay::generateBehaviorTreeTIEntities(BehavesComponent& behavesComponent) {
    BehaviorTreeNode* root = behavesComponent.rootBehaviorTreeNode.get();
    if (root) {
        this->generateBehaviorTreeTIEntity(*root, 1);
    }
}


void BehaviorTreeDisplay::generateBehaviorTreeTIEntity(BehaviorTreeNode& node, const int depth) {
    /*
    * I want a box for each node entity and a line to each of it's children.
    * Tientites of the same depth should have the same y axix and equally spaced x axis
    * these values can be stored using a map of std::map<int, float> where the key is the depth and the float is the current x padding
    * You can multiply the key by the constnat y padding to get the y location

    this requires me to pass down additional info through the recursive function
    am i just being too lazy to creat the right data structure
    std::map<int, std<<vector<TIEntity*>> ?
    no matter what i probably have to pass down the depth
    This would support dynamic resizing, where just holding the numbers wouldn't.
    * 
    * The buttons are stored as children, do they need to know about each other?
    * Well, I'm going to want to light them up when they are hit, which means I need references to them. That can just be a map later.
    * 
    * Need a better name for this kind of object, which will almost certainly be a class.
    **/
    TIEntity& behaviorTreeTIEntity = this->attachChild();
    behaviorTreeTIEntity.setName("Behavior Tree Node TIEntity");

    if (!behaviorTreeNodeTIEntities.count(depth)) {
        behaviorTreeNodeTIEntities[depth];
    }
    behaviorTreeNodeTIEntities.at(depth).push_back(&behaviorTreeTIEntity);

    const sf::Vector2f position = sf::Vector2f(
        behaviorTreeNodeTIEntities.at(depth).size() * (this->size.x + this->xPadding), 
        depth * (this->size.y + this->yPadding)
    );
    PositionComponentSystem::Instance()->setPosition(behaviorTreeTIEntity, position);
    
    ShapeComponent& shapeComponent = ShapeComponentSystem::Instance()->addComponent(behaviorTreeTIEntity);
    shapeComponent.setDrawn(true);
    
    sf::RectangleShape& rectangleShape = shapeComponent.addRectangleShape();
    rectangleShape.setSize(this->size);
    rectangleShape.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
    rectangleShape.setOutlineThickness(2);
    rectangleShape.setOutlineColor(sf::Color::White);
    rectangleShape.setFillColor(sf::Color::Transparent);

    TextComponent& textComponent = TextComponentSystem::Instance()->addComponent(behaviorTreeTIEntity);
    textComponent.setString(node.getName());
    textComponent.setTextAlignment(TextAlignment::CENTER);
    textComponent.setCharacterSize(16);
    // get node type, needs to be implemetned in BehaviorTreeNode
    textComponent.setDrawn(true);
    
    for (auto& childNode : node.getChildren()) {
        this->generateBehaviorTreeTIEntity(*childNode, depth + 1);
    }
}
