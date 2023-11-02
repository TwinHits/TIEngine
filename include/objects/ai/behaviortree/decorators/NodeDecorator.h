#ifndef NODEDECORATOR_H
#define NODEDECORATOR_H

#include "objects/enumeration/NodeStatus.h"

namespace TIE {

class NodeDecorator {
    public:
        NodeDecorator(BehaviorTreeNode& node) : node(node) {}
        virtual BehaviorTree::NodeStatus update(const float delta) = 0;
    protected:
        BehaviorTreeNode& node;

};

}

#endif 
