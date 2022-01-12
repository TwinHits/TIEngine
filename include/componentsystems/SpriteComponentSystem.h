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

		static const inline std::string SPRITE = "sprite";
		static const inline std::string DRAWN = "sprite.drawn";
		static const inline std::string TEXTURE = "sprite.texture";
		static const inline std::string WIDTH = "sprite.width";
		static const inline std::string HEIGHT = "sprite.height";
		static const inline std::string ORIGIN_X_OFFSET = "sprite.originOffset.x";
		static const inline std::string ORIGIN_Y_OFFSET = "sprite.originOffset.y";
		static const inline std::string REPEATED = "sprite.repeated";
		static const inline std::string ROTATES = "sprite.rotates";
		static const inline std::string SHOW_WIREFRAME = "sprite.showWireframe";
	private: 
		struct Components {
			SpriteComponent& spriteComponent;
			PositionComponent& positionComponent;
			TIEntity& tientity;
		};
		std::list<Components> components;
};

}
#endif 
