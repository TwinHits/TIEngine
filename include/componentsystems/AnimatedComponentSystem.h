#ifndef ANIMATEDCOMPONENTSYSTEM_H
#define ANIMATEDCOMPONENTSYSTEM_H

#include "componentsystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <vector>

#include "objects/components/AnimatedComponent.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"

namespace TIE {

// Animated
// Sprite

class AnimatedComponentSystem : public Singleton<AnimatedComponentSystem>, ComponentSystem {
    public:
        AnimatedComponentSystem() {};
        void update(TIEntity&, const float) {};
        void update(const float);
        void addComponent(const TIEntityFactory&, TIEntity&);

		static const std::string ANIMATED;
		static const std::string FRAMES;
		static const std::string RANGE;
		static const std::string SPEED;
		static const std::string DIRECTION;
    private:
        struct Components {
            AnimatedComponent& animatedComponent;
            SpriteComponent& spriteComponent;
            MovesComponent& movesComponent;
        };
        std::vector<Components> components;
        
        bool progressAnimation(Animation*, const float);
        void setTextureRect(const Animation&, SpriteComponent&);
        void updateCurrentAnimation(Components&);
};

}

#endif
