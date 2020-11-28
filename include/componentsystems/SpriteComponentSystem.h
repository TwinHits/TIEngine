#ifndef SPRITECOMPONENTSYSTEM_H
#define SPRITECOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <string>

#include "objects/components/PositionComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"

namespace TIE {

class SpriteComponentSystem : public Singleton<SpriteComponentSystem>, public ComponentSystem {
	public:
		SpriteComponentSystem() {};
		void update(const float);
		void addComponent(const TIEntityFactory&, TIEntity&);
		const std::string& getName();

		static const std::string DRAWN;
		static const std::string TEXTURE;
		static const std::string ROTATION;
		static const std::string WIDTH;
		static const std::string HEIGHT;
		static const std::string REPEATED;
		static const std::string POSITION_X;
		static const std::string POSITION_Y;
	private: 
		struct Components {
			SpriteComponent& spriteComponent;
			PositionComponent& positionComponent;
		};
		std::vector<Components> components;
};

}
#endif 
