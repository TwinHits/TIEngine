#ifndef BEHAVIORCOMPONENTSYSTEM_H
#define BEHAVIORCOMPONENTSYSTEM_H

#include "templates/Singleton.h"
#include "componentsystems/ComponentSystem.h"

#include <vector>

#include "objects/components/BehaviorComponent.h"

namespace TIE {

class BehaviorComponentSystem : public Singleton<BehaviorComponentSystem>, public ComponentSystem {

public:
    BehaviorComponentSystem() {};
    void update(const float);
    void addComponent(const TIEntityFactory&, TIEntity&);
    const std::string& getName();

    static const inline std::string BEHAVIORS = "behaviors";
    static const inline std::string BEHAVIOR = "behaves.behavior";
    static const inline std::string BEHAVES = "behaves";

private:
    struct Components {
        TIEntity& tientity;
        BehaviorComponent& behaviorComponent;
    };
    std::vector<Components> components;
};

}

#endif