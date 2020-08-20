#ifndef SPRITECOMPONENTSYSTEM_H
#define SPRITECOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <string>

#include "objects/components/SpriteComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"

namespace TIE {

class SpriteComponentSystem : public Singleton<SpriteComponentSystem>, ComponentSystem {
	public:
		SpriteComponentSystem() {};
		void update(const float);
		SpriteComponent& addComponent(TIEntity&);
		void addComponent(const TIEntityFactory&, TIEntity&);

		static const std::string DRAWN;
		static const std::string TEXTURE;
		static const std::string ROTATION;
		static const std::string DRAWN_KEY;
		static const std::string TEXTURE_KEY;
		static const std::string ROTATION_KEY;
	private: 
};

}
#endif 
