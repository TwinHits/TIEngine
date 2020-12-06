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
		bool removeComponent(TIEntity&);
		const std::string& getName();

		static const inline std::string DRAWN = "drawn";
		static const inline std::string TEXTURE = "drawn.texture";
		static const inline std::string ROTATION = "drawn.rotation";
		static const inline std::string WIDTH = "drawn.width";
		static const inline std::string HEIGHT = "drawn.height";
		static const inline std::string REPEATED = "drawn.repeated";
		static const inline std::string POSITION_X = "drawn.position.x";
		static const inline std::string POSITION_Y = "drawn.position.y";
	private: 
		struct Components {
			SpriteComponent& spriteComponent;
			PositionComponent& positionComponent;
		};
		std::list<Components> components;
};

}
#endif 
