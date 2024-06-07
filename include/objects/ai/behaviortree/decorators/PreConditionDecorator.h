#ifndef PRECONDITIONDECORATOR_H
#define PRECONDITIONDECORATOR_H

#include "objects/ai/behaviortree/decorators/NodeDecorator.h"

#include "objects/tientities/TIEntity.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/GlobalId.h"

namespace TIE {

class PreConditionDecorator : public NodeDecorator {
    public:
        PreConditionDecorator(TIEntity&);
        virtual BehaviorTree::NodeStatus update(const float);

        void setPreConditonFunctionId(const GlobalId);

    private:
        GlobalId preConditionFunctionId = 0;
};

}

#endif 