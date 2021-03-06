#ifndef BEHAVIORCOMPONENT_H
#define BEHAVIORCOMPONENT_H

#include "objects/components/Component.h"
#include "objects/GlobalId.h"

namespace TIE {

class BehaviorComponent : public Component {

public:
    BehaviorComponent() {};
    virtual ~BehaviorComponent() {};

    GlobalId behaviorFunctionId = 0;
};

}

#endif