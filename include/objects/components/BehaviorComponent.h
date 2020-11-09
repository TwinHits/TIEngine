#ifndef BEHAVOIRCOMPONENT_H
#define BEHAVOIRCOMPONENT_H

#include "objects/components/Component.h"

namespace TIE {

class BehaviorComponent : public Component {

public:
    BehaviorComponent() {};
    virtual ~BehaviorComponent() {};

    std::string behavior = "";
    std::vector<std::string> instructions;
    std::vector<std::string>::iterator currentInstruction = instructions.end();
};

}

#endif