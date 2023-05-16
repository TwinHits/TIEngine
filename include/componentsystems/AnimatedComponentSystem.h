#ifndef ANIMATEDCOMPONENTSYSTEM_H
#define ANIMATEDCOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <vector>

#include "objects/components/AnimatedComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/tientities/TIEntity.h"
#include "objects/factories/tientities/TIEntityFactory.h"

namespace TIE {

class AnimatedComponentSystem : public Singleton<AnimatedComponentSystem>, public OwnsComponent<AnimatedComponent> {
    public:
        AnimatedComponentSystem();
        void update(const float);
        AnimatedComponent& addComponent(TIEntity&);
        AnimatedComponent& addComponent(const TIEntityFactory&, TIEntity&);
        bool removeComponent(TIEntity&);
        
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
