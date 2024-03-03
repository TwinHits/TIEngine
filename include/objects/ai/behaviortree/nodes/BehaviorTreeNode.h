#ifndef BEHAVIORTREENODE_H
#define BEHAVIORTREENODE_H

#include <memory>
#include <string>
#include <vector>

#include "objects/GlobalId.h"
#include "objects/Message.h"
#include "objects/ai/behaviortree/decorators/NodeDecorator.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class BehaviorTreeNode {
    public:
        BehaviorTreeNode(TIEntity&, const std::string&);
        virtual ~BehaviorTreeNode() {}

        TIEntity& getTIEntity();
        const std::string& getName();
        const std::string& getNodeType();

        BehaviorTree::NodeStatus updatePreDecorators(float);
        virtual BehaviorTree::NodeStatus update(float) = 0;
        BehaviorTree::NodeStatus updatePostDecorators(float);

        void addPreDecorator(std::unique_ptr<NodeDecorator>);
        void addChild(std::unique_ptr<BehaviorTreeNode>);
        const std::vector<std::unique_ptr<BehaviorTreeNode>>& getChildren();
        void addPostDecorator(std::unique_ptr<NodeDecorator>);

    protected:
        TIEntity& tientity;
        std::string name;
        std::string nodeType;

        std::vector<std::unique_ptr<NodeDecorator>> preDecorators;
        std::vector<std::unique_ptr<BehaviorTreeNode>> children;
        std::vector<std::unique_ptr<NodeDecorator>> postDecorators;
        NodeDecorator* resumeDecorator = nullptr;

        BehaviorTree::NodeStatus updateDecorators(const std::vector<std::unique_ptr<NodeDecorator>>&, float);
};

}

#endif