#ifndef NODEDECORATOR_H
#define NODEDECORATOR_H

#include "enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class NodeDecorator {
    public:
        NodeDecorator(TIEntity& tientity);
        virtual BehaviorTree::NodeStatus update(const float delta) = 0;
    protected:
        TIEntity& tientity;
};

}

#endif 
