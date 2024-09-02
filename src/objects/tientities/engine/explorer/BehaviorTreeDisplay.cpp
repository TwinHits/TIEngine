#include "objects/tientities/engine/explorer/BehaviorTreeDisplay.h"

#include <SFML/Graphics.hpp>

#include "ai/behaviortree/nodes/BehaviorTreeNode.h"
#include "componentsystems/PositionComponentSystem.h"
#include "objects/components/BehavesComponent.h"
#include "objects/tientities/TIEntity.h"
#include "objects/tientities/engine/explorer/BehaviorTreeDisplayNode.h"

using namespace TIE;

BehaviorTreeDisplay::BehaviorTreeDisplay(TIEntity& tientity, const sf::Vector2f& displayArea) {
    this->displayArea = displayArea;
    this->setTIEntity(tientity);
}


void BehaviorTreeDisplay::setTIEntity(TIEntity& tientity) {
    this->tientity = &tientity;
    this->setRemoveChildren(true);
    this->createBehaviorTreeNodes();
}


void BehaviorTreeDisplay::createBehaviorTreeNodes() {
    BehavesComponent* behavesComponent = this->tientity->getComponent<BehavesComponent>();
    if (behavesComponent && behavesComponent->rootBehaviorTreeNode) {

        BehaviorTreeNode& rootNode = *behavesComponent->rootBehaviorTreeNode;
        std::map<int, std::vector<BehaviorTreeDisplayNode*>> rowDisplayNodeMap;
        this->createBehaviorTreeNodes(rowDisplayNodeMap, rootNode, nullptr, 1);

        for (auto& pair : rowDisplayNodeMap) {
            int row = pair.first;
            int column = 1;
            float columnSize = this->displayArea.x / pair.second.size();
            float rowSize = this->displayArea.y / rowDisplayNodeMap.size();
            for (auto& behaviorTreeDisplayNode : pair.second) {
                float x = (column * columnSize) - (columnSize / 2);
                float y = (row * rowSize) - (rowSize / 2);
                PositionComponentSystem::Instance()->setPosition(*behaviorTreeDisplayNode, sf::Vector2f(x, y));
                behaviorTreeDisplayNode->addLineToParent();
                column++;
            }
        }
    }
}


void BehaviorTreeDisplay::createBehaviorTreeNodes(std::map<int, std::vector<BehaviorTreeDisplayNode*>>& rowDisplayNodeMap, BehaviorTreeNode& node, BehaviorTreeDisplayNode* parentNode, const int row) {

    if (!rowDisplayNodeMap.count(row)) {
        rowDisplayNodeMap[row];
    }

    BehaviorTreeDisplayNode* behaviorTreeDisplayNode = dynamic_cast<BehaviorTreeDisplayNode*>(&this->attachChild(make_unique<BehaviorTreeDisplayNode>(node, parentNode, size)));
    rowDisplayNodeMap[row].push_back(behaviorTreeDisplayNode);
    for (auto& child : node.getChildren()) {
        createBehaviorTreeNodes(rowDisplayNodeMap, *child, behaviorTreeDisplayNode, row+1);
    }
}
