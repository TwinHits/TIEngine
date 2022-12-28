#ifndef ANIMATEDCOMPONENTSYSTEM_H
#define ANIMATEDCOMPONENTSYSTEM_H

#include "componentsystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <vector>

#include "objects/components/AnimatedComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"

namespace TIE {

class AnimatedComponentSystem : public Singleton<AnimatedComponentSystem>, public ComponentSystem {
    public:
        AnimatedComponentSystem();
        void update(const float);
        bool hasComponent(const TIEntity&);
        AnimatedComponent& addComponent(TIEntity&);
        AnimatedComponent& addComponent(const TIEntityFactory&, TIEntity&);
        bool removeComponent(TIEntity&);
        const std::string& getName();
        
		bool setComponentProperty(const std::string&, bool, TIEntity&);
		bool setComponentProperty(const std::string&, float, TIEntity&);
		bool setComponentProperty(const std::string&, const std::string&, TIEntity&);
        sol::object getComponentProperty(const std::string&, TIEntity&);

        static const inline std::string ANIMATED = "animated";
		static const inline std::string FRAMES = "frames";
		static const inline std::string RANGE = "range";
		static const inline std::string SPEED = "speed";
		static const inline std::string DIRECTION = "direction";

    private:
        struct Components {
            AnimatedComponent& animatedComponent;
            PositionComponent& positionComponent;
            SpriteComponent& spriteComponent;
        };
        std::list<Components> components;
        
        bool progressAnimation(Animation*, const float);
        void setTextureRect(const Animation&, SpriteComponent&);
        void updateCurrentAnimation(AnimatedComponent&, PositionComponent&, SpriteComponent&);
};

}

#endif
