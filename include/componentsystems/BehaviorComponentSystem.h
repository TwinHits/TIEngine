#ifndef BEHAVIORCOMPONENTSYSTEM_H
#define BEHAVIORCOMPONENTSYSTEM_H

#include "templates/Singleton.h"
#include "componentsystems/ComponentSystem.h"

#include <vector>

#include "objects/components/BehaviorComponent.h"

namespace TIE {

class BehaviorComponentSystem : public Singleton<BehaviorComponentSystem>, ComponentSystem {

public:
    BehaviorComponentSystem() {};
    void update(const float);
    void addComponent(const TIEntityFactory&, TIEntity&);

    static const std::string BEHAVIORS;
    static const std::string BEHAVIOR;
    static const std::string BEHAVES;
private:
    struct Components {
        TIEntity& tientity;
        BehaviorComponent& behaviorComponent;
    };
    std::vector<Components> components;
};

}

#endif