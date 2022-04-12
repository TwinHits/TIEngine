#ifndef BEHAVIORCOMPONENTSYSTEM_H
#define BEHAVIORCOMPONENTSYSTEM_H

#include "templates/Singleton.h"
#include "componentsystems/ComponentSystem.h"

#include <string>
#include <vector>

#include "objects/GlobalId.h"
#include "objects/components/BehaviorComponent.h"

namespace TIE {

class BehaviorComponentSystem : public Singleton<BehaviorComponentSystem>, public ComponentSystem {

public:
    BehaviorComponentSystem() {};
    void update(const float);
    void addComponent(const TIEntityFactory&, TIEntity&);
    bool removeComponent(TIEntity&);
    const std::string& getName();

    bool setComponentProperty(const std::string&, bool, TIEntity&);
    bool setComponentProperty(const std::string&, float, TIEntity&);
    bool setComponentProperty(const std::string&, const std::string&, TIEntity&);
    std::string getComponentProperty(const std::string&, TIEntity&);

    void setBehavior(TIEntity&, GlobalId);
    void setBehavior(TIEntity&, const std::string&);

    static const inline std::string BEHAVIORS = "behaviors";
    static const inline std::string BEHAVIOR = "behaves.behavior";
    static const inline std::string BEHAVES = "behaves";

private:
    struct Components {
        TIEntity& tientity;
        BehaviorComponent& behaviorComponent;
    };
    std::list<Components> components;
};

}

#endif