#ifndef ANIMATEDCOMPONENTSYSTEM_H
#define ANIMATEDCOMPONENTSYSTEM_H

#include "componentsystems/ComponentSystem.h"

#include "objects/components/AnimatedComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"

namespace TIE {

class AnimatedComponentSystem : public ComponentSystem {
    public:
        void update(TIEntity&, const float);
        static AnimatedComponent* addComponent(TIEntityFactory&, TIEntity&);

		static const std::string ANIMATED;
		static const std::string FRAMES;
		static const std::string RANGE;
		static const std::string SPEED;
		static const std::string DIRECTION;
    private:
        bool progressAnimation(Animation*, const float);
        static void setTextureRect(const Animation&, SpriteComponent&);
        static void updateCurrentAnimation(AnimatedComponent&, TIEntity&);
};

}

#endif
