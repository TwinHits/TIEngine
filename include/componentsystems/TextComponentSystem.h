#ifndef TEXTCOMPONENTSYSTEM_H
#define TEXTCOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/TextComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"

namespace TIE {

class TextComponentSystem : public Singleton<TextComponentSystem>, ComponentSystem {
	public:
		TextComponentSystem() {};
		void update(const float);
		void addComponent(const TIEntityFactory&, TIEntity&);

		static const std::string DRAWN;
		static const std::string TEXT;
		static const std::string OFFSET_X;
		static const std::string OFFSET_Y;
	private:		
		struct Components {
			TextComponent& textComponent;
			PositionComponent& positionComponent;
		};
		std::vector<Components> components;
};

}
#endif 
