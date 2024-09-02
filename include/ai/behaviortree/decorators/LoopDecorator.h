#ifndef LOOPDECORATOR_H
#define LOOPDECORATOR_H

#include "ai/behaviortree/decorators/NodeDecorator.h"

#include "enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class LoopDecorator : public NodeDecorator {
    public:
        LoopDecorator(TIEntity&);
        
        virtual BehaviorTree::NodeStatus update(const float);
    private:

};

}

#endif
